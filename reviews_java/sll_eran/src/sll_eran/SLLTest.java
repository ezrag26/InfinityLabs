package sll_eran;

public class SLLTest {
	public static void main(String[] args) {

		int failures = 0;

		System.out.println("Testing pushFront......");
		failures += SLLTest.testPushFront();
		System.out.println("Testing popFront...");
		failures += SLLTest.testPopFront();
		System.out.println("Testing size...");
		failures += SLLTest.testSize();
		System.out.println("Testing isEmpty...");
		failures += SLLTest.testIsEmpty();
		System.out.println("Testing findTrue...");
		failures += SLLTest.testFindTrue();
		System.out.println("Testing findFalse...");
		failures += SLLTest.testFindFalse();
		System.out.println("Testing iterator...");
		failures += SLLTest.testIterator();

		if (failures != 0) {
			System.out.println(failures + " failures");
		}
		else {
			System.out.println("All tests passed.");
		}
	}

	public static int testPushFront() {
		SLL sll = new SLL();
		int[] data = {1, 8, 3, 9, 5};
		int size = 0;
		int ret;
		int failures = 0;

		if (size != (ret = sll.size())) {
			System.out.println("\tExpected: " + size);
			System.out.println("\tReturned: " + ret);
			++failures;
		}

		++size;
		for (int i = 0; i < data.length; ++i, ++size) {

			sll.pushFront(data[i]);

			if (size != (ret = sll.size())) {
				System.out.println("\ti: " + i);
				System.out.println("\tExpected: " + size);
				System.out.println("\tReturned: " + ret);
				++failures;
			}
		}

		Iterator iter = sll.iterator();

		for (int i = (data.length - 1); i >= 0; --i) {
			if (data[i] != (ret = (int) iter.next())) {
				System.out.println("\tExpected: " + data[i]);
				System.out.println("\tReturned: " + ret);
				++failures;
			}
		}

		return failures;
	}

	public static int testPopFront() {
		SLL sll = new SLL();
		int[] data = {1, 8, 3, 9, 5};
		int ret;
		int failures = 0;

		for (int i = 0; i < data.length; ++i) {
			sll.pushFront(data[i]);
		}

		for (int i = (data.length - 1); i >= 0; --i) {
			if (data[i] != (ret = (int) sll.popFront())) {
				System.out.println("\tExpected: " + data[i]);
				System.out.println("\tReturned: " + ret);
				++failures;
			}
		}

		return failures;
	}

	public static int testSize() {
		SLL sll = new SLL();
		int[] data = {1, 8, 3, 9, 5};
		int size = 0;
		int ret;
		int failures = 0;

		if (size != (ret = sll.size())) {
			System.out.println("\tExpected: " + size);
			System.out.println("\tReturned: " + ret);
			++failures;
		}

		++size;
		for (int i = 0; i < data.length; ++i, ++size) {

			sll.pushFront(data[i]);

			if (size != (ret = sll.size())) {
				System.out.println("\ti: " + i);
				System.out.println("\tExpected: " + size);
				System.out.println("\tReturned: " + ret);
				++failures;
			}
		}

		--size;
		for (int i = (data.length - 1); i >= 0; --i) {

			sll.popFront();

			if (--size != (ret = sll.size())) {
				System.out.println("\ti: " + i);
				System.out.println("\tExpected: " + size);
				System.out.println("\tReturned: " + ret);
				++failures;
			}
		}

		return failures;
	}

	public static int testIsEmpty() {
		SLL sll = new SLL();
		int[] data = {1, 8, 3, 9, 5};
		boolean ret;
		int failures = 0;

		if (true != (ret = sll.isEmpty())) {
			System.out.println("\tExpected: " + true);
			System.out.println("\tReturned: " + ret);
			++failures;
		}

		for (int i = 0; i < data.length; ++i) {

			sll.pushFront(data[i]);

			if (false != (ret = sll.isEmpty())) {
				System.out.println("\ti: " + i);
				System.out.println("\tExpected: " + false);
				System.out.println("\tReturned: " + ret);
				++failures;
			}
		}

		for (int i = 0; i < data.length; ++i) {

			if (false != (ret = sll.isEmpty())) {
				System.out.println("\ti: " + i);
				System.out.println("\tExpected: " + false);
				System.out.println("\tReturned: " + ret);
				++failures;
			}

			sll.popFront();
		}

		if (true != (ret = sll.isEmpty())) {
			System.out.println("\tExpected: " + true);
			System.out.println("\tReturned: " + ret);
			++failures;
		}

		return failures;
	}

	public static int testFindTrue() {
		SLL sll = new SLL();
		int[] data = {1, 8, 3, 9, 5};
		int[] find = {8, 5, 1, 9, 3};
		Iterator ret;
		int failures = 0;

		for (int i = 0; i < data.length; ++i) {

			sll.pushFront(data[i]);

		}

		for (int i = 0; i < data.length; ++i) {

			if (null == (ret = sll.find(find[i]))) {
				System.out.println("\ti: " + i);
				System.out.println("\tExpected: " + false);
				System.out.println("\tReturned: " + ret);
				++failures;
			}
		}

		return failures;
	}

	public static int testFindFalse() {
		SLL sll = new SLL();
		int[] data = {1, 8, 3, 9, 5};
		int[] find = {0, -1, 7, 20, 6};
		Iterator ret;
		int failures = 0;

		for (int i = 0; i < data.length; ++i) {

			sll.pushFront(data[i]);

		}

		for (int i = 0; i < data.length; ++i) {

			if (null != (ret = sll.find(find[i]))) {
				System.out.println("\ti: " + i);
				System.out.println("\tExpected: " + null);
				System.out.println("\tReturned: " + ret);
				++failures;
			}
		}

		return failures;
	}

	public static int testIterator() {
		SLL sll = new SLL();
		int[] data = {1, 8, 3, 9, 5};
		Iterator iterReturn;
		int failures = 0;

		if (false != (iterReturn = sll.iterator()).hasNext())
		{
			System.out.println("\tExpected: " + false);
			System.out.println("\tReturned: " + iterReturn.hasNext());
			++failures;
		}

		for (int i = 0; i < data.length; ++i) {
			sll.pushFront(data[i]);

			if (true != (iterReturn = sll.iterator()).hasNext())
			{
				System.out.println("\tExpected: " + true);
				System.out.println("\tReturned: " + iterReturn.hasNext());
				++failures;
			}
		}

		for (int i = 0; i < data.length; ++i) {

			if (true != (iterReturn = sll.iterator()).hasNext())
			{
				System.out.println("\tExpected: " + true);
				System.out.println("\tReturned: " + iterReturn.hasNext());
				++failures;
			}

			sll.popFront();
		}

		if (false != (iterReturn = sll.iterator()).hasNext())
		{
			System.out.println("\tExpected: " + false);
			System.out.println("\tReturned: " + iterReturn.hasNext());
			++failures;
		}

		return failures;
	}
}
