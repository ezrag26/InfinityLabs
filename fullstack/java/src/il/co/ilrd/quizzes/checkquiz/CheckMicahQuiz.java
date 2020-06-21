package il.co.ilrd.quizzes.checkquiz;

public class CheckMicahQuiz {
	public static void main(String[] args) {
		String[] strings = {"1", "2222", "12321", "112321"};
		String[] revStrings = {"Ezra", "StRiNg", "racecar", "a1b2c3"};

		for (int i = 0; i < strings.length; ++i) {
			System.out.println(strings[i] + " : " + isPalindrome(strings[i]));
		}

		for (int i = 0; i < revStrings.length; ++i) {
			printReverse(revStrings[i]);
		}

	}

	private static boolean isPalindrome(String str) {
		int iStart = 0;
		int iEnd = str.length() - 1;

		while (iStart < iEnd) {
			if (str.charAt(iStart++) != str.charAt(iEnd--)) return false;
		}

		return true;
	}

	private static void printReverse(String org) {
		for (int i = org.length() - 1; i >= 0; --i) {
			System.out.print(org.charAt(i));
		}
		System.out.println();
	}

//	private void swap(String str,  int i1, int i2) {
//		char tmp = str.charAt(i1);
//		str.set(i1, str.charAt(i2));
//		str.set(i2, tmp);
//	}
//
//	private void printPermutations(String str) {
//		for (int i = 0, size = str.length(); i < size; ++i) {
//			for (int j = 0; j < size - 1; ++j) {
//				System.out.println(str);
//				swap(str, j, j + 1);
//			}
//		}
//	}
}
