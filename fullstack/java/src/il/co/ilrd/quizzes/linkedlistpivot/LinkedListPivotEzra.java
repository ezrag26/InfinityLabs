package il.co.ilrd.quizzes.linkedlistpivot;

import il.co.ilrd.singlylinkedlist.Iterator;
import il.co.ilrd.singlylinkedlist.SLL;

public class LinkedListPivotEzra extends SLL {

	public LinkedListPivotEzra() {}

	public LinkedListPivotEzra arrangeToPivot(int pivot) {
		Iterator i = this.iterator();
		SLL sll2 = new SLL();
		SLL sll3 = new SLL();

		while (i.hasNext()) {
			int data = (int)i.next();
			this.popFront();

			if (data >= pivot) {
				sll2.pushFront(data);
			} else {
				sll3.pushFront(data);
			}
		}

		i = sll2.iterator();
		while (i.hasNext()) {
			Object data = i.next();
			this.pushFront(data);
		}

		i = sll3.iterator();
		while (i.hasNext()) {
			Object data = i.next();
			this.pushFront(data);
		}

		return this;
	}
}
