package il.co.ilrd.exams.datastructures;

public class DataStructuresExam {
	public static void main(String[] args) {

		int[][] world = {
				{1, 0, 0, 1, 0},
				{0, 0, 1, 0, 0},
				{0, 0, 0, 0, 1},
				{1, 0, 0, 0, 1},
				{0, 0, 0, 0, 0}
		};

//		int size = 89;
//		int[][] world = new int[size][size];
//		for (int i = 0; i < size; ++i) {
//			for (int j = 0; j < size; ++j) {
//				world[i][j] = 1;
//			}
//		}

		System.out.println(CountIslands.countIslands(world));

	}
}

class CountIslands {
	static int[] rowCheck = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
	static int[] colCheck = {1, 0, -1, 1, 0, -1, 1, 0, -1};

	static void recFindIsland(int[][] arr, boolean[][] visArr, int i, int j) {
		visArr[i][j] = true;

		for (int k = 0; k < rowCheck.length; ++k) {
			int row = i + rowCheck[k];
			int col = j + colCheck[k];

			if (row < 0 || col < 0 || row >= visArr.length || col >= visArr[0].length|| visArr[row][col] == true) continue;
			else if (arr[row][col] == 1) {
				recFindIsland(arr, visArr, row, col);
			}

			visArr[row][col] = true;
		}
	}

	public static int countIslands(int[][] arr) {
		boolean[][] visArr = new boolean[arr.length][arr[0].length];
		int count = 0;

		for (int i = 0; i < arr.length; ++i) {
			for (int j = 0; j < arr[0].length; ++j) {
				if (visArr[i][j]) { ; }
				else if (arr[i][j] == 1) {
					recFindIsland(arr, visArr, i, j);
					++count;
				}
			}
		}
		
		

		return count;
	}
}