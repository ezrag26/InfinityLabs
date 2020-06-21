package il.co.ilrd.quizzes.dynamicprogrammingstringdistance;

import static java.lang.Integer.min;

public class StringDistance {
	public static void main(String[] args) {
		String[] s1 = {"hey","hello", "fhuie"};
		String[] s2 = {"eyh", "ehlo", "fnbdoi"};

		for (int i = 0; i < s1.length; ++i) {
//			System.out.println("Rec: " + s1[i] + " -> " + s2[i] + " = " + getRecStringDistance(s1[i], s2[i], s1[i].length(), s2[i].length()) + " operations");
			System.out.println("Table: " + s1[i] + " -> " + s2[i] + " = " + getStringDistance(s1[i], s2[i]) + " operations");
		}
	}

	static int getRecStringDistance(String s1, String s2, int s1Length, int s2Length) {

		if (s1Length == 0) return s2Length;
		if (s2Length == 0) return s1Length;

		if (s1.charAt(s1Length - 1) == s2.charAt(s2Length - 1)) return getRecStringDistance(s1, s2, s1Length - 1, s2Length - 1);

		int insert = 1 + getRecStringDistance(s1, s2, s1Length, s2Length - 1);
		int delete = 1 + getRecStringDistance(s1, s2, s1Length - 1, s2Length);
		int replace = 1 + getRecStringDistance(s1, s2, s1Length - 1, s2Length - 1);

		return min(insert, min(delete, replace));
	}

	static int getStringDistance(String s1, String s2) {
		int s1Length = s1.length();
		int s2Length = s2.length();
		int i = 0, j = 0;

		int[][] table = new int[s1Length + 1][s2Length + 1];

		/*           table
					s2Length
				0   1   2   3   4 ...
				---------------------
			0   '   0   1   2   3   4
			1   '   1   0
s1Length    2   '   2       0
			3   '   3           0
			.
			.
			.
		 */

//		if (s1Length == 0) return s2Length;
		for (; j <= s2Length; ++j) {
			table[0][j] = j;
		}

//		if (s2Length == 0) return s1Length;
		for (; i <= s1Length; ++i) {
			table[i][0] = i;
		}

		for (i = 1; i <= s1Length; ++i) {
			for (j = 1; j <= s2Length; ++j) {
//				if (s1.charAt(s1Length - 1) == s2.charAt(s2Length - 1)) return getRecStringDistance(s1, s2, s1Length - 1, s2Length - 1);
				if (s1.charAt(i - 1) == s2.charAt(j - 1)) { // -1 to get the first index
					table[i][j] = table[i - 1][j - 1];
					continue;
				}

//				int insert = 1 + getRecStringDistance(s1, s2, s1Length, s2Length - 1);
//				int delete = 1 + getRecStringDistance(s1, s2, s1Length - 1, s2Length);
//				int replace = 1 + getRecStringDistance(s1, s2, s1Length - 1, s2Length - 1);
				int insert = 1 + table[i][j - 1];
				int delete = 1 + table[i - 1][j];
				int replace = 1 + table[i - 1][j - 1];

				table[i][j] = min(insert, min(delete, replace));
			}
		}

		return table[s1Length][s2Length];
	}
}

