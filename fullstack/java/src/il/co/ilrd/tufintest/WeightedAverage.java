package il.co.ilrd.tufintest;

import java.util.Arrays;
import java.util.List;

public class WeightedAverage {
    public static double mean(List<Integer> numbers, List<Integer> weights) throws IllegalArgumentException
    {
        if (numbers == null || weights == null ||
                numbers.size() != weights.size()) throw new IllegalArgumentException();




        int total = 0;
        int totalWeights = 0;
        for (int i = 0; i < numbers.size(); i++)
        {
            int num = numbers.get(i) * weights.get(i);
            if (num + total > Integer.MAX_VALUE - 1) {
                total = Integer.MAX_VALUE;
            }
            else {
                total += numbers.get(i) * weights.get(i);
            }
            totalWeights += weights.get(i);
        }


        return total / totalWeights;
    }

    public static void main(String[] args)
    {
        List<Integer> a = Arrays.asList(new Integer[] { 3, 6 });
        List<Integer> b = Arrays.asList(new Integer[] { 4, 2 });

        System.out.println(WeightedAverage.mean(a, b));
    }
}
