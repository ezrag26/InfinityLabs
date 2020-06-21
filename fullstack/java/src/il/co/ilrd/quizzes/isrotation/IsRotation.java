package il.co.ilrd.quizzes.isrotation;

public class IsRotation {
	public static void main(String[] args) {
		String[] s1 = {"12345", "1212345", "1423", ""};
		String[] s2 = {"45123", "3451212", "3124", "123"};
		boolean[] exp = {true, true, false, false};

		for (int i = 0; i < s1.length; ++i) {
			if (exp[i] != isRotation(s1[i], s2[i])) {
				System.out.println("Failed at index " + i);
			} else {
				System.out.println("'" + s1[i] + "'" + " is a rotation of " + "'" + s2[i] + "'" + "? " + exp[i]);
			}
		}
	}

	public static boolean isRotation(String s1, String s2) {
		int s1length = s1.length();
		int s2length = s2.length();

		/* at least one of the strings is empty, or the strings have different lengths, can't be a rotation */
		if (s1length == 0 || s1length != s2length) return false;

		for (int i = 0; i < s1length; ++i) {
			int current = i;
			int j = 0;

			/* find first match starting at i */
			while (current < s1length && s1.charAt(current) != s2.charAt(j)) {
				++current;
			}

			/* no match found, not a rotation */
			if (current >= s1length) return false;

			/* while the chars are equal, go to next char for each string */
			while (j < s2length && s1.charAt(current % s1length) == s2.charAt(j)) {
				++current;
				++j;
			}

			/* reached end of string, is a rotation */
			if (j >= s2length) return true;
		}

		return false;
	}
}
