package il.co.ilrd.quizzes.maxindexdifference;

public class MaxIndexDifference {
    public static void main(String[] args) {
        int[][] arr = {
                        {34, 8, 10, 3, 2, 80, 30, 33, 1},
                        {9, 2, 3, 4, 5, 6, 7, 8, 18, 0},
                        {1, 2, 3, 4, 5, 6},
                        {6, 5, 4, 3, 2, 1}
                    };

        for (int i = 0; i < arr.length; ++i) {
            System.out.println("Iterative: " + getMaxIndexDiff(arr[i]));
            System.out.println("Recursive: " + getMaxIndexDiffRec(arr[i]));
        }
    }

    private static int getMaxIndexDiff(int[] A) {
        int maxDiff = -1;

        for (int i = 0; i < A.length; ++i) {
            for (int j = A.length - 1; j > i; --j) {
                if (A[j] >= A[i] && j - i > maxDiff) {
                    maxDiff = j - i;
                }
            }
        }

        return maxDiff;
    }

    private static int getMaxIndexDiffRec(int[] A) {
        return getMaxIndexDiffRec(A, -1, 0, A.length - 1);
    }

    private static int getMaxIndexDiffRec(int[] A, int maxDiff, int i, int j) {
        if (i >= A.length || j <= i) return maxDiff;

        if (A[j] >= A[i] && j - i > maxDiff) maxDiff = j - i;

        return Integer.max(getMaxIndexDiffRec(A, maxDiff, i + 1, j),
                           getMaxIndexDiffRec(A, maxDiff, i, j - 1));
    }
}
