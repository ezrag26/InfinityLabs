package il.co.ilrd.randomtests.threadinvokerun;

public class ThreadInvokeRunTest {
	public static void main(String[] args) {
		Runnable runnable = new Runnable() {
			@Override
			public void run() {
				System.out.println(Thread.currentThread().getName());
			}
		};
		
		Thread thread = new Thread(runnable);
		System.out.print("runnable.run(): ");
		runnable.run(); // invoking run() directly does not create a new thread
		System.out.print("thread.start(): ");
		thread.start(); // creates a new thread and invokes run()
	}
}
