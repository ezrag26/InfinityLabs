package il.co.ilrd.quizzes.sortoddleaveeven;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class SortOddsLeaveEvens {
	public static void main(String[] args) {
		int[][] arrs = {{5, 3, 2, 8, 1, 4}, {}, {3}, {5, 2, 8, 3, 0, 1, 5, 2}};

		for (int i = 0; i < arrs.length; ++i) {

			System.out.println(Arrays.toString(sortArray(arrs[i])));
		}
	}

	public static int[] sortArray(int[] arr) {
		if (arr.length <= 1) return arr;
		List<List<Integer>> list = new ArrayList<>();
		list.add(new ArrayList<>());
		list.add(new ArrayList<>());

		for (int i = 0; i < arr.length; ++i) {
			if (arr[i] % 2 == 0) continue;
			list.get(0).add(i);
			list.get(1).add(arr[i]);
		}

		Collections.sort(list.get(1));

		for (int i = 0; i < list.get(0).size(); ++i) {
			arr[list.get(0).get(i)] = list.get(1).get(i);
		}

		return arr;
	}
}
