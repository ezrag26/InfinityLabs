package il.co.ilrd.worksheets.ws10;

import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Ex1 {
	public static void main(String[] args) {
		Ex1();

		Ex2();

	}

	public static void Ex1() {
		int[] primitives = {1, 3, 2, 10, 5};
		System.out.println(Arrays.toString(primitives));
		/* create a stream of the array, wrap as Integer, sort them, and make into a list */
		List<Integer> list = Arrays.stream(primitives).boxed().sorted().collect(Collectors.toList());
		System.out.println(Arrays.toString(list.toArray()));
	}

	public static void Ex2() {
		Map<String, Integer> daysOfWeek = new HashMap<>();
		String[] days = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
		for (int i = 0; i < 7; ++i) {
			daysOfWeek.put(days[i], i + 1);
		}

		for (Map.Entry<String, Integer> entry : daysOfWeek.entrySet()) {
			System.out.println(entry.getKey());
		}

		for (Map.Entry<String, Integer> entry : daysOfWeek.entrySet()) {
			System.out.println(entry.getValue());
		}
	}
}
