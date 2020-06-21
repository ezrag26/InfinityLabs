package il.co.ilrd.threadpool;

import il.co.ilrd.waitablequeue.WaitableQueue;

import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;

public class ThreadPool {
	private final WaitableQueue<Task<?>> tasks = new WaitableQueue<>();

	private final AtomicInteger numOfActiveThreads = new AtomicInteger(0);

	private final Semaphore pauseSem = new Semaphore(0);
	private final Semaphore threadDeactivationSem = new Semaphore(0);

	private boolean isShutdown = false;
	private boolean isPaused = false;

	private static final int HIGHEST_PRIORITY = Priority.MAX_PRIORITY.priority + 1;
	private static final int LOWEST_PRIORITY = Priority.MIN_PRIORITY.priority - 1;


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

		int priority;

		Priority(int priority) { this.priority = priority; }
	}

	private enum TaskStatus {
		QUEUED {
			@Override
			boolean cancel(Task<?> task, WaitableQueue<Task<?>> wq, boolean mayInterruptIfRunning) {
				/* has not begun to run, can be removed with no problem */
				wq.remove(task);
				task.futureTask.status = CANCELED;
				task.getVal.release();

				return true;
			}
		},
		RUNNING {
			@Override
			boolean cancel(Task<?> task, WaitableQueue<Task<?>> wq, boolean mayInterruptIfRunning) {
				if (mayInterruptIfRunning) {
					task.futureTask.handlingThread.interrupt();
				}

				return mayInterruptIfRunning;
			}
		},
		CANCELED {
			@Override
			boolean cancel(Task<?> task, WaitableQueue<Task<?>> wq, boolean mayInterruptIfRunning) {
				return false;
			}
		},
		DONE {
			@Override
			boolean cancel(Task<?> task, WaitableQueue<Task<?>> wq, boolean mayInterruptIfRunning) {
				return false;
			}
		};

		abstract boolean cancel(Task<?> task, WaitableQueue<Task<?>> wq, boolean mayInterruptIfRunning);
	}

	private class Task<T> implements Comparable<T> {
		private Callable<T> callable;
		private int priority;
		private FutureTask futureTask = new FutureTask();
		private Semaphore getVal = new Semaphore(0);

		private class FutureTask implements Future<T> {
			private T returnVal;
			private TaskStatus status = TaskStatus.QUEUED;
			private Thread handlingThread;
			Exception e;

			/**
			 * Cancels a future task if possible. A task can be cancelled if
			 * it has yet to run or if it is running and mayInterruptIfRunning
			 * is {@code true}.
			 *
			 * @param mayInterruptIfRunning {@code true} if the thread handling
			 * an already running task can be interrupted or {@code false} if
			 * not.
			 * @return {@code true} if the task could be cancelled, {@code false}
			 * if not.
			 */
			@Override
			public boolean cancel(boolean mayInterruptIfRunning) {
				return status.cancel(Task.this, tasks, mayInterruptIfRunning);
			}

			/**
			 * Checks whether this future task is a cancelled task
			 *
			 * @return {@code true} if this future task is cancelled,
			 * {@code false} if not.
			 */
			@Override
			public boolean isCancelled() {
				return status == TaskStatus.CANCELED;
			}

			/**
			 * Checks if this future task will not run in the future.
			 *
			 * @return {@code true} if this future task is done, {@code false}
			 * if not.
			 */
			@Override
			public boolean isDone() {
				return status != TaskStatus.QUEUED &&
						status != TaskStatus.RUNNING;
			}

			private T getReturnVal() throws ExecutionException {
				if (isCancelled()) throw new CancellationException();
				if (e != null) throw new ExecutionException(e);

				return returnVal;
			}

			/**
			 * Blocks until this future task returns
			 *
			 * @return the tasks return value specified at submit() invocation
			 *
			 * @throws InterruptedException if the task was cancelled during
			 * execution
			 * @throws ExecutionException if the task throws an exception during
			 * execution
			 */
			@Override
			public T get() throws InterruptedException, ExecutionException {
				getVal.acquire();

				return getReturnVal();
			}

			/**
			 * Blocks until this future task returns, or the given timeout
			 * period elapsed, whichever comes first.
			 *
			 * @return the tasks return value specified at submit() invocation
			 *
			 * @throws InterruptedException if the task was cancelled during
			 * execution
			 * @throws ExecutionException if the task throws an exception during
			 * execution
			 * @throws TimeoutException if the task did not return during the
			 * specified timeout period
			 */
			@Override
			public T get(long timeout, TimeUnit unit) throws InterruptedException, ExecutionException, TimeoutException {
				if (!getVal.tryAcquire(timeout, unit))
					throw new TimeoutException();

				return getReturnVal();
			}

		}

		public Task(Runnable r, int priority, T value) {
			callable = () -> {
				r.run();
				return value;
			};

			this.priority = priority;
		}

		public Task(Callable<T> c, int priority) {
			callable = c;
			this.priority = priority;
		}

		@Override
		public int compareTo(Object o) {
			return Integer.compare(((Task<?>)o).priority, priority);
		}
	}

	private class WorkerThread extends Thread {
		private boolean isActive = true;

		@Override
		public void run() {
			while (isActive) {
				try {
					@SuppressWarnings("unchecked")
					Task<Object> task = (Task<Object>)tasks.dequeue();
					task.futureTask.handlingThread = this;
					task.futureTask.status = TaskStatus.RUNNING;
					try {
						task.futureTask.returnVal = task.callable.call();
						task.futureTask.status = TaskStatus.DONE;
					} catch (InterruptedException ignored) {
						task.futureTask.status = TaskStatus.CANCELED;
					} catch (Exception e) {
						task.futureTask.e = e;
					} finally {
						task.getVal.release();
					}
				} catch (InterruptedException ignored) {}
			}
		}
	}

	private void createWorkerThread(int initNumThreads) {
		for (int i = 0; i < initNumThreads; ++i) {
			new WorkerThread().start();
			numOfActiveThreads.getAndIncrement();
		}
	}

	public ThreadPool(int initNumThreads) {
		createWorkerThread(initNumThreads);
	}

	public Future<Void> submit(Runnable runnable, Priority priority) {
		return submit(runnable, priority, null);
	}

	public <T> Future<T> submit(Runnable runnable, Priority priority, T value) {
		if (isShutdown) throw new RejectedExecutionException();

		Task<T> task = new Task<>(runnable, priority.priority, value);
		tasks.enqueue(task);

		return task.futureTask;
	}

	public <T> Future<T> submit(Callable<T> callable) {
		return submit(callable, Priority.NORMAL_PRIORITY);
	}

	public <T> Future<T> submit(Callable<T> callable, Priority priority) {
		if (isShutdown) throw new RejectedExecutionException();

		Task<T> task = new Task<>(callable, priority.priority);
		tasks.enqueue(task);

		return task.futureTask;
	}

	private Task<?> addActiveThreadTask = new Task<>(() -> {
		createWorkerThread(1);

		return null;
	}, HIGHEST_PRIORITY);

	private Task<?> deleteActiveThreadTask = new Task<>(() -> {
		((WorkerThread)Thread.currentThread()).isActive = false;
		numOfActiveThreads.getAndDecrement();
		return null;
	}, HIGHEST_PRIORITY);

	public void setNumThreads(int numThreads) {
		if (numThreads < 1) throw new IllegalArgumentException("numThreads must be greater than 0");
		int threadDifference = numOfActiveThreads.get() - numThreads;

		if (threadDifference > 0) {
			addSpecialTask(deleteActiveThreadTask, threadDifference);
		} else {
			addSpecialTask(addActiveThreadTask, -threadDifference);
		}
	}

	private void addSpecialTask(Task<?> task, int n) {
		for (int i = 0; i < n; ++i) {
			tasks.enqueue(task);
		}
	}

	private Task<?> pauseTask = new Task<>(() -> {
			pauseSem.acquire();
			return null;
	}, HIGHEST_PRIORITY);

	public void pause() {
		if (isShutdown) throw new RejectedExecutionException();
		if (isPaused) return;

		isPaused = true;

		addSpecialTask(pauseTask, numOfActiveThreads.get());
	}

	public void resume() {
		if (isShutdown) throw new RejectedExecutionException();
		isPaused = false;

		pauseSem.release(numOfActiveThreads.get());
	}

	private Task<?> shutdownTask = new Task<>(() -> {
		((WorkerThread)Thread.currentThread()).isActive = false;
		threadDeactivationSem.release();

		return null;
	}, LOWEST_PRIORITY);

	public void shutdown() {
		if (isShutdown) return;
		if (isPaused) resume();
		isShutdown = true;

		addSpecialTask(shutdownTask, numOfActiveThreads.get());
	}

	public void awaitTermination() throws InterruptedException {
		threadDeactivationSem.acquire(numOfActiveThreads.get());
	}

	public boolean awaitTermination(long timeout, TimeUnit unit) throws InterruptedException {
		return threadDeactivationSem.tryAcquire(numOfActiveThreads.get(), timeout, unit);
	}
}