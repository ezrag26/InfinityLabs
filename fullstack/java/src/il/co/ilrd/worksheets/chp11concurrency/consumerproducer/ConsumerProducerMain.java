package il.co.ilrd.worksheets.chp11concurrency.consumerproducer;

import java.util.concurrent.atomic.AtomicBoolean;

public class ConsumerProducerMain {
	static int[] gArray = new int[1];
//	static volatile boolean isProducing = false;
	static AtomicBoolean atomicIsProducing = new AtomicBoolean(true);

	public static void main(String[] args) throws InterruptedException {

		Thread proThread = new Thread(new Runnable() {
			@Override
			public void run() {
				Producer.doThis();
			}
		});

		Thread conThread = new Thread(new Runnable() {
			@Override
			public void run() {
				Consumer.doThis();
			}
		});

		proThread.start();
		conThread.start();

		proThread.join();
		conThread.join();

	}

	static class Producer {
		static void doThis() {
			while (true) {
//				while (!isProducing);
				while (atomicIsProducing.get() == false);

				for (int i = 0; i < gArray.length; ++i) {
					++gArray[i];
				}

//				isProducing = false;
				atomicIsProducing.set(false);
			}
		}
	}

	static class Consumer {
		static void doThis() {
			while (true) {
//				while (isProducing);
				while (atomicIsProducing.get());

				int total = 0;
				for (int i = 0; i < gArray.length; ++i) {
					total += gArray[i];
				}
				System.out.println(total);

//				isProducing = true;
				atomicIsProducing.set(true);
			}
		}
	}
}
