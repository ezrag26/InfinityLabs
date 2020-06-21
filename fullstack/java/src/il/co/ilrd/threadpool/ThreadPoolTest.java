package il.co.ilrd.threadpool;

import org.junit.jupiter.api.Test;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;

import static org.junit.jupiter.api.Assertions.*;

class ThreadPoolTest {
	private static final int NUM_OF_THREADS = 10;

	@Test
	public void initThreadPool() throws InterruptedException {
		ThreadPool threadPool = new ThreadPool(NUM_OF_THREADS);


		threadPool.shutdown();
		threadPool.awaitTermination();
	}

	@Test
	public void submitRunnableNoVal() throws InterruptedException, ExecutionException {
		ThreadPool threadPool = new ThreadPool(NUM_OF_THREADS);
		Future<Void> future = threadPool.submit(new Runnable() {
			@Override
			public void run() {
				System.out.println(Thread.currentThread().getName());
			}
		}, ThreadPool.Priority.MIN_PRIORITY);

		assertNotNull(future);
		assertNull(future.get());

		threadPool.shutdown();
		threadPool.awaitTermination();
	}

	@Test
	public void submitRunnableVal() throws InterruptedException, ExecutionException {
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

	@Test
	public void submitCallableWPriority() throws InterruptedException, ExecutionException {
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

	@Test
	public void submitCallable() throws InterruptedException, ExecutionException {
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

	@Test
	public void pause() throws InterruptedException, ExecutionException {
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
		assertEquals(retVal, future.get());

		threadPool.shutdown();
		threadPool.awaitTermination();
	}

	@Test
	public void get() throws InterruptedException {
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
}