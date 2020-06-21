package il.co.ilrd.quizzes.snail;

//“The Snail”:
//        Given a N by M matrix of numbers, print out the matrix in a clockwise spiral.
//        For example, given the following matrix:
//        [[1, 2, 3, 4, 5],
//        [6, 7, 8, 9, 10],
//        [11, 12, 13, 14, 15],
//        [16, 17, 18, 19, 20]]
//        You should print out the following:
//        1
//        2
//        3
//        4
//        5
//        10
//        15
//        20
//        19
//        18
//        17
//        16
//        11
//        6
//        7
//        8
//        9
//        14
//        13
//        12

import il.co.ilrd.hashmap.HashMap;

import java.util.Map;

public class Snail {
    static Map<Integer, Integer> starts = new HashMap<>();
    static Map<Integer, Integer> ends = new HashMap<>();
    public static void main(String[] args) {
        int[][] matrix = {{1, 2, 3, 4, 5},
                          {14, 15, 16, 17, 6},
                          {13, 20, 19, 18, 7},
                          {12, 11, 10, 9, 8}};

//        int[][] matrix1 = {{1,  2,  3,  4, 5},
//                           {14, 15, 16, 6},
//                           {13, 18, 17, 7},
//                           {12, 11, 10, 9, 8}};

        printClockwise(matrix);
    }

    public static void printClockwise(int[][] matrix) {
        int rows = matrix.length;

        for (int i = 0; i < rows; ++i) {
            starts.put(i, 0);
            ends.put(i, matrix[i].length - 1);

        }

        int row = 0;
        while (!starts.isEmpty()) {
            row = goAcrossRight(matrix, row);
            row = goDown(matrix, row);
            row = goAcrossLeft(matrix, row);
            row = goUp(matrix, row);
        }

    }

    public static int goAcrossRight(int[][] matrix, int row) {
        if (starts.isEmpty()) return 0;

        for (int i = starts.get(row); i <= ends.get(row); ++i) {
            System.out.println(matrix[row][i]);
        }

        starts.remove(row);
        ends.remove(row);

        return ++row;
    }

    public static int goDown(int[][] matrix, int row) {
        if (ends.isEmpty()) return 0;

        while (ends.containsKey(row)) {
            int end = ends.get(row);
            System.out.println(matrix[row][end]);
            ends.put(row, --end);

            ++row;
        }

        return --row;
    }

    public static int goAcrossLeft(int[][] matrix, int row) {
        if (ends.isEmpty()) return 0;

        for (int i = ends.get(row); i >= starts.get(row); --i) {
            System.out.println(matrix[row][i]);
        }

        starts.remove(row);
        ends.remove(row);

        return --row;
    }

    public static int goUp(int[][] matrix, int row) {
        if (starts.isEmpty()) return 0;

        while (starts.containsKey(row)) {
            int start = starts.get(row);
            System.out.println(matrix[row][start]);
            starts.put(row, ++start);

            --row;
        }

        return ++row;
    }
}
