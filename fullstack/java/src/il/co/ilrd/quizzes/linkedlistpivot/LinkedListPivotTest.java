package il.co.ilrd.quizzes.linkedlistpivot;

import org.junit.jupiter.api.Test;
import il.co.ilrd.singlylinkedlist.Iterator;

class LinkedListPivotTest {
	@Test
	public void testLinkedListPivot() {
		int[] data = {3, 7, 1, 4, 8, 2, 4, 9, 2, 5, 8, 10, -2, 6, -1, 8, 3};
		int pivot = 4;
		int smallerThanPivot = 0;
		int greaterThanPivot = 0;

		LinkedListPivotEzra sll = new LinkedListPivotEzra();

		for (int i = 0; i < data.length; ++i) {
			if (data[i] < pivot) {
				++smallerThanPivot;
			} else {
				++greaterThanPivot;
			}
		}

		for (int datum : data) {
			sll.pushFront(datum);
		}

		sll = sll.arrangeToPivot(pivot);

		Iterator iter = sll.iterator();
		for (int i = 0; i < smallerThanPivot; ++i) {
			int ret = (int)iter.next();
			if (ret >= pivot) {
				System.out.println("Index " + i + " Below Returned " + ret);
			}
		}

		for (int i = 0; i < greaterThanPivot; ++i) {
			int ret = (int)iter.next();
			if (ret < pivot) {
				System.out.println("Index " + i + " - Above Returned " + ret);
			}
		}
	}
}