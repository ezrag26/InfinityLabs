package il.co.ilrd.singlylinkedlist;

/**
 * 
 * @author  Ezra Gordon
 * @version 1.2, 12/10/2019
 */

public class SLL {

	private SLLNode head = null;

	static private class SLLNode {

		private final Object data;
		private SLLNode next;

		private SLLNode(Object data, SLLNode next) {
			this.data = data;
			this.next = next;
		}
	}

	private static class SLLIter implements Iterator {

		private SLLNode currentNode = null;

		/**
		 * Class constructor setting currentNode
		 * 
		 * @param currentNode the node for which to receive the iterator
		 */
		SLLIter(SLLNode currentNode) {
			this.currentNode = currentNode;
		}

		/**
		* Increments the current iterator to the next
		* 
		* @return 	data of the iterator that called next(), or null if the
		* iterator is passed the last item
		*/
		@Override
		public Object next() {
			if (null == currentNode) return null;		 /* no more items */
			
			final Object retData = currentNode.data;		/* data to return */
			currentNode = currentNode.next;			/* increment to next node */

			return retData;
		}

		/**
		* Checks if the iterator will return data if it calls next()
		* 
		* @return true if the iterator will return data if it calls next, 
		* false if not
		*/
		@Override
		public boolean hasNext() {
			return (currentNode != null);
		}
	}

	private SLLIter getSLLIter(SLLNode node) {
		return new SLLIter(node);
	}

	/**
	* Adds an element to the front of the SLL object
	* 
	* @param data data to add to the SLL
	*/
	public void pushFront(Object data) {

		this.head = new SLLNode(data, this.head);
	}

	/**
	* Removes the front element of an SLL object
	* 
	* @return reference to the removed element, or null if the SLL is empty
	*/
	public Object popFront() {
		if (this.isEmpty()) return null;						 /* empty SLL */

		/* save data to return and increment head to next node */
		final Object retData = this.head.data;
		this.head = this.head.next;

		return retData;
	}

	/**
	* Calculates the number of items in an SLL object
	* 
	* @return number of items in the SLL
	*/
	public int size() {
		final SLLIter i = this.getSLLIter(this.head);
		int size = 0;

		while (i.hasNext()) {
			++size;
			i.next();
		}

		return size;
	}

	/**
	* Checks if an SLL object is empty
	* 
	* @return true if SLL is empty, false if not empty
	*/
	public boolean isEmpty() {
		return (null == head);
	}

	/**
	* Finds the given data of an SLL object
	* 
	* @param  data data to find
	* @return Iterator to the data found, null if data is not found
	*/
	public Iterator find(Object data) {
		final SLLIter i = this.getSLLIter(this.head);

		while (i.hasNext()) {
			SLLNode node = i.currentNode;	/* save node in case it's a match */

			/* found a match */
			if (data.equals(i.next())) {
				return this.getSLLIter(node);	/* iterator to the node found */
			}
		}

		return null;
	}

	/**
	* Gets the iterator to the head of an SLL object
	* 
	* @return iterator to the head of an SLL object
	*/
	public Iterator iterator() {
		return this.getSLLIter(this.head);
	}

}

