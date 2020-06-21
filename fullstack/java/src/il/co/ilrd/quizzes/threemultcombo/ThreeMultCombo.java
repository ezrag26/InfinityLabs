package il.co.ilrd.quizzes.threemultcombo;

//This problem was asked by Facebook.
// Given a list of integers, return the largest product that can be made by multiplying any three
// integers.
// For example, if the list is [-10, -10, 5, 2], we should return 500, since that's -10 * -10
// * 5.
// You can assume the list has at least three integers.

import java.util.Arrays;

public class ThreeMultCombo {

    public static void main(String[] args) {
        int[][] nums = {{-10, -10, 5, 2, 5, 2, 8, 3, 4},
                        {-3, 1, 5, -5, 2, 6, 5, 2, 7},
                        {-3, 1, 5, 2, -5, 6, 23, 6, 3},
                        {10, 9, 5, 3, 2, 1, 37, 1, 6}};

        /* takes roughly no time to compute */
        for (int i = 0; i < nums.length; ++i) {
            System.out.println(getMaxCombo(nums[i]));
        }

        /* takes a very long time to complete with array of 9 and fewer numbers,
                     and never saw an answer with array of 10 or more numbers */
        for (int i = 0; i < nums.length; ++i) {
            System.out.println(getLargestCombo(nums[i]));
        }

    }

    /* brute force */
    public static int getLargestCombo(int[] nums) {
        int i = 0;
        int j = i + 1;
        int k = j + 1;

        if (nums.length < 3) throw new IllegalArgumentException();

        return getLargestCombo(nums, i, j, k, nums[i] * nums[j] * nums[k]);
    }

    public static int getLargestCombo(int[] nums, int i, int j, int k, int max) {
        if (i > nums.length - 3) return max;
        if (k > nums.length - 1) return getLargestCombo(nums, i + 1, i + 2, i + 3, max);

        int currentMax = Integer.max(nums[i] * nums[j] * nums[k], max);

        int possibleMax = Integer.max(getLargestCombo(nums, i, j, k + 1, max), getLargestCombo(nums, i, j + 1, k + 1, max));

        return Integer.max(currentMax, possibleMax);
    }

    /* the efficient way... */
    public static int getMaxCombo(int[] nums) {
        int len = nums.length;

        Arrays.sort(nums);

        return Integer.max(nums[0] * nums[1] * nums[len - 1],
                           nums[len - 3] * nums[len - 2] * nums[len - 1]);
    }
}
