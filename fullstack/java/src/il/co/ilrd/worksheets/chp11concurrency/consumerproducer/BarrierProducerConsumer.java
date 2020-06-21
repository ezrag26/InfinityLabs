package il.co.ilrd.worksheets.chp11concurrency.consumerproducer;

import org.apache.commons.collections4.queue.CircularFifoQueue;

import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class BarrierProducerConsumer {
	static final int NUM_OF_CONSUMERS = 10;
	static CircularFifoQueue<Integer> gList = new CircularFifoQueue<>(NUM_OF_CONSUMERS);

	public static void main(String[] args) {
		ReentrantLock lock = new ReentrantLock();
		Semaphore semConsumersReady = new Semaphore(0);
		Condition isReady = lock.newCondition();
		Thread[] conThreads = new Thread[NUM_OF_CONSUMERS];

		Thread proThread = new Thread(new Producer(lock, semConsumersReady, isReady));
		proThread.setName("Producer");

		for (int i = 0; i < NUM_OF_CONSUMERS; ++i) {
			conThreads[i] = new Thread(new Consumer(lock, semConsumersReady, isReady));
			conThreads[i].setName("Consumer " + (i + 1));
		}

		proThread.start();

		for (Thread thread : conThreads) {
			thread.start();
		}
	}

	static class Producer implements Runnable {
		ReentrantLock lock;
		Semaphore semConsumersReady;
		Condition isReady;

		public Producer(ReentrantLock lock, Semaphore semConsumersReady, Condition isReady) {
			this.lock = lock;
			this.semConsumersReady = semConsumersReady;
			this.isReady = isReady;
		}

		void createProducts() {
			for (int i = 0; i < NUM_OF_CONSUMERS; ++i) {
				products[i] = ++productNumber;
			}
		}

		int productNumber = 0;
		static int[] products = new int[NUM_OF_CONSUMERS];

		@Override
		public void run() {

			while (true) {
				createProducts();

				semConsumersReady.acquireUninterruptibly(NUM_OF_CONSUMERS);

				lock.lock();
				for (int i = 0; i < NUM_OF_CONSUMERS; ++i) {
					gList.add(products[i]);
					System.out.println(Thread.currentThread().getName() + " added " + products[i]);
				}

				isReady.signalAll();
				lock.unlock();
			}
		}
	}

	static class Consumer implements Runnable {
		ReentrantLock lock;
		Semaphore semConsumersReady;
		Condition isReady;

		public Consumer(ReentrantLock lock, Semaphore semConsumersReady, Condition isReady) {
			this.lock = lock;
			this.semConsumersReady = semConsumersReady;
			this.isReady = isReady;
		}

		@Override
		public void run() {
			while (true) {
				lock.lock();

				semConsumersReady.release();
				isReady.awaitUninterruptibly();

				lock.lock();
				int product = gList.remove();
				System.out.println(Thread.currentThread().getName() + " consumed " + product);
				lock.unlock();
			}
		}
	}
}
