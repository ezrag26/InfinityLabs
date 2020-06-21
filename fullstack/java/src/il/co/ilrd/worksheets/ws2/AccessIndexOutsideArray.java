package il.co.ilrd.worksheets.ws2;

public class AccessIndexOutsideArray {
	public static void main(String[] args) {
		int[] arr = new int[5];
		int num = 0;

		for (int i = 0; i < arr.length; ++i)
		{
			arr[i] = i;
		}

		num = arr[5];

		System.out.println(num);
	}
}
