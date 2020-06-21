package il.co.ilrd.extrapractice.tictactoe;

import java.util.Scanner;

public class TicTacToeOnlyMain {
    public static void main(String[] args) {
        char[] gameboard = new char[9];
        String player1 = null;
        String player2 = null;

        /* initialize players */
        boolean initialized = false;
        while (!initialized) {
            System.out.println("Number of human players (0, 1, 2): ");
            Scanner input = new Scanner(System.in);
            int numOfHumans = Integer.parseInt(input.nextLine());
            switch (numOfHumans) {
                case 2:
                    System.out.println("Player 1 name: ");
                    player1 = new Scanner(System.in).nextLine();
                    System.out.println("Player 2 name: ");
                    player2 = new Scanner(System.in).nextLine();
                    initialized = true;
                    break;
                case 1:
                    System.out.println("Player 1 name: ");
                    player1 = new Scanner(System.in).nextLine();
                    player2 = "CPU-1";
                    initialized = true;
                    break;
                case 0:
                    player1 = "CPU-1";
                    player2 = "CPU-2";
                    initialized = true;
                    break;
                default:
                    break;
            }
        }

        /* starting player */
        String playing = player1;

        /* initialize gameboard */
        for (int i = 0; i < gameboard.length; ++i) {
            gameboard[i] = (char)(i + 49);
        }

        /* print gameboard */
        for (int i = 0; i < gameboard.length; ++i) {
            System.out.print(gameboard[i] + "    ");
            if ((i + 1) % 3 == 0) System.out.println("\n");
        }

        /* play game */
        boolean gameover = false;
        while (!gameover) {
            System.out.println(playing + "'s turn");

            char playerSymbol = playing.equals(player1) ? 'X' : 'O';
            int square = 0;

            /* choose square */
            boolean validSquare = false;
            while (!validSquare) {
                if (playing.contains("CPU")) {
                    square = (int)(Math.random() * 9) + 1;
                } else {
                    boolean validNum = false;
                    while (!validNum) {
                        System.out.println("Choose an open square (1 - 9)");
                        try {
                            square = Integer.parseInt(new Scanner(System.in).nextLine());
                        } catch (NumberFormatException ignored) {
                            // number wasn't entered
                        }

                        if (square >= 1 && square <= 9) validNum = true;
                    }
                }

                /* square chosen is open */
                if (gameboard[square - 1] >= 49 && gameboard[square - 1] <= 57) {
                    gameboard[square - 1] = playerSymbol;
                    validSquare = true;
                }
            }

            /* print gameboard */
            for (int i = 0; i < gameboard.length; ++i) {
                System.out.print(gameboard[i] + "    ");
                if ((i + 1) % 3 == 0) System.out.println("\n");
            }

            /* check if there are 3 in a row */
            if (((gameboard[0] == gameboard[1] && gameboard[1] == gameboard[2])/* && gameboard[0] != '\0'*/) ||
                ((gameboard[3] == gameboard[4] && gameboard[4] == gameboard[5])/* && gameboard[3] != '\0'*/) ||
                ((gameboard[6] == gameboard[7] && gameboard[7] == gameboard[8])/* && gameboard[6] != '\0'*/) ||
                ((gameboard[0] == gameboard[3] && gameboard[3] == gameboard[6])/* && gameboard[0] != '\0'*/) ||
                ((gameboard[1] == gameboard[4] && gameboard[4] == gameboard[7])/* && gameboard[1] != '\0'*/) ||
                ((gameboard[2] == gameboard[5] && gameboard[5] == gameboard[8])/* && gameboard[2] != '\0'*/) ||
                ((gameboard[0] == gameboard[4] && gameboard[4] == gameboard[8])/* && gameboard[0] != '\0'*/) ||
                ((gameboard[2] == gameboard[4] && gameboard[4] == gameboard[6])/* && gameboard[2] != '\0'*/)) {

                System.out.println(playing + " wins!");
                break;
            }

            /* check if there are any spaces to fill */
            gameover = true;
            for (char c : gameboard) {
                if (c >= 49 && c <= 57) {
                    gameover = false;
                    break;
                }
            }

            if (gameover) System.out.println("It's a tie!");
            /* opponent's turn */
            else playing = playing.equals(player1) ? player2 : player1;
        }
    }
}
