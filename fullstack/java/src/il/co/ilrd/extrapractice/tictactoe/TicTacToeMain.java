package il.co.ilrd.extrapractice.tictactoe;

public class TicTacToeMain {
    public static void main(String[] args) {
        TicTacToe game = new TicTacToe();
        int numOfHumans = game.getNumOfHumans();

        game.createPlayers(numOfHumans);

        do {
            game.play();

            game.printGameBoard();

            game.displayCurrentMatchup();

        } while (game.playAgain());
    }
}
