package il.co.ilrd.quizzes.powerset;

//Software design for an elevator system
// we should be telling the classes , relations, class diagrams & Sequence
// flow.
//
// The power set of a set is the set of all its subsets. Write a function that,
// given a set, generates its power set.
// For example, given the set {1, 2, 3}, it should return {{}, {1}, {2}, {3}, {1,
// 2}, {1, 3}, {2, 3}, {1, 2, 3}}

import java.util.Arrays;

public class PowerSet {
    public static void main(String[] args) {
        int[] set = {1, 2, 3, 4, 5};
        int[][] powerSet = generatePowerSet(set);
        
        for (int i = 0; i < powerSet.length; ++i) {
            System.out.println(Arrays.toString(powerSet[i]));
        }
    }

    private static int[][] generatePowerSet(int[] set) {
        int[][] powerSet = new int[(set.length * (set.length + 1)) / 2 + 1][];

        powerSet[0] = new int[0];
        int l = 1;
        for (int i = 0; i < set.length; ++i) {
            for (int j = 0; j + i < set.length; ++j) {
                int[] newSet = new int[i + 1];
                for (int k = 0; k < i + 1; ++k) {
                    newSet[k] = set[j + k];
                }
                powerSet[l++] = newSet;
            }
        }

        return powerSet;
    }
}
