package il.co.ilrd.reviews.lidanthreadpool;

import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ThreadPoolFix {
    private static final int SHUTDOWN_PRIORITY = Priority.MIN_PRIORITY.value - 1;
    private static final int URGENT_TASK_PRIORITY = Priority.MAX_PRIORITY.value + 1;
    private AtomicInteger currentNumOfThreads;
    private WaitableQueue<Task<?>> tasks;
    //FIXME I didn't see any real use for this Map... Like I saw that you used
    // it, but I think it didn't help you in any way within your code. Seems not
    // needed and can be removed, which also means you won't need the nThreadsLock
    private Map<Long, WorkerThread> threadsMap;
    private Lock nThreadsLock;
    private Semaphore pauseSem;
    private Semaphore terminationSem;
    private boolean isShutDown;
    private boolean isPaused;

    public enum Priority {
        MIN_PRIORITY(1),
        ONE(1),
        TWO(2),
        THREE(3),
        FOUR(4),
        NORMAL_PRIORITY(5),
        FIVE(5),
        SIX(6),
        SEVEN(7),
        EIGHT(8),
        NINE(9),
        TEN(10),
        MAX_PRIORITY(10);

        private int value;

        private Priority(int priority) {
            this.value = priority;
        }
    }

    private enum TaskStatus {
        QUEUED {
            @Override
            boolean cancel(WaitableQueue<Task<?>> tasks, Task<?> t, boolean mayInterruptIfRunning) {
                tasks.remove(t);
                t.futureTask.status = CANCELED;
                t.futureTask.taskIsDoneSem.release();

                return true;
            }
        },
        RUNNING {
            @Override
            boolean cancel(WaitableQueue<Task<?>> tasks, Task<?> t, boolean mayInterruptIfRunning) {
                if (mayInterruptIfRunning) t.futureTask.handlingThread.interrupt();

                return mayInterruptIfRunning;
            }
        },
        CANCELED {
            @Override
            boolean cancel(WaitableQueue<Task<?>> tasks, Task<?> t, boolean mayInterruptIfRunning) {
                return false;
            }
        },
        DONE {
            @Override
            boolean cancel(WaitableQueue<Task<?>> tasks, Task<?> t, boolean mayInterruptIfRunning) {
                return false;
            }
        },
        EXCEPTION_THROWN {
            @Override
            boolean cancel(WaitableQueue<Task<?>> tasks, Task<?> t, boolean mayInterruptIfRunning) {
                return false;
            }
        };

        abstract boolean cancel(WaitableQueue<Task<?>> tasks, Task<?> t, boolean mayInterruptIfRunning);
    }

    private class Task<T> implements Comparable<T> {
        private Callable<T> callable;
        private int priority;
        private FutureTask futureTask;

        private class FutureTask implements Future<T> {
            private Object returnVal;
            private Exception exception;
            private WorkerThread handlingThread;

            private TaskStatus status = TaskStatus.QUEUED;
            private Semaphore taskIsDoneSem = new Semaphore(0);

            @Override
            public boolean cancel(boolean mayInterruptIfRunning) {
                return status.cancel(tasks, Task.this, mayInterruptIfRunning);
            }

            @Override
            public boolean isCancelled() {
                return status == TaskStatus.CANCELED;
            }

            @Override
            public boolean isDone() {
                return status != TaskStatus.RUNNING && status != TaskStatus.QUEUED;
            }

            @Override
            public T get() throws InterruptedException, ExecutionException {
                taskIsDoneSem.acquire(); // waits until task is done

                return getImp();
            }

            @Override
            public T get(long timeout, TimeUnit unit) throws InterruptedException, ExecutionException, TimeoutException {
                // tryAcquire returns false in case of timeout
                if (!taskIsDoneSem.tryAcquire(timeout, unit)) throw new TimeoutException();

                return getImp();
            }

            private T getImp() throws ExecutionException {
                if (isCancelled()) throw new CancellationException("Task was canceled.");
                else if (exception != null) throw new ExecutionException(exception);

                @SuppressWarnings("unchecked")
                T result =  (T)returnVal;

                return result;
            }
        } // class FutureTask

        public Task(Runnable r, int priority, T value) {
            this.futureTask = new FutureTask();
            this.priority = priority;
            this.callable = () -> {
                r.run();

                return value;
            };
        }

        public Task(Callable<T> c, int priority) {
            this.futureTask = new FutureTask();
            this.priority = priority;
            this.callable = c;
        }

        @Override
        public int compareTo(Object o) {
            return ((Task<?>) o).priority - this.priority;
        }
    }

    private class WorkerThread extends Thread {
        volatile boolean isActive = true;

        @Override
        public void run() {
            Task<?> task = null;
            while (isActive) {
                try {
                    task = tasks.dequeue();
                    task.futureTask.handlingThread = this;
                    task.futureTask.status = TaskStatus.RUNNING;
                    try {
                        task.futureTask.returnVal = task.callable.call();
                        task.futureTask.status = TaskStatus.DONE;
                    } catch (InterruptedException e) {
                        task.futureTask.status = TaskStatus.CANCELED;
                    } catch (Exception e) {
                        task.futureTask.exception = e;
                        task.futureTask.status = TaskStatus.EXCEPTION_THROWN;

                        // to signal the get method that the task is over
                    } finally { task.futureTask.taskIsDoneSem.release(); }
                /*dequeue interrupt is ignored, may be used later in case
                 of ShutDownNow feature addition*/
                } catch (InterruptedException ignore) {}
            }
            nThreadsLock.lock();
            threadsMap.remove(Thread.currentThread().getId());
            nThreadsLock.unlock();

            //FIXME why don't you just have the shutdownTask do this release? Right now you have to check this every time a task runs
            if(task.priority == SHUTDOWN_PRIORITY) terminationSem.release();
        }
    }

    public ThreadPoolFix(int initNumThreads) {
        if (initNumThreads < 1) throw new IllegalArgumentException("num of threads must be greater than 0.");
        currentNumOfThreads = new AtomicInteger(initNumThreads);
        tasks = new WaitableQueue<>();
        pauseSem = new Semaphore(initNumThreads); //FIXME why not initialize to 0? Then you don't need to drain the permits on pause
        terminationSem = new Semaphore(0);
        isShutDown = false;
        isPaused = false;
        threadsMap = new HashMap<>(initNumThreads);
        nThreadsLock = new ReentrantLock();
        addThreadsToPool(initNumThreads);
    }

    public void setNumThreads(int numThreads) {
        if (numThreads < 1) throw new IllegalArgumentException("num of threads must be greater than 0.");

        int threadsDelta = currentNumOfThreads.get() - numThreads;

        currentNumOfThreads.set(numThreads);
        if (threadsDelta < 0) addShutDownTasks(-threadsDelta, URGENT_TASK_PRIORITY);
        else {
            // in case of adding threads after shutdown - add shutdown tasks as well
            if (isShutDown) addShutDownTasks(threadsDelta, SHUTDOWN_PRIORITY);
            else if (isPaused) addPauseTasks(threadsDelta);

            addThreadsToPool(threadsDelta);
        }
    }

    private void addThreadsToPool(int n) {
        nThreadsLock.lock();
        while (n > 0) {
            WorkerThread worker = new WorkerThread();
            threadsMap.put(worker.getId(), worker);
            worker.start();
            --n;
        }
        nThreadsLock.unlock();
    }

    private void addShutDownTasks(int nTasks, int priority) {
        for (int i = 0; i < nTasks; ++i) {
            tasks.enqueue(new Task<Void>(() -> {
                WorkerThread worker = threadsMap.get(Thread.currentThread().getId());
                worker.isActive = false;
            }, priority, null));
        }
    }

    private void addPauseTasks(int nTasks) {
        for (int i = 0; i < nTasks; ++i) {
            tasks.enqueue(new Task<Void>(() -> {
                pauseSem.acquireUninterruptibly();
            }, URGENT_TASK_PRIORITY, null));
        }
    }

    public Future<Void> submit(Runnable runnable) {
        return submit(runnable, Priority.NORMAL_PRIORITY, null);
    }

    public Future<Void> submit(Runnable runnable, Priority priority) {
        return submit(runnable, priority, null);
    }

    public <T> Future<T> submit(Runnable runnable, Priority priority, T value) {
        Objects.requireNonNull(runnable, "runnable cannot be null.");
        Objects.requireNonNull(priority, "priority cannot be null.");

        if (isShutDown) throw new RejectedExecutionException("Thread pool has already been shut down.");

        Task<T> t = new Task<>(runnable, priority.value, value);
        tasks.enqueue(t);

        return t.futureTask;
    }

    public <T> Future<T> submit(Callable<T> callable) {
        return submit(callable, Priority.NORMAL_PRIORITY);
    }

    public <T> Future<T> submit(Callable<T> callable, Priority priority) {
        Objects.requireNonNull(callable, "callable cannot be null.");
        Objects.requireNonNull(priority, "priority cannot be null.");

        if (isShutDown) throw new RejectedExecutionException("Thread pool has already been shut down.");

        Task<T> t = new Task<>(callable, priority.value);
        tasks.enqueue(t);

        return t.futureTask;
    }

    public void pause() {
        if (isShutDown) throw new RejectedExecutionException("Thread pool has already been shut down.");
        if (isPaused) return;

        isPaused = true;

        //FIXME If you initialize the pauseSem to 0, then you don't need to drain all the permits
        pauseSem.drainPermits();
        addPauseTasks(currentNumOfThreads.get());
    }

    public void resume() {
        if (isShutDown) throw new RejectedExecutionException("Thread pool has already been shut down.");

        pauseSem.release(currentNumOfThreads.get());
    }

    public void shutdown() {
        if (isShutDown) return;

        resume();
        isShutDown = true;

        // enqueue numOfThreads shutdown tasks to the tasks queue
        addShutDownTasks(currentNumOfThreads.get(), SHUTDOWN_PRIORITY);
    }

    public void awaitTermination() throws InterruptedException {
        shutdown();
        terminationSem.acquire(currentNumOfThreads.get());
    }

    public boolean awaitTermination(long timeout, TimeUnit unit) throws InterruptedException {
        shutdown();

        return terminationSem.tryAcquire(currentNumOfThreads.get(), timeout, unit);
    }
}
