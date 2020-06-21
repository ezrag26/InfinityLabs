package il.co.ilrd.randomtests;

class IncNum {
	private int num;
	public Integer a = 0;
	public Integer b = 0;

	public IncNum(int num) {
		this.num = num;
	}

	public int getNum() {
		return this.num;
	}

	public void incNum(int num) {
		this.num += num;
	}
}

public class MonitorWaitAndNotify {
	public static void main(String[] args) throws InterruptedException {
//		IncNum obj = new IncNum(0);
//
//		Runnable runnable = new Runnable() {
//			@Override
//			public void run() {
//				synchronized (obj) {
//					try {
//						System.out.println(Thread.currentThread().getName());
//						System.out.println(Thread.currentThread().getName());
//						obj.wait(2000);
//
//						System.out.println(Thread.currentThread().getName());
//					} catch (InterruptedException e) {
//					}
//					obj.incNum(1);
//					System.out.println(Thread.currentThread().getName() + " : " + obj.getNum());
//				}
//			}
//		};
//
//		Runnable runnable2 = new Runnable() {
//			@Override
//			public void run() {
//				synchronized (obj) {
//					try {
//						System.out.println(Thread.currentThread().getName());
//						System.out.println(Thread.currentThread().getName());
//						obj.wait(2000);
//
//						System.out.println(Thread.currentThread().getName());
//					} catch (InterruptedException e) {
//					}
//					obj.incNum(1);
//					System.out.println(Thread.currentThread().getName() + " : " + obj.getNum());
//				}
//			}
//		};
//		Thread thread = new Thread(runnable);
//		Thread thread2 = new Thread(runnable2);
//		thread.start();
//		thread2.start();
//		Thread.sleep(1000);
//		synchronized (obj) {
//			obj.notifyAll();
//			System.out.println(Thread.currentThread().getName());
//			Thread.sleep(10000);
//			System.out.println(Thread.currentThread().getName() + " : " + obj.getNum());
//			obj.incNum(5);
//			System.out.println(Thread.currentThread().getName() + " : " + obj.getNum());
//
//		}

		IncNum obj2 = new IncNum(0);
		System.out.println("a = " + obj2.a);
		System.out.println("b = " + obj2.b);

		Runnable runnable3 = new Runnable() {
			@Override
			public void run(){
				synchronized (obj2) {
					try {
						System.out.println("In " + Thread.currentThread().getName());
						Thread.sleep(10000);
						System.out.println("a = " + ++obj2.a);
					}
					catch (InterruptedException ignored) {}
				}
			}
		};

		Thread t = new Thread(runnable3);

		t.start();
		Thread.sleep(2000);
		synchronized (obj2) {
			obj2.b += 10;
			System.out.println("b = " + obj2.b);

		}
	}
}

