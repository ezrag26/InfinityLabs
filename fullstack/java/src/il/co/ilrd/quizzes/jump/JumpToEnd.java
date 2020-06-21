package il.co.ilrd.quizzes.jump;
//Given an array of non-negative integers, start from the first element and
// reach the last by jumping. The jump length can be at most the value at the
// current position in the array. The optimum result is when you reach the goal
// using a minimum number of jumps.

public class JumpToEnd {
    public static void main(String[] args) {
        int[][] nums = {{4, 7, 5, 8, 3, 5, 1, 3, 7, 3, 6, 2, 4},
                        {4, 7, 5, 8, 3},
                        {0, 7, 5, 8, 3},
                        {1, 3, 6, 3, 2, 3, 6, 8, 9, 5},
                        {2,3,1,1,4}};

        int[] expMinJumps = {3, 1, 0, 4, 2};

        for (int i = 0; i < nums.length; ++i) {
            if (expMinJumps[i] != findMinJumpsToEndRec(nums[i])) {
                System.out.println(i + ": " + findMinJumpsToEndRec(nums[i]));
            }
        }
    }

    public static int findMinJumpsToEndRec(int[] nums) {
        return findMinJumpsToEndRec(nums, 0);
    }

    public static int findMinJumpsToEndRec(int[] nums, int i) {
        if (nums[i] == 0) return 0;
        if (nums[i] >= ((nums.length - 1) - i)) return 1;

        int min = findMinJumpsToEndRec(nums, i + 1);
        for (int j = 2; j <= nums[i]; ++j) {
            int possibleMin = findMinJumpsToEndRec(nums, i + j);

            if (possibleMin != 0) min = Integer.min(min, possibleMin);
        }

        return min == 0 ? min : 1 + min;
    }
}


// Recursive:
// if current num == 0, return 0
// if current num >= arr length - 1 - index of current num, return 1

// for all indexes from the current num, take min jumps from those indexes
// return 1 + min
// -----------------------------------------------------------------------------
// Dynamic Programming:
// lut = {}
// for i = arr length - 1, i >= 0, --i
        // min = min of lut from i + 1 to i + lut[i]
        // add 1 + min to lut[i]

// return lut[0]