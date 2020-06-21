package il.co.ilrd.worksheets.chp11concurrency.ex3;

import java.util.ArrayList;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

public class ProducerConsumer {
	public static void main(String[] args) throws InterruptedException {
		AtomicInteger atomicI = new AtomicInteger(0);
		ArrayList<Integer> buffer = new ArrayList<Integer>();
		Semaphore sem1 = new Semaphore(1);
		Semaphore sem2 = new Semaphore(1);

		Thread t1 = new Thread(new Runnable() {
			@Override
			public void run() {
//				Producer.proAtomicVar(atomicI);
				Producer.proSemaphore(sem1, sem2);
			}
		});

		Thread t2 = new Thread(new Runnable() {
			@Override
			public void run() {
//				Consumer.conAtomicVar(atomicI);
				Consumer.conSemaphore(sem1, sem2);
			}
		});

		t1.start();
		t2.start();
		t1.join();
		t2.join();
	}
}

class Producer {
	static void printThis(String message) {
		System.out.print(Thread.currentThread().getName() + " " + message + "... ");
	}

	static void proAtomicVar(AtomicInteger atomicI) {
		while (true) {
			if (atomicI.get() == 0) {
				printThis("Ping!");
				atomicI.set(1);
			}
		}
	}

	static void proSemaphore(Semaphore sem1, Semaphore sem2) {
		while (true) {
			try {
				sem1.acquire();
			} catch (InterruptedException ignored) {
			}
			printThis("Ping!");
			sem1.release();
		}
	}
}

class Consumer {
	static void printThis(String message) {
		System.out.println(Thread.currentThread().getName() + " " + message);
	}

	static void conAtomicVar(AtomicInteger atomicI) {
		while (true) {
			while (atomicI.get() != 0) {
				printThis("Pong!");
				atomicI.set(0);
			}
		}
	}

	static void conSemaphore(Semaphore sem1, Semaphore sem2) {
		while (true) {
			try {
				sem1.acquire();
			} catch (InterruptedException ignored) {
			}
			printThis("Pong!");
			sem1.release();
		}
	}

}