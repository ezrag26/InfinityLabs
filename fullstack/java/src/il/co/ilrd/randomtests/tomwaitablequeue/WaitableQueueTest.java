package il.co.ilrd.randomtests.tomwaitablequeue;

import il.co.ilrd.waitablequeue.WaitableQueue;
import org.junit.jupiter.api.MethodOrderer;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestMethodOrder;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;
import java.util.function.Consumer;

import static org.junit.jupiter.api.Assertions.*;

@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
class WaitableQueueTest {
    private WaitableQueue<Integer> wq = new WaitableQueue<>(10);
    private static Integer[] integers = {1, 5, 3, 10, -1, 8, 0, 4};
    private static final int THREADS = 10000;
    private List<Thread> producers = new ArrayList<>();
    private List<Thread> consumers = new ArrayList<>();
    private static int i = 0;

    public void initProducers(Consumer<Void> func) {
        for (int i = 0; i < THREADS; ++i) {
            producers.add(new Producer(func));
        }
    }

    public void initConsumers(Consumer<Void> func) {
        for (int i = 0; i < THREADS; ++i) {
            consumers.add(new MyConsumers(func));
        }
    }

    @Test
    public void testEnqueue() throws InterruptedException {


        int size = 0;

        for (Integer integer : integers) {
            wq.enqueue(integer);
            assertEquals(++size, wq.size());
        }
    }

    @Test
    public void testDequeue() throws InterruptedException {
        Integer[] expDequeue = {-1, 0, 1, 3, 4, 5, 8, 10};

        for (Integer integer : integers) {
            wq.enqueue(integer);
        }

        for (Integer integer : expDequeue) {
            assertEquals(integer, wq.dequeue());
        }
    }

    @Test
    public void testManyThreads() throws InterruptedException {
        initProducers(this::producerRun);
        initConsumers(this::consumerRun);

        for (Thread producer : producers) {
            producer.start();
        }

        for (Thread consumer : consumers) {
            consumer.start();
        }

        for (Thread producer : producers) {
            producer.join();
        }

        for (Thread consumer : consumers) {
            consumer.join();
        }

        assertEquals(0, wq.size());
    }

    @Test @Order(1)
    public void testRemove() throws InterruptedException {
        List<Thread> producers = new ArrayList<>();
        List<Thread> consumers = new ArrayList<>();

        for (int i = 0; i < THREADS; ++i) {
            producers.add(new Producer(this::producerRun));
        }

        for (int i = 0; i < THREADS; ++i) {
            consumers.add(new MyConsumers(this::consumerRemove));
        }

        for (Thread producer: producers) {
            producer.start();
        }

        for (Thread consumer: consumers) {
            consumer.start();
        }

        for (Thread consumer : consumers) {
            consumer.join();
        }
        assertEquals(THREADS - 1, wq.size());

    }

    @Test
    public void testTimeout() throws InterruptedException {
        List<Thread> consumers = new ArrayList<>();
        int threads = 9000;
        for (int i = 0; i < threads; ++i) {
            consumers.add(new MyConsumers(this::consumerTimeoutDequeue));
        }

        for (Thread consumer: consumers) {
            consumer.start();
        }

        assertEquals(0, wq.size());

        for (Thread consumer : consumers) {
            consumer.join();
        }

        assertEquals(0, wq.size());

    }

    public void producerRun(Void aVoid) {
        int product = ++i;
        wq.enqueue(product);
        System.out.println(Thread.currentThread().getName() + " enqueued " + product);
    }

    public void consumerRun(Void aVoid) {
        int i = 0;
        Integer product = null;
        try {
            product = wq.dequeue();
        } catch (InterruptedException ignored) {}
        System.out.println(Thread.currentThread().getName() + " dequeued " + product);
    }

    public void consumerRemove(Void aVoid) {
            wq.remove(5);
    }

    public void consumerTimeoutDequeue(Void aVoid) {
        try {
            assertThrows(NullPointerException.class, () -> wq.dequeue(3, null));
            assertNull(wq.dequeue(3, TimeUnit.SECONDS));
        } catch (InterruptedException ignored) {}
    }

    class Producer extends Thread {
        Consumer<Void> func;
        public Producer(Consumer<Void> func) {this.func = func;}

        @Override
        public void run() {
            func.accept(null);
        }
    }

    class MyConsumers extends Thread {
        Consumer<Void> func;
        public MyConsumers(Consumer<Void> func) {this.func = func;}

        @Override
        public void run() {
            func.accept(null);

        }
    }

}
