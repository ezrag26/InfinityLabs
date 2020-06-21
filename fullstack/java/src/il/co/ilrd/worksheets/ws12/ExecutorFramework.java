package il.co.ilrd.worksheets.ws12;

import java.util.concurrent.*;

public class ExecutorFramework {
	static int anInt = 0;
	public static void main(String[] args) throws ExecutionException, InterruptedException {
		System.out.println("singleThreadPool:");
		singleThread();
		System.out.println();
		System.out.println("fixedThreadPool:");
		fixedThreadPool();
		System.out.println();
		System.out.println("cachedThreadPool:");
		cachedThreadPool();
		System.out.println();
		System.out.println("scheduledThreadPool:");
		scheduledThreadPool();

	}

	public static void singleThread() throws InterruptedException, ExecutionException {
		ExecutorService executor = Executors.newSingleThreadExecutor();
		int ID = 0;

		Future<Integer> future = addCallable(executor, ++ID);
		Future<Integer> future1 = addCallable(executor, ++ID);
		Future<Integer> future2 = addCallable(executor, ++ID);
		addRunnable(executor, ++ID);
		addRunnable(executor, ++ID);

		executor.shutdown();

		try {
			addRunnable(executor, ++ID);
		} catch (RejectedExecutionException e) {
			System.out.println("New task submitted after shutdownNow() has been rejected!");
		}

		executor.awaitTermination(1, TimeUnit.SECONDS );
	}

	public static void fixedThreadPool() throws InterruptedException, ExecutionException {
		ExecutorService executor = Executors.newFixedThreadPool(3);
		int ID = 0;

		Future<Integer> future = addCallable(executor, ++ID);
		Future<Integer> future1 = addCallable(executor, ++ID);
		Future<Integer> future2 = addCallable(executor, ++ID);
		addRunnable(executor, ++ID);
		addRunnable(executor, ++ID);

		executor.shutdown();

		try {
			addRunnable(executor, ++ID);
		} catch (RejectedExecutionException e) {
			System.out.println("New task submitted after shutdownNow() has been rejected!");
		}

		executor.awaitTermination(1, TimeUnit.SECONDS );
	}

	public static void cachedThreadPool() throws InterruptedException, ExecutionException {
		ExecutorService executor = Executors.newCachedThreadPool();
		int ID = 0;

		Future<Integer> future = addCallable(executor, ++ID);
		Future<Integer> future1 = addCallable(executor, ++ID);
		Future<Integer> future2 = addCallable(executor, ++ID);
		addRunnable(executor, ++ID);
		addRunnable(executor, ++ID);


		try {
			addRunnable(executor, ++ID);
		} catch (RejectedExecutionException e) {
			System.out.println("New task submitted after shutdownNow() has been rejected!");
		}

		executor.awaitTermination(1, TimeUnit.SECONDS );
	}

	public static void scheduledThreadPool() throws InterruptedException, ExecutionException {
		ExecutorService executor = Executors.newScheduledThreadPool(10);
		int ID = 0;

		Future<Integer> future = addCallable(executor, ++ID);
		Future<Integer> future1 = addCallable(executor, ++ID);
		Future<Integer> future2 = addCallable(executor, ++ID);
		addRunnable(executor, ++ID);
		addRunnable(executor, ++ID);

		executor.shutdown();

		try {
			addRunnable(executor, ++ID);
		} catch (RejectedExecutionException e) {
			System.out.println("New task submitted after shutdownNow() has been rejected!");
		}

		executor.awaitTermination(1, TimeUnit.SECONDS );
	}

	public static Future<Integer> addCallable(ExecutorService executor, int ID) {
		return executor.submit(new Callable<Integer>() {
			@Override
			public Integer call() throws Exception {
				System.out.println(Thread.currentThread().getName() + " Callable" + ID);

				return 5;
			}
		});
	}

	public static void addRunnable(ExecutorService executor, int ID) {
		executor.submit(new Runnable() {
			@Override
			public void run() {
				System.out.println(Thread.currentThread().getName() + " Runnable" + ID);
			}
		});
	}


}
