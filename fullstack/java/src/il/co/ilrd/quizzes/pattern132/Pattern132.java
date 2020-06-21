package il.co.ilrd.quizzes.pattern132;

public class Pattern132 {
    public static void main(String[] args) {
        int[][] arr = {{1, 2, 3, 4},
                       {1, 2, 4, 3},
                       {0, 1, -4},
                       {3, 5, 0, 3, 4},
                       {5, 1, 2, 3, 0, 2, -1}};

        boolean[] exp = {false, true, false, true, true};

        int fails = 0;
        for (int i = 0; i < arr.length; ++i) {
            if (pattern132(arr[i]) != exp[i]) {
                System.out.println("Failed at index " + i);
                ++fails;
            }
        }

        if (fails == 0) System.out.println("All tests passed.");
    }

    static boolean pattern132(int[] arr) {
        int length = arr.length;
        for (int i = 0; i < length - 2; ++i) {
            for (int j = i + 1; j < length - 1; ++j) {
                for (int k = j + 1; k < length; ++k) {
                    if (arr[k] > arr[i] && arr[j] > arr[k]) return true;
                }
            }
        }

        return false;
    }
}
