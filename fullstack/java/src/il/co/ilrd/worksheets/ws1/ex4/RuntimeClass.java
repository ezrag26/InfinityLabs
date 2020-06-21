package il.co.ilrd.worksheets.ws1.ex4;

import java.util.ArrayList;

public class RuntimeClass {

	public static void main(String[] args) {
		ArrayList<int[]> list = new ArrayList<int[]>();

		for (int i = 0; i < 1000; ++i) {
			int[] arr = new int[100000];
    		list.add(arr);
			System.out.print("Free memory = " + Runtime.getRuntime().freeMemory() + " - ");
			System.out.println("Total memory = " + Runtime.getRuntime().totalMemory());
		}
	}
}
