package il.co.ilrd.reviews.shirwaitablequeue;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class WaitableQueue<E> {
    private Queue<E> queue;
    private Lock lock = new ReentrantLock();
    private Condition notEmpty = lock.newCondition();

    /**
     * Creates a {@code WaitableQueue} with the default initial
     * capacity (11) that orders its elements according to their
     * {@linkplain Comparable natural ordering}.
     */
    public WaitableQueue() {
        queue = new PriorityQueue<>();
    }

    /**
     * Creates a {@code WaitableQueue} with the specified initial
     * capacity that orders its elements according to their
     * {@linkplain Comparable natural ordering}.
     *
     * @param initialCapacity the initial capacity for this waitable queue
     * @throws IllegalArgumentException if {@code initialCapacity} is less
     * than 1
     */
    public WaitableQueue(int initialCapacity) {
        this(initialCapacity, null);
    }

    /**
     * Creates a {@code WaitableQueue} with the default initial capacity and
     * whose elements are ordered according to the specified comparator.
     *
     * @param  comparator the comparator that will be used to order this
     * waitable queue.  If {@code null}, the {@linkplain Comparable
     * natural ordering} of the elements will be used.
     */
    public WaitableQueue(Comparator<? super E> comparator) {
        queue = new PriorityQueue<>(comparator);
    }

    /**
     * Creates a {@code WaitableQueue} with the specified initial capacity
     * that orders its elements according to the specified comparator.
     *
     * @param  initialCapacity the initial capacity for this waitable queue
     * @param  comparator the comparator that will be used to order this
     * priority queue.  If {@code null}, the {@linkplain Comparable
     * natural ordering} of the elements will be used.
     * @throws IllegalArgumentException if {@code initialCapacity} is
     * less than 1
     */
    public WaitableQueue(int initialCapacity, Comparator<? super E> comparator) {
        queue = new PriorityQueue<>(initialCapacity, comparator);
    }


    /**
     * Returns the number of elements in this queue.
     *
     * @return Returns the number of elements in this queue
     * @throws InterruptedException if the current thread is interrupted
     * while acquiring the lock (and interruption of lock acquisition
     * is supported)
     */
    public int size() throws InterruptedException {
        lock.lockInterruptibly();
        int size = queue.size();
        lock.unlock();
        return size;
    }

    /**
     * Returns {@code true} if this queue contains no elements otherwise false.
     *
     * @return {@code true} if this deque contains no elements otherwise false.
     * @throws InterruptedException if the current thread is interrupted
     * while acquiring the lock (and interruption of lock acquisition
     * is supported)
     */
    public boolean isEmpty() throws InterruptedException {
        lock.lockInterruptibly();
        boolean isEmpty = queue.isEmpty();
        lock.unlock();
        return isEmpty;
    }

    /**
     * Inserts the specified element into this waitable queue.
     *
     * @throws ClassCastException if the specified element cannot be
     * compared with elements currently in this waitable priority queue
     * according to the waitable queue's ordering
     * @throws NullPointerException if the specified element is null
     * @throws InterruptedException if the current thread is interrupted
     * while acquiring the lock (and interruption of lock acquisition
     * is supported)
     */
    public void enqueue(E e) throws InterruptedException {
        lock.lockInterruptibly();
        queue.add(e);
        notEmpty.signal(); //notify the consumer that there is data available.
        lock.unlock();

    }

    /**
     * Removes the head of this queue and returns the element.
     *
     * @return the head of this queue
     * @throws InterruptedException if the current thread is interrupted
     * while acquiring the lock (and interruption of lock acquisition
     * is supported)
     */
    public E dequeue() throws InterruptedException {
        lock.lockInterruptibly();
        while (queue.isEmpty()) notEmpty.await();
        E ret = queue.remove();
        lock.unlock();
        return ret;
    }

    /**
     * Removes the head of this queue and returns the element or null if
     * the waiting time elapsed.
     *
     * @param time the maximum time to wait
     * @param unit the time unit of the {@code time} argument
     * @return the head of this queue or null if the waiting time elapsed.
     * @throws InterruptedException if the current thread is interrupted
     * while acquiring the lock (and interruption of lock acquisition
     * is supported)
     */
    public E dequeue(long time, TimeUnit unit) throws InterruptedException {
        long restTime = unit.toNanos(time);

        lock.lockInterruptibly();
        while (queue.isEmpty()) {
            restTime = notEmpty.awaitNanos(restTime);

            if (restTime <= 0) {
                lock.unlock();
                return null;
            }
        }

        E ret = queue.remove();
        lock.unlock();
        return ret;
    }


    /**
     * Removes a single instance of the specified element from this queue,
     * if it is present.  More formally, removes an element {@code e} such
     * that {@code o.equals(e)}, if this queue contains one or more such
     * elements.  Returns {@code true} if and only if this queue contained
     * the specified element.
     *
     * @param e element to be removed from this queue.
     * @return {@code true} if this queue changed as a result of the call
     * @throws InterruptedException if the current thread is interrupted
     * while acquiring the lock (and interruption of lock acquisition
     * is supported)
     */
    public boolean remove (E e) throws InterruptedException {
        lock.lockInterruptibly();
        boolean ret = queue.remove(e);
        lock.unlock();
        return ret;
    }

}
