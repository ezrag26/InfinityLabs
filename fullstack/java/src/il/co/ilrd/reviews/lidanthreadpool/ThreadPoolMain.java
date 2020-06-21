package il.co.ilrd.reviews.lidanthreadpool;

import il.co.ilrd.threadpool.ThreadPool;

import java.io.FileNotFoundException;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.RejectedExecutionException;

import static org.junit.jupiter.api.Assertions.*;

public class ThreadPoolMain {
	public static void main(String[] args) throws InterruptedException, ExecutionException, FileNotFoundException {
//		System.setOut(new PrintStream(new File("./src/il/co/ilrd/threadpool/TPOutput.txt")));
		System.out.println("initThreadPool()");
		initThreadPool();
		System.out.println("submitRunnableNoVal()");
		submitRunnableNoVal();
		System.out.println("submitRunnableVal()");
		submitRunnableVal();
		System.out.println("submitCallableWPriority()");
		submitCallableWPriority();
		System.out.println("submitCallable()");
		submitCallable();
		System.out.println("get()");
		get();
		System.out.println("pause()");
		pause();
		System.out.println("submitAfterShutdown()");
		submitAfterShutdown();
//		System.out.println("submitNull()");
//		submitNull();
	}

	private static final int NUM_OF_THREADS = 10;

	public static void initThreadPool() throws InterruptedException {
		ThreadPool threadPool = new ThreadPool(NUM_OF_THREADS);

		threadPool.shutdown();
		threadPool.awaitTermination();
	}

	public static void submitRunnableNoVal() throws InterruptedException, ExecutionException {
		ThreadPool threadPool = new ThreadPool(NUM_OF_THREADS);
		Future<Void> future = threadPool.submit(new Runnable() {
			@Override
			public void run() {
				System.out.println(Thread.currentThread().getName());
			}
		}, ThreadPool.Priority.MIN_PRIORITY);

		Future<?> nullCallable = threadPool.submit((Callable<?>) null, ThreadPool.Priority.NORMAL_PRIORITY);
		assertThrows(ExecutionException.class, nullCallable::get);

		assertNotNull(future);
		assertNull(future.get());

		threadPool.shutdown();
		threadPool.awaitTermination();
	}

	public static void submitRunnableVal() throws InterruptedException, ExecutionException {
		ThreadPool threadPool = new ThreadPool(NUM_OF_THREADS);
		Future<Integer> future = threadPool.submit(new Runnable() {
			@Override
			public void run() {
				System.out.println(Thread.currentThread().getName());
			}
		}, ThreadPool.Priority.MAX_PRIORITY, 5);

		assertNotNull(future);
		assertEquals(5, future.get());

		threadPool.shutdown();
		threadPool.awaitTermination();
	}

	public static void submitCallableWPriority() throws InterruptedException, ExecutionException {
		String retVal = "submitCallableWPriority";
		ThreadPool threadPool = new ThreadPool(NUM_OF_THREADS);
		Future<String> future = threadPool.submit(new Callable<>() {
			@Override
			public String call() {
				System.out.println(Thread.currentThread().getName());
				return retVal;
			}
		}, ThreadPool.Priority.EIGHT);

		assertNotNull(future);
		assertEquals(retVal, future.get());

		threadPool.shutdown();
		threadPool.awaitTermination();
	}

	public static void submitCallable() throws InterruptedException, ExecutionException {
		String retVal = "submitCallable";
		ThreadPool threadPool = new ThreadPool(NUM_OF_THREADS);
		Future<String> future = threadPool.submit(new Callable<>() {
			@Override
			public String call() {
				System.out.println(Thread.currentThread().getName());
				return retVal;
			}
		});

		assertNotNull(future);
		assertEquals(retVal, future.get());

		threadPool.shutdown();
		threadPool.awaitTermination();
	}

	public static void get() throws InterruptedException {
		ThreadPool threadPool = new ThreadPool(NUM_OF_THREADS);

		for (int i = 0; i < 200; ++i) {
			threadPool.submit(new Runnable() {
				@Override
				public void run() {
					System.out.println(Thread.currentThread().getName());
				}
			}, ThreadPool.Priority.MIN_PRIORITY);

			threadPool.submit(new Runnable() {
				@Override
				public void run() {
					System.out.println(Thread.currentThread().getName());
				}
			}, ThreadPool.Priority.NORMAL_PRIORITY);

			threadPool.submit(new Runnable() {
				@Override
				public void run() {
					System.out.println(Thread.currentThread().getName());
				}
			}, ThreadPool.Priority.MAX_PRIORITY);

		}

		threadPool.shutdown();
		threadPool.awaitTermination();
	}

	public static void pause() throws InterruptedException, ExecutionException {
		String retVal = "pause";
		ThreadPool threadPool = new ThreadPool(NUM_OF_THREADS);
		threadPool.pause();

		Future<String> future = threadPool.submit(new Callable<>() {
			@Override
			public String call() {
				System.out.println(Thread.currentThread().getName());
				return retVal;
			}
		});

		assertNotNull(future);

		threadPool.shutdown();
		threadPool.awaitTermination();
	}

	public static void submitAfterShutdown() throws InterruptedException, ExecutionException {
		String retVal = "submitAfterShutdown";
		ThreadPool threadPool = new ThreadPool(NUM_OF_THREADS);

		Future<String> future = threadPool.submit(new Callable<>() {
			@Override
			public String call() {
				System.out.println(Thread.currentThread().getName());
				return retVal;
			}
		});

		threadPool.shutdown();

		assertThrows(RejectedExecutionException.class, () -> threadPool.submit(new Callable<>() {
			@Override
			public String call() {
				System.out.println(Thread.currentThread().getName());
				return retVal;
			}
		}));

		threadPool.awaitTermination();
	}

	public static void submitNull() throws InterruptedException, ExecutionException {
		String retVal = "submitAfterShutdown";
		ThreadPool threadPool = new ThreadPool(NUM_OF_THREADS);

		assertThrows(NullPointerException.class, () -> threadPool.submit(null, ThreadPool.Priority.MIN_PRIORITY, "Hi"));

		threadPool.shutdown();
		threadPool.awaitTermination();
	}
}
