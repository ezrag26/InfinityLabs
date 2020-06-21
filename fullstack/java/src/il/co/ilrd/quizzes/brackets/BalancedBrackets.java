package il.co.ilrd.quizzes.brackets;

import java.util.*;

public class BalancedBrackets {
    public static void main(String[] args) {
        String[] s = {"{{([])}}", "()", "[()]", "{[()]}", "([{{[(())]}}])",
                        "{([][](]", "abc[](){}", "{{[]()}}}}", "{[(])}", "(([{{[(())]}}])"
        };
        boolean[] exp = {true, true, true, true, true, false, false, false, false, false};
        
        for (int i = 0; i < s.length; ++i) {
            if (exp[i] != balancedBrackets(s[i])) {
                System.out.println(i + ": " + s[i]);
            }
        }

        for (int i = 0; i < s.length; ++i) {
            if (exp[i] != balancedBracketsString(s[i])) {
                System.out.println(i + ": " + s[i]);
            }
        }
    }

    public static boolean balancedBrackets(String s) {
        if (s == null || s.length() % 2 != 0) return false;

        char[] open = {'(', '{', '['};
        char[] close = {')', '}', ']'};
        Map<Character, Character> closeToOpenBracketsMap = new HashMap<>();
        Set<Character> openBracketsSet = new HashSet<>();

        for (int i = 0; i < open.length; ++i) {
            closeToOpenBracketsMap.put(close[i], open[i]);
            openBracketsSet.add(open[i]);
        }

        Stack<Character> stackOpenBrackets = new Stack<>();
        for (int i = 0; i < s.length(); ++i) {
            char ch = s.charAt(i);

            if (openBracketsSet.contains(ch)) stackOpenBrackets.add(ch);
            else if (stackOpenBrackets.isEmpty() ||
                     closeToOpenBracketsMap.get(ch) != stackOpenBrackets.pop()) return false;
        }
        return stackOpenBrackets.isEmpty();
    }

    public static boolean balancedBracketsString(String s) {
        if (s == null || s.length() % 2 != 0) return false;

        Map<Character, Character> openToCloseBracketsMap = new HashMap<>();
        char[] open = {'(', '{', '['};
        char[] close = {')', '}', ']'};

        for (int i = 0; i < open.length; ++i) openToCloseBracketsMap.put(open[i], close[i]);

        for (int left = 0, right = s.length() - 1; left < right; ++left, --right) {
            if (openToCloseBracketsMap.get(s.charAt(left)) != s.charAt(right)) return false;
        }

        return true;
    }
}
