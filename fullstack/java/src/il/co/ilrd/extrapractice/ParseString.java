package il.co.ilrd.extrapractice;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ParseString {
    public static void main(String[] args) {
        System.out.println(parse1("repetition foo 1 2 3, - repetition, *repetition*"));
        parse2("age 25 name joe");
    }
    static int parse1(String s) {
        String repetition = "repetition";
        int counter = 0;
        for (int i = 0; i <= s.length() - repetition.length(); ++i) {
            if (repetition.equals(s.substring(i, i + repetition.length()))) {
                ++counter;
                i += repetition.length() - 1;
            }
        }

        return counter;
    }

    private static int parse2(String input) {
//		String age = "age";
//		String name = "name";

        Pattern p = Pattern.compile("age ([0-9]*) name ([a-z|A-Z]*)");
        Matcher m = p.matcher(input);
        if (m.find()) {
            int age = Integer.parseInt(m.group(1));
            String name = m.group(2);
            System.out.println(age);
            System.out.println(name);

        }


//		for (int i = 0; i < input.length(); ++i) {
//			while ()
//		}
        return 0;
    }
}
