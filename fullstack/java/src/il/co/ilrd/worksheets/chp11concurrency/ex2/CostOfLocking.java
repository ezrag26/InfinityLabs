package il.co.ilrd.worksheets.chp11concurrency.ex2;

import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.ReentrantLock;

/**
 * Synchronization Method   :   Execution time (milliseconds)
 *
 * Not synchronized         :   4 - 17
 * synchronized method      :   4 - 23
 * synchronized block       :   4 - 16
 * Atomics                  :   212 - 453
 * reentrant lock           :   6 - 19
 */

public class CostOfLocking {
//	static int i = 0;
	static AtomicInteger atomicI = new AtomicInteger(0);

	public static void main(String[] args) throws InterruptedException {
		ThreadRunnable runnable = new ThreadRunnable();
		Thread t1 = new Thread(runnable);
		Thread t2 = new Thread(runnable);

		long startTime = System.nanoTime();
		t1.start();
		t2.start();

		t1.join();
		t2.join();
		long endTime = System.nanoTime();
		long totalTime = endTime - startTime;
		
//		System.out.println(i);
		System.out.println(atomicI);
		System.out.println(totalTime / 1000000 + " milliseconds");
	}
}

class ThreadRunnable implements Runnable {
	ReentrantLock lock = new ReentrantLock();

	@Override
	public /*synchronized*/ void run() {
		int j = 10000000;
//		lock.lock();
//		synchronized (Integer.valueOf(1)) {
			while (j-- > 0) {
//				++CostOfLocking.i;
				CostOfLocking.atomicI.getAndIncrement();
			}
//		}
//		lock.unlock();
	}
}
