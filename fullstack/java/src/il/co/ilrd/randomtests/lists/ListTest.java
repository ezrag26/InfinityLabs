package il.co.ilrd.randomtests.lists;

import java.util.ArrayList;
import java.util.List;

public class ListTest {
	public static void main(String[] args) {
		List<Number> list = new ArrayList<>();
		list.add(3); // why does this work?
		list.add(3.0); // why does this work?
		System.out.println(list.get(0));
		System.out.println(list.get(1));
		Integer integer = (Integer)list.get(0);
		Double string = (Double)list.get(1);

		doThis(list);

	}

	static <T extends Object> void doThis(List<T> list) {

	}

}
