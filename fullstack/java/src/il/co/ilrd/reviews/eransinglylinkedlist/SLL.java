package il.co.ilrd.reviews.eransinglylinkedlist;/*version number 0.1,
    4.12.2019, 19:00*/

public class SLL {

    static private SLLNode head = new SLLNode(null, null);

	private class SLLIter implements Iterator {

		SLLNode currentNode = head;

		/**
		 * @return returns the data at current place in list, and advances.
		 * after last item - returns null.
		 */
		@Override

        public Object next() {
        	if (hasNext()) {
        		final Object returnObject = currentNode.data;
        		currentNode = currentNode.next;
        		return returnObject;	
        	}
        	else {
        		return null;
        	}
        }

		/**
		 *
		 * @return returns true if item is not last item.
		 */
        @Override
        public boolean hasNext() {
			return null != currentNode.next;
		}

		/**
		 *
		 * @return allows item data to be retrieved.
		 */
		private Object getData() {
			return currentNode.data;
        }
    }

    static private class SLLNode {  

        private final Object data;
        private SLLNode next;

		/**
		 *
		 * @param dataToInsert this is the data stored in item.
		 * @param next reference to the next item in list.
		 */
        SLLNode(Object dataToInsert, SLLNode next){
        	data = dataToInsert;
        	this.next = next;
        }
    }

	/**
	 *
	 * @param dataToInsert this is the data to be inserted into list.
	 */
	public void pushFront(Object dataToInsert) {
		head = new SLLNode(dataToInsert, head);
    }

	/**
	 *
	 * @return removes first item from list and returns the data.
	 * if list is empty returns null.
	 */
	public Object popFront() {
    	if (isEmpty()) {
    		return null;
    	}
    	
    	final Object retObj = head.data;
    	head = head.next;
    	
    	return retObj;
    }

	/**
	 *
	 * @return returns the number of items in the list.
	 */
    public int size()
    {
    	int counter = 0;
    	final Iterator iter = iterator();
    	
    	while (iter.hasNext())
    	{
    		iter.next();
    		counter++;
    	}
    	return counter;
    }

	/**
	 *
	 * @return returns true if list empty or false if not.
	 */
    public boolean isEmpty()
    {
    	return (head.next == null);
    }

	/**
	 *
	 * @param findData data to be found in list.
	 * @return iterator containing the data. if non found - return null.
	 */
	public Iterator find(Object findData) {
    	final SLLIter iter = new SLLIter();
    	
    	while (iter.hasNext()) {
    		if (iter.getData().equals(findData)) {
    			return iter;
    		}
    		iter.next();
    	}
    	return null;
    }

	/**
	 *
	 * @return returns iterator holding item in list.
	 */
	public Iterator iterator() {
		return new SLLIter();
    }

}