package il.co.ilrd.quizzes.knapsack;

public class KnapSack {
	public static void main(String[] args) {
		int[] wt = {10, 20, 30};
		int[] val = {60, 100, 120};
		int W = 10;
		int n = wt.length;
		System.out.println(knapSack(W, wt, val, n));
	}

	public static int knapSack(int W, int[] wt, int[] val, int n) {
		int result = 0;

//		for (int i = 0; i < n; ++i) {
//			if (wt[i] > W) continue;
//
//			for (int j = 0; j < n; ++j) {
//				int currentW = wt[i];
//				int currentVal = val[i];
//
//				for (int k = j, i1 = 0; i1 < n; k = (k + 1) % n, ++i1) {
//					if (k == i || (currentW + wt[k] > W)) continue;
//
//					currentVal += val[i];
//					if (currentVal > result) result = currentVal;
//				}
//			}
//		}

		return result;
	}
}
