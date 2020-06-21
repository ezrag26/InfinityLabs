package il.co.ilrd.waitablequeue;

import java.util.Comparator;
import java.util.Objects;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class WaitableQueue<E> {
    private static final int DEFAULT_CAPACITY = 16;
    private Queue<E> pq;
    private Lock lock = new ReentrantLock();
    private Condition notEmpty = lock.newCondition();

    /**
     * Creates a WaitableQueue with the default capacity
     */
    public WaitableQueue() {
        this(DEFAULT_CAPACITY, null);
    }

    /**
     * Creates a WaitableQueue with the given initial capacity
     *
     * @param initCapacity the initial capacity for this WaitableQueue
     *
     * @throws IllegalArgumentException if initCapacity is less than 1
     */
    public WaitableQueue(int initCapacity) {
        this(initCapacity, null);
    }

    /**
     * Creates a WaitableQueue with the given initial capacity and Comparator
     *
     * @param initCapacity the initial capacity for this WaitableQueue
     * @param comparator the comparator used to prioritize this WaitableQueue.
     *                   If {@code null} the Comparable natural ordering of the
     *                   elements will be used.
     *
     * @throws IllegalArgumentException if initCapacity is less than 1
     */
    public WaitableQueue(int initCapacity, Comparator<? super E> comparator) {
        pq = new PriorityQueue<>(initCapacity, comparator);
    }

    /**
     * Synchronously counts the number of elements in this queue.
     *
     * @return the number of elements in this queue
     *
     * @throws InterruptedException if the current thread is interrupted while
     * acquiring the lock
     */
    public int size() {
        lock.lock();       /* gain control     */
        int size = pq.size();
        lock.unlock();                  /* release control  */

        return size;
    }

    /**
     * Synchronously checks if this queue is empty
     *
     * @return {@code true} if this queue is empty and {@code false} if not
     *
     * @throws InterruptedException if the current thread is interrupted while
     * acquiring the lock
     */
    public boolean isEmpty() {
        lock.lock();       /* gain control     */
        boolean isEmpty = pq.isEmpty();
        lock.unlock();                  /* release control  */

        return isEmpty;
    }

    /**
     * Synchronously adds an element to this queue
     *
     * @param e the element to be added to this queue
     *
     * @throws IllegalStateException if the element cannot be added at this
     * time due to capacity restrictions
     * @throws ClassCastException if the class of the specified element
     * prevents it from being added to this queue
     * @throws NullPointerException if the specified element is null
     * @throws IllegalArgumentException if some property of this element
     * prevents it from being added to this queue
     * @throws InterruptedException if the current thread is interrupted while
     * acquiring the lock
     */
    public void enqueue(E e) {
        Objects.requireNonNull(e);

        lock.lock();       /* gain control     */

        try {
            pq.add(e);
            notEmpty.signal();          /* signal that the queue is not empty */
        } finally {
            lock.unlock();              /* release control  */
        }

    }

    /**
     * Synchronously removes the highest priority element specified by the given
     * Comparator or its natural ordering if no Comparator was provided upon
     * this queue's creation
     *
     * @return the highest priority element of this queue
     *
     * @throws InterruptedException if the current thread is interrupted while
     * acquiring the lock
     */
    public E dequeue() throws InterruptedException {
        lock.lockInterruptibly();       /* gain control     */

        /* wait for signal that queue is not empty */
        while (isEmpty()) { notEmpty.await(); }

        try {
            return pq.remove();
        } finally {
            lock.unlock();              /* release control  */
        }
    }

    /**
     * Synchronously removes the highest priority element specified by the given
     * Comparator or its natural ordering if no Comparator was provided upon
     * this queue's creation.
     *
     * When the current thread acquires the lock, if this queue is empty, the
     * thread will wait up until the specified time * unit for it to become
     * not empty. If it passes that time, the thread will wakeup and return
     * immediately without removing an element.
     *
     * @param time the maximum time to wait
     * @param unit the time unit of the {@code time} argument
     * @return the highest priority element of this queue or {@code null} if
     * the specified time has elapsed
     *
     * @throws NullPointerException if the unit specified is null
     * @throws InterruptedException if the current thread is interrupted while
     * acquiring the lock
     */
    public E dequeue(long time, TimeUnit unit) throws InterruptedException {
        Objects.requireNonNull(unit);

        long waitTimeLeft = unit.toNanos(time);

        lock.lockInterruptibly();       /* gain control     */
        while (isEmpty()) { /* in case of a spurious wakeup */
            /* time elapsed */
            if ((waitTimeLeft = notEmpty.awaitNanos(waitTimeLeft)) <= 0) {
                lock.unlock();          /* release control  */
                return null;
            }
        }

        try {
            return pq.remove();
        } finally {
            lock.unlock();              /* release control  */
        }

    }

    /**
     * Synchronously removes the specified element from this queue.
     *
     * @param e the element to be removed
     * @return {@code true} if the element was succesfully removed and
     * {@code false} if not
     *
     * @throws NullPointerException if the element is null
     * @throws ClassCastException if the type of the specified element
     * is incompatible with this collection
     * @throws InterruptedException if the current thread is interrupted while
     * acquiring the lock
     */
    public boolean remove (E e) {
        Objects.requireNonNull(e);

        lock.lock();       /* gain control     */

        try {
            return pq.remove(e);
        } finally {
            lock.unlock();              /* release control  */
        }

    }

}
