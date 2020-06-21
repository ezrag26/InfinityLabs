package il.co.ilrd.extrapractice.tictactoe;

import java.util.Scanner;

public class HumanPlayer extends Player {
    public HumanPlayer(char symbol, String name) {
        super(symbol, name);
    }

    @Override
    protected int chooseSquare() {
        int square = 0;

        do {
            System.out.print("Choose an open square (1 - 9): ");
            try {
                square = Integer.parseInt(new Scanner(System.in).nextLine());
            } catch (NumberFormatException ignored) {
                // not a valid number
            }
        } while (square < 1 || square > 9);

        return square;
    }
}
