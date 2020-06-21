package il.co.ilrd.worksheets.chp11concurrency.ex1;

public class ThreadAndRunnableTask {
	public static void main(String[] args) {
		ThreadRunnable runnable = new ThreadRunnable();

		Thread t1 = new Thread(runnable);
		t1.start();
		try {
			Thread.sleep(1000);
		} catch (InterruptedException ignored) {}
		runnable.stopRunning();

		ThreadSubclass t2 = new ThreadSubclass();
		t2.start();
		try {
			Thread.sleep(1000);
		} catch (InterruptedException ignored) {}
		t2.stopRunning();
	}
}

class ThreadRunnable implements Runnable {
	boolean isRunning = true;

	void stopRunning() {
		isRunning = false;
	}

	@Override
	public void run() {
		while (isRunning) {
			System.out.println(Thread.currentThread().getName());
		}
	}
}

class ThreadSubclass extends Thread {
	boolean isRunning = true;

	void stopRunning() {
		isRunning = false;
	}

	@Override
	public void run() {
		while (isRunning) {
			System.out.println(Thread.currentThread().getName());
		}
	}
}
