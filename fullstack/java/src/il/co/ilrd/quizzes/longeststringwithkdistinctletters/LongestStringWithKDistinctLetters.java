package il.co.ilrd.quizzes.longeststringwithkdistinctletters;

import java.util.Set;
import java.util.TreeSet;

public class LongestStringWithKDistinctLetters {
	public static void main(String[] args) {
		System.out.println(findLongestStringWithKDistinctLettersSet("abcba", 3));
//		System.out.println(findLongestStringWithKDistinctLetters("abcba", 2));
	}

	public static String findLongestStringWithKDistinctLettersSet(String s, int k) {
		int sLength = s.length();
		int start = 0;
		int end = 0;

		for (int currentStart = 0; currentStart < sLength; ++currentStart) {
			int currentEnd = currentStart;
			int distinctLetters = 0;
			Set<Character> lettersSet = new TreeSet<>();

			while (distinctLetters <= k && currentEnd < sLength) {
				char ch = s.charAt(currentEnd);
				lettersSet.add(ch);
				distinctLetters = lettersSet.size();
				++currentEnd;

			}

			if (distinctLetters > k) --currentEnd;

			if (((distinctLetters > k) || ((distinctLetters == k) && (currentEnd == sLength))) &&
					(currentEnd - currentStart) > (end - start)) {
				start = currentStart;
				end = currentEnd;
			}
		}

		if (end - start == 0) return null;

		String retString = "";

		for (int i = start; i < end; ++i) {
			retString += s.charAt(i);
		}

		return retString;
	}

	public static String findLongestStringWithKDistinctLetters(String s, int k) {
		int sLength = s.length();
		int start = 0;
		int end = 0;

		for (int currentStart = 0; currentStart < sLength; ++currentStart) {
			int currentEnd = currentStart + 1;
			int distinctLetters = 1;
			int[] lettersArr = new int[256];

			while (distinctLetters <= k && currentEnd < sLength) {
				char ch = s.charAt(currentEnd);

				if (lettersArr[ch] == 0) {
					++distinctLetters;
					++lettersArr[ch];
					if (distinctLetters <= k) {
						++currentEnd;
					}
				}
				else {
					++currentEnd;
				}
			}

			if (((distinctLetters > k) || ((distinctLetters == k) && (currentEnd == sLength))) &&
					(currentEnd - currentStart) > (end - start)) {
				start = currentStart;
				end = currentEnd;
			}
		}

		if (end - start == 0) return null;

		String retString = "";

		for (int i = start; i < end; ++i) {
			retString += s.charAt(i);
		}

		return retString;
	}
}
