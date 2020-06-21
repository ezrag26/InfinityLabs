package il.co.ilrd.quizzes.perfectdigits;

public class PerfectDigit {
    public static void main(String[] args) {
        int[] nums = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 28, 29, 88, 100};
        
        for (int num : nums) {
            System.out.println(getPerfectNumber(num));
        }
    }

    private static int getPerfectNumber(int n) {
        final int PERFECT_SUM = 10;
        
        int sum;
        int num = n;

        while (true) {
            sum = sumDigits(num);
            
            if (sum < PERFECT_SUM) break;
            
            if (sum == PERFECT_SUM) return num;
            
            num = sum;
        }
        
        return (num * PERFECT_SUM) + (PERFECT_SUM - sum);
    }
    
    private static int sumDigits(int num) {
        int sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }
        
        return sum;
    }
}
