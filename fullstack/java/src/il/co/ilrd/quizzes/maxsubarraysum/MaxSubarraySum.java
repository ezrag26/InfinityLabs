package il.co.ilrd.quizzes.maxsubarraysum;

public class MaxSubarraySum {
    public static void main(String[] args) {
        int[] arr = {-2, 1,-3, 4, -1, 2, 1, -5, 4};
        System.out.println(maxSubarraySum(arr));
    }

    static int maxSubarraySum(int[] arr) {
        return maxSubarraySum(arr, 0, arr[0], 0);
    }

    static int maxSubarraySum(int[] arr, int index, int abs_max, int tmp_max) {
        if (index >= arr.length) return abs_max;

        if (arr[index] < tmp_max) {
            return maxSubarraySum(arr, index, abs_max + arr[index], abs_max + arr[index]);
        }
        else {
            tmp_max = maxSubarraySum(arr, index + 1, abs_max + arr[index], abs_max + arr[index]);
        }

        return Integer.max(tmp_max, abs_max);
    }
}
