package il.co.ilrd.quizzes.stocksbuysell;

public class BuySellStock {
    public static void main(String[] args) {
        //Given a array of numbers representing the stock prices of a company in chronological order, write a
        //function that calculates the maximum profit you could have made from buying and selling that stock
        //once. You must buy before you can sell it.
        //For example, given [9, 11, 8, 5, 7, 10], you should return 5, since you could buy the stock at 5 dollars and
        //sell it at 10 dollars.

        int[] arr = {9, 11, 8, 5, 7, 10};
        System.out.println(getMaxProfit(arr));
    }

    static int getMaxProfit(int[] arr) {
        int buyI = 0;
        int profit = 0;

        for (int sellI = 1; sellI < arr.length; ++sellI) {
            if (arr[sellI] - arr[buyI] > profit) {
                profit = arr[sellI] - arr[buyI];
            }

            if (arr[sellI] < arr[buyI]) {
                buyI = sellI;
            }
        }

        return profit;
    }
}
