package il.co.ilrd.extrapractice.tictactoe;

import java.util.Scanner;

public class TicTacToe {
    private TicTacToeBoard board = new TicTacToeBoard();
    private Player player1;
    private Player player2;

    private void resetGameBoard() {
        board.resetBoard();
    }

    public boolean playAgain() {
        System.out.print("Play again? y / n: ");

        do {
            Scanner input = new Scanner(System.in);
            String reset = input.nextLine().toLowerCase();
            switch (reset) {
                case "y":
                    resetGameBoard();
                    return true;
                case "n":
                    return false;
                default:
                    System.out.print("Invalid input. Play again? y / n: ");
            }
        } while (true);
    }

    private boolean validNumOfHumans(int numOfHumans) {
        return numOfHumans >= 0 && numOfHumans <= 2;
    }

    public int getNumOfHumans() {
        int numOfHumans = -1;

        do {
            System.out.print("Number of human players (0, 1, or 2): ");
            Scanner input = new Scanner(System.in);
            try {
                numOfHumans = Integer.parseInt(input.nextLine());
            } catch (NumberFormatException ignored) {
                // not a valid number
            }
        } while (!validNumOfHumans(numOfHumans));

        return numOfHumans;
    }

    public void createPlayers(int numOfHumans) {
        switch (numOfHumans) {
            case 2:
                System.out.print("Player1's (X's) name: ");
                player1 = new HumanPlayer( 'X', new Scanner(System.in).nextLine());
                System.out.print("Player2's (O's) name: ");
                player2 = new HumanPlayer( 'O', new Scanner(System.in).nextLine());
                break;
            case 1:
                System.out.print("Player1's (X's) name: ");
                player1 = new HumanPlayer( 'X', new Scanner(System.in).nextLine());
                player2 = new CPUPlayer( 'O', "CPU");
                break;
            case 0:
                player1 = new CPUPlayer( 'X', "CPU-1");
                player2 = new CPUPlayer( 'O', "CPU-2");
                break;
            default:
        }
    }

    public void play() {
        Player currentPlayer = player1;

        boolean gameover = false;
        do {
            System.out.println(currentPlayer.getPlayerName() + "'s turn:");

            board.print();

            int square = currentPlayer.makeMove(board);

            if (board.hasThreeInARow(square)) {
                System.out.println(currentPlayer.getPlayerName() + " wins!");
                currentPlayer.addWin();
                gameover = true;
            } else if (board.isFull()) {
                System.out.println("It's a tie!");
                gameover = true;
            } else {
                currentPlayer = currentPlayer.equals(player1) ? player2 : player1;
            }
        } while (!gameover);
    }

    public void printGameBoard() { board.print(); }
    
    public void displayCurrentMatchup() {
        System.out.println("Total Wins:");
        System.out.println(player1.getPlayerName() + ": " + player1.getWins());
        System.out.println(player2.getPlayerName() + ": " + player2.getWins());
    }
}