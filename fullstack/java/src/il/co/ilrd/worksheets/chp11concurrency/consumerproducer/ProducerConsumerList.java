package il.co.ilrd.worksheets.chp11concurrency.consumerproducer;

import org.apache.commons.collections4.queue.CircularFifoQueue;

import java.util.Queue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.ReentrantLock;

public class ProducerConsumerList {
//	static List<String> gList = new LinkedList<String>();
	static int queueSize = 5;
	static Queue<String> gList = new CircularFifoQueue<>(queueSize);
	static boolean run = true;
	public static void main(String[] args) throws InterruptedException {
		int numOfProducers = 3;
		int numOfConsumers = 3;

		Producer[] proArray = new Producer[numOfProducers];
		Consumer[] conArray = new Consumer[numOfConsumers];
		Thread[] threads = new Thread[numOfProducers + numOfConsumers];

//		ReentrantLock lock = new ReentrantLock();
		ReentrantLock proLock = new ReentrantLock();
		ReentrantLock conLock = new ReentrantLock();
		Semaphore semProduct = new Semaphore(0);
		Semaphore semShelfSpace = new Semaphore(queueSize);

		for (int i = 0; i < numOfProducers; ++i) {
			proArray[i] = new Producer(/*lock, */proLock, semProduct, semShelfSpace);
		}

		for (int i = 0; i < numOfConsumers; ++i) {
			conArray[i] = new Consumer(/*lock, */conLock, semProduct, semShelfSpace);
		}

		for (int i = 0; i < numOfProducers; ++i) {
			threads[i] = new Thread(proArray[i]);
		}

		for (int i = numOfProducers; i < numOfProducers + numOfConsumers; ++i) {
			threads[i] = new Thread(conArray[i - numOfProducers]);
		}

		for (int i = 0; i < numOfProducers + numOfConsumers; ++i) {
			threads[i].start();
		}

		for (int i = 0; i < numOfProducers; ++i) {
			threads[i].join();
		}

		run = false;

	}

	static class Producer implements Runnable {
		int item = 0;
//		ReentrantLock lock;
		ReentrantLock proLock;
		Semaphore semProduct;
		Semaphore semShelfSpace;

		String ProduceItem() {
			return Thread.currentThread().getName() + "-" + ++item;
		}

		public Producer(/*ReentrantLock lock, */ReentrantLock proLock, Semaphore semProduct, Semaphore semShelfSpace) {
//			this.lock = lock;
			this.proLock = proLock;
			this.semProduct = semProduct;
			this.semShelfSpace = semShelfSpace;
		}

		@Override
		public void run() {
			while (item < 1000000) {
				String product = ProduceItem();

				/*
				since a product is being added, reduce the amount of available
				space for another product, stopping producers from adding any
				more products if there is no more space available
				 */
				semShelfSpace.acquireUninterruptibly();

				/*
				acquire mutual exclusion so that this producer can add a
				product without any other producer or consumer to interfere
				in the middle
				 */
//				lock.lock();

				/*
				lock only the producers, because with a fixed sized queue and
				the two semaphores, there will never be a situation where a
				producer and consumer are reading/writing to the same element,
				but we need to avoid 2 reads or 2 writes at the same time, so
				create mutual exclusion for the producers so only one producer
				will enter at a time to write
				 */
				proLock.lock();

				/* add product to list */
				gList.add(product);

				System.out.println(Thread.currentThread().getName() + " added " + product);

				/*
				release the mutual exclusion so that any producer or
				consumer can now update the list
				 */
//				lock.unlock();
				proLock.unlock();

				/*
				since a product was just added, increase products available
				so that consumers can know that they can enter and buy
				 */
				semProduct.release();
			}
		}
	}

	static class Consumer implements Runnable {
		String consumedProduct;
//		ReentrantLock lock;
		ReentrantLock conLock;
		Semaphore semProduct;
		Semaphore semShelfSpace;

		public Consumer(/*ReentrantLock lock, */ReentrantLock conLock, Semaphore semProduct, Semaphore semShelfSpace) {
//			this.lock = lock;
			this.conLock = conLock;
			this.semProduct = semProduct;
			this.semShelfSpace = semShelfSpace;
		}

		@Override
		public void run() {
			while (run) {
				/*
				reduce total products left so that producers new
				consumers will not try to buy if none are left
				*/
				semProduct.acquireUninterruptibly();

				/*
				acquire mutual exclusion so that only this consumer can
				update the list without any interferences from any other
				consumer or a producer
				 */
//				lock.lock();

				/*
				lock only the consumers, because with a fixed sized queue and
				the two semaphores, there will never be a situation where a
				producer and consumer are reading/writing to the same element,
				but we need to avoid 2 reads or 2 writes at the same time, so
				create mutual exclusion for the consumers so only one consumer
				will enter at a time to read
				 */
				conLock.lock();

				/*
				creates busy waiting if a consumer tries to buy when
				there are no products. Problem fixed using semaphore that
				only allows a consumer to enter the critical section
				when the list is not empty
				*/
//				    while (gList.isEmpty()) {
//					    lock.unlock();
//					    lock.lock();
//				}

				/* consume product */
				consumedProduct = gList.remove();

				/*
				release lock so that any producer or consumer can now enter
				*/
//				lock.unlock();
				conLock.unlock();
				System.out.println(Thread.currentThread().getName() + " Consumed " + consumedProduct);

				/*
				since a consumer just bought, there is now more space for a
				producer to add another product
				*/
				semShelfSpace.release();

			}
		}
	}
}
