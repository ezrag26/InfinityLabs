package il.co.ilrd.quizzes.aftermediakindinterviewquiz;

import java.util.Arrays;

public class MediaKindInterviewQuestions {
	public static String reverseString(String string) {
		int currentIndex = 0;
		int saveIndex = 0;
		int stringLength = string.length();
		char[] charString = string.toCharArray();
		char[] outString = new char[stringLength];

		while (currentIndex < string.length()) {
			while (currentIndex < stringLength && charString[currentIndex] == ' ') {
				outString[currentIndex++] = ' ';
			}

			saveIndex = currentIndex;
			while (currentIndex < stringLength && charString[currentIndex] != ' ') {
				++currentIndex;
			}

			reverseString(charString, saveIndex, currentIndex, outString);
		}
		return new String(outString);
	}

	private static char[] reverseString(char[] string, int first, int last, char[] outString) {
		int j = first;
		for (int i = last - 1; i >= first ; --i) {
			outString[j++] = string[i];
		}
		return outString;
	}

	public static int[] sortZeroOne(int[] arr) {
		int[] nums = arr.clone();
		int left = 0;
		int right = nums.length -1;


		while (left < right) {
			while (nums[left] != 1) {
				++left;
			}

			while (nums[right] != 0) {
				--right;
			}

			if (left < right) {
				nums[left] = 0;
				nums[right] = 1;
			}
		}

		return nums;
	}

	public static int[] findTripletSum(int target, int[] arr) {
		int[] values = new int[3];
		int[] nums = arr.clone();
		Arrays.sort(nums);

		int left = 0;
		int right = nums.length -1;
		int middle = left + 1;

		while (right > middle) {
			int sum = nums[left] + nums[middle] + nums[right];

			if (sum > target) {
				--right;
			} else if (sum < target) {
				++left;
			} else {
				values[0] = nums[left];
				values[1] = nums[middle];
				values[2] = nums[right];
				return values;
			}

			if (left >= middle || middle >= right) {
				++middle;
				left = 0;
				right = nums.length - 1;
			}
		}
		return values;

	}
}
