/*
 * @author TG
 * WaitableQueue.
 */
package il.co.ilrd.randomtests.tomwaitablequeue;

import java.util.Comparator;
import java.util.Objects;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class WaitableQueue<E> {

    private Queue<E> queue;
    private static final int DEFAULT_INITIAL_CAPACITY = 16;

    private final Lock lock = new ReentrantLock(true);
    private Condition condition = lock.newCondition();

    /**
     * ctor which creates an WaitableQueue with the default capacity (16), that compared according to Comparable natural ordering.
     */
    public WaitableQueue() {
        this(DEFAULT_INITIAL_CAPACITY);
    }

    /**
     * ctor which creates an WaitableQueue with specified initial capacity, that compared according to Comparable natural ordering. initcapacity must be greather than 0.
     */
    public WaitableQueue(int initcapacity) {

        queue = new PriorityQueue<>(initcapacity);
    }

    /**
     * ctor which creates an WaitableQueue with specified initial capacity, that compared according to Comparable natural ordering.
     *
     * @param initcapacity, specified initial capacity.
     * @param comparator    the compared is according to Comparator - not by natural ordering
     */


    public WaitableQueue(int initcapacity, Comparator<? super E> comparator) {
        queue = new PriorityQueue<>(initcapacity, Objects.requireNonNull(comparator));
    }

    /**
     * @return Returns the number of elements in this collection.
     * @throws InterruptedException if the current thread is interrupted while acquiring the lock
     */
    public int size() throws InterruptedException {
        lock.lockInterruptibly();
        int size = queue.size();
        lock.unlock();
        return size;
    }

    /**
     * @return Returns true if this PriorityQueue has no elements, otherwise return false.
     * @throws InterruptedException if the current thread is interrupted while acquiring the lock
     */
    public boolean isEmpty() {
//

        boolean isEmpty = queue.isEmpty();

        return isEmpty;
    }

    /**
     * @param e insert the element (e) into the queue.
     * @throws InterruptedException if the current thread is interrupted while acquiring the lock.
     */

    public void enqueue(E e) throws InterruptedException {
        lock.lockInterruptibly();
        queue.add(e);
        condition.signal();
        lock.unlock();
    }


    /**
     * Retrieves and removes the head of this queue, waiting if necessary until an element becomes available.
     *
     * @return the head of this queue.
     * @throws InterruptedException if the current thread is interrupted while acquiring the lock.
     */
    public E dequeue() throws InterruptedException {

        lock.lockInterruptibly();
        E poll_return = null;

        while (queue.isEmpty()) {
            condition.await();

            poll_return = queue.poll();
        }
        lock.unlock();

        return poll_return;
    }

    /**
     * @param time unit durations at a given unit of granularity.
     * @param time to wait before return.
     * @return the head of this queue, or null if the specified waiting time elapses before an element is available.
     * @throws InterruptedException if the current thread is interrupted while acquiring the lock.
     */
    public E dequeue(TimeUnit unit, long time) throws InterruptedException {
        E poll_return;
        try {
            lock.lockInterruptibly();

            while (queue.isEmpty()) {
                if (!condition.await(time, unit)) {
                    return null;
                }
            }

             poll_return = queue.poll();
        }
    finally{
            lock.unlock();
        }
        return poll_return;
    }

    /**
     * Removes a single instance of the specified element from this queue, if it is present.
     *
     * @param e element to be removed from this queue.
     * @return true if a change has been made to the queue, otherwise false.
     * @throws InterruptedException if the current thread is interrupted while acquiring the lock.
     */
    public boolean remove(E e) throws InterruptedException {

        boolean remove_return;

        lock.lockInterruptibly();

        remove_return = queue.remove(e);
        lock.unlock();

        return remove_return;
    }
}
