package il.co.ilrd.quizzes.longestnum;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

//    Given a list of non negative integers, listange them such that they form the largest
//    number.Example:
//
//    Given [3, 30, 34, 5, 9], the largest formed number is 9534330. The result may be very large, so
//    you need to return a string instead of an integer.
public class LongestNum {
    public static void main(String[] args) {
        int[] nums = {3, 30, 34, 5, 9};
        
        System.out.println(makeLongestNum(nums));

    }

    //sort list by first num, descending -> [9, 5, 34, 30, 3]
    //keep doing that within each num group (0 < ' ') -> [9, 5, 34, 3, 30]

    private static String makeLongestNum(int[] nums) {
        List<String> list = new ArrayList<>(nums.length);
        for (int i = 0; i < nums.length; ++i) {
            list.add(String.valueOf(nums[i]));
        }
        list.sort(new MyCompare());

        StringBuilder retString = new StringBuilder();

        for (int i = 0; i < list.size(); ++i) {
            retString.append(list.get(i));
        }

        return retString.toString();
    }

}

class MyCompare implements Comparator<String> {

    @Override
    public int compare(String num1, String num2) {
        String comp1 = num1 + num2;
        String comp2 = num2 + num1;

        return -comp1.compareTo(comp2);
    }
}
