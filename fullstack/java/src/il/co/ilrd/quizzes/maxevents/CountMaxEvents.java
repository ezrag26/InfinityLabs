package il.co.ilrd.quizzes.maxevents;

public class CountMaxEvents {
    static int current = 0;
    static int max = 0;
    public static void main(String[] args) {

    }

    void startEvent() {
        if (++current > max) max = current;
    }

    void endEvent() {
        --current;
    }

    int getMax() {
        return max;
    }
}
