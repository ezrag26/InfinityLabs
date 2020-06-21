package il.co.ilrd.reviews.lidanthreadpool;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class WaitableQueue<E> {
    private static final int DEFAULT_INIT_CAPACITIY = 16;
    Lock lock = new ReentrantLock();
    Condition cv = lock.newCondition();
    private PriorityQueue<E> queue;

    public WaitableQueue(){
        this(DEFAULT_INIT_CAPACITIY);
    }

    public WaitableQueue(int initCapacity){
        queue = new PriorityQueue<>(initCapacity);
    }

    public WaitableQueue(Comparator<? super E> comparator){
        this(DEFAULT_INIT_CAPACITIY, comparator);
    }

    public WaitableQueue(int initCapacity, Comparator<? super E> comparator){
        queue = new PriorityQueue<>(initCapacity, comparator);
    }

    public int size(){
        lock.lock();
        int currentSize = queue.size();
        lock.unlock();

        return currentSize;
    }

    public boolean isEmpty(){
        lock.lock();
        boolean isEmpty = queue.isEmpty();
        lock.unlock();

        return isEmpty;
    }

    public void enqueue(E e){
        lock.lock();
        queue.add(e);
        cv.signal();
        lock.unlock();
    }

    public E dequeue() throws InterruptedException{
        lock.lockInterruptibly();
        while (queue.isEmpty())
            cv.await();

        E dequeued = queue.poll();
        lock.unlock();

        return dequeued;
    }

    public E dequeue(long millis) throws InterruptedException{
        return dequeue(millis, TimeUnit.MILLISECONDS);
    }

    public E dequeue(long time, TimeUnit unit) throws InterruptedException{
        lock.lockInterruptibly();
        while (queue.isEmpty())
            if (!cv.await(time, unit)) break;

        E dequeued = queue.poll();
        lock.unlock();

        return dequeued;
    }

    public boolean remove (E e){
        lock.lock();
        boolean isRemoved = queue.remove(e);
        lock.unlock();

        return isRemoved;
    }

    public static void main(String[] args) {
        WaitableQueue<String> wq = new WaitableQueue<>();

        try {
            System.out.println(wq.dequeue(3000));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
