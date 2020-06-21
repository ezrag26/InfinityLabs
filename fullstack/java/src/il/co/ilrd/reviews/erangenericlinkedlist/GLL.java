package il.co.ilrd.reviews.erangenericlinkedlist;


import java.util.*;

public class GLL<E> implements Iterable<E>{
    private GLLNode<E> head;
    private int modCount;

    /**
     * Nodes that are stored within the list. Each node has data and a reference to next node.
     * @param <T> the type parameter that is stored within the generic linked list node
     */
    private static class GLLNode<T> {
        private T data;
        private GLLNode<T> next;

        /**
         * Node Ctor
         * @param data the data to be stored in node.
         * @param next the reference to the next node.
         */
        private GLLNode(T data, GLLNode<T> next) {
            this.data = data;
            this.next = next;
        }
    }

    /**
     * The Generic linked list accepts data of the type specified by E, if not - a compile error will occur.
     * The linked list implements Iterator to allow list traversal.
     * @param <E>the type of data stored within node of the linked list
     */
    private static class GLLIter<E> implements Iterator<E> {
        private GLLNode<E> currentNode;
        private int modCounter;
        GLL<E> list;

        /**
         * The Iterator holds a reference to one node each time, this reference can change.
         * @param gll the list on which the Iterator will operate on.
         */
        public GLLIter(GLL<E> gll) {
            currentNode = gll.head;
            modCounter = gll.modCount;
            list = gll;
        }

        /**
         *
         * @return Checks if next next() will return a value.
         */
        @Override
        public boolean hasNext() {
            if (modCounter != list.modCount) {
                throw new ConcurrentModificationException("iterator is no longer valid");
            }
            return currentNode != null;
        }

        /**
         *
         * @return Returns the data stored by the node currently in Iterator.
         */
        @Override
        public E next() {
            if (modCounter != list.modCount) {
                throw new ConcurrentModificationException("iterator is no longer valid");
            }

            if(!this.hasNext()) { throw new NoSuchElementException("no more elements"); }
            E retE = currentNode.data;
            currentNode = currentNode.next;

            return retE;
        }

        /**
         *
         * @return returns the data from a node. only relevant to Iterator.
         */
        private E getData() {
            return currentNode.data;
        }
    }

    /**
     * FLL Ctor.
     */
    public GLL() {
        head = null;
        modCount = 0;
    }

    /**
     * Create node with given data and push to front of list.
     * @param data data to be stored in list.
     */
    public void pushFront(E data) {
        this.head = new GLLNode<>(data, this.head);
        ++modCount;
    }

    /**
     * Removes node from front of list, and return the data stored within it.
     * @return returns data stored in removed node.
     */
    public E popFront() {
        if (this.isEmpty()) {
            throw new NoSuchElementException("no such element exists)");
        }

        E retData = this.head.data;
        this.head = this.head.next;
        ++modCount;

        return retData;
    }

    /**
     *
     * @return length of linked list. Int.
     */
    public int size() {
        int counter = 0;
        Iterator<E> iter = iterator();
        while (iter.hasNext()) {
            iter.next();
            ++counter;
        }
        return counter;
    }

    /**
     *
     * @return if list is empty or not. Boolean.
     */
    public boolean isEmpty() {
        return this.head == null;
    }

    /**
     *
     * @return returns an Iterator to first element of given list.
     */
    @Override
    public Iterator<E> iterator() {
        return new GLLIter<>(this);
    }

    /**
     * Finds occurrence of data within Linked List. Returns an Iterator containing the node.
     * @param data the data to be found.
     * @return the iterator with the node containing the data. null if not found.
     */
    public Iterator<E> find(E data) {
        GLLIter<E> retIter = new GLLIter<>(this);
        E testData;
        while (retIter.hasNext()) {
            testData = retIter.getData();
            if (testData.equals(data)) {
                return retIter;
            }
            retIter.next();
        }
        return null;
    }

    /**
     * Merges to lists into a new list. Lists will appear one after the other in reverse order.
     * Does not modify given lists.
     * @param list1
     * @param list2
     * @param <E> the type that the lists given must implement - must be identical in both.
     * @return returns new list, merged product of both given lists.
     */
    public static <E> GLL<E> merge(GLL<E> list1, GLL<E> list2) {
        Iterator<E> gll1 = new GLLIter<>(list1);
        GLL<E> newGLL = new GLL<>();

        while (gll1.hasNext()) {
            newGLL.pushFront(gll1.next());
        }
        gll1 = new GLLIter<>(list2);
        while (gll1.hasNext()) {
            newGLL.pushFront(gll1.next());
        }

        return newGLL;
    }

    /**
     * Receives a Generic Linked list, returns a new list in the reversed order of given list.
     * Does not modify given list.
     * @param list
     * @param <E> The type that the given list contains.
     * @return New reversed list.
     */
    public static <E> GLL<E> reverse(GLL<E> list) {
        GLL<E> newGLL = new GLL<>();
        Iterator<E> revIter = list.iterator();
        while (revIter.hasNext()) {
            newGLL.pushFront(revIter.next());
        }

        return newGLL;
    }

    /**
     * Prints all items in given list.
     * @param list
     * @param <E> The type that the given list contains
     */
    public static <E> void print(GLL<E> list) {
        Iterator<E> gllIter = list.iterator();
        while (gllIter.hasNext()) {
            System.out.println(gllIter.next());
        }
    }

    /**
     * Merges and sorts two lists, returns new list.
     * Does not alter given lists.
     * @param list1
     * @param list2
     * @param <E> the type that the lists given must implement - must be identical in both.
     * @return New list that is the merged and sorted product of the two given lists.
     */
    public static <E extends Comparable<E>> GLL<E> advMerge(GLL<E> list1, GLL<E> list2) {
        List<E> list = new ArrayList<>();
        Iterator<E> iter = list1.iterator();
        while(iter.hasNext()) {
            list.add(iter.next());
        }

        iter = list2.iterator();
        while(iter.hasNext()) {
            list.add(iter.next());
        }

        Collections.sort(list);

        GLL<E> merged = new GLL<>();
        for(E e : list) {
            merged.pushFront(e);
        }
        return merged;
    }
}
