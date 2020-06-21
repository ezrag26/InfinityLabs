package il.co.ilrd.worksheets.ws9.boundedunboundedtest;

import java.util.ArrayList;
import java.util.List;

public class BoundedUnboundedTest {

	public static void main(String[] args) {
		List<Object> listOfListOfObject = new ArrayList<>();
		List<String> listOfString = new ArrayList<>();
		List<?> listOfWildcard = new ArrayList<>();

		List someList = new ArrayList();
		/*someList.add(1);
		System.out.println(listOfString.add(someList.get(0)));*/ // runtime error Object can't be converted to String

		listOfString.add("Hello");
		/*listOfWildcard.add("Hello");*/    /* not ok: can only receive null */
		listOfWildcard.add(null);       /* ok: can only receive null */
		listOfListOfObject.add(Integer.valueOf(1));

		someFunc(listOfString);
		someFunc2(listOfString, "Hi");
	}

	static void someFunc(List<?> list) {
//		list.add(1);
	}

	static <T> void someFunc2(List<T> list, T i) {
		list.add(i);
	}
}
