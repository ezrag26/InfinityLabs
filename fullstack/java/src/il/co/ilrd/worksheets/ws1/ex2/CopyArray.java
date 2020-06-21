package il.co.ilrd.worksheets.ws1.ex2;

public class CopyArray {
	public static void main(String[] args) {
		int src[] = {1, 2, 3, 4, 5};
		int dest[] = {0, 0, 0, 0, 0};
		System.arraycopy(src, 3, dest, 2, 2);
		System.out.println(dest[2]);
	}
}
