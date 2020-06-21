package il.co.ilrd.extrapractice.tictactoe;

public class TicTacToeBoard {
    private char[] board = new char[9];
    private static final int NUM_OF_SQUARES = 9;
    private static final char CHAR_ONE = 49;
    private static final char CHAR_NINE = CHAR_ONE + 8;

    public TicTacToeBoard() {
        initGameBoard();
    }

    private void initGameBoard() {
        for (int i = 0; i < NUM_OF_SQUARES; ++i) {
            board[i] = (char)(CHAR_ONE + i);
        }
    }

    public boolean isOpen(int square) {
        boolean isInBounds = square >= 1 && square <= 9;
        return isInBounds && (board[square - 1] >= CHAR_ONE &&
                              board[square - 1] <= CHAR_NINE);
    }

    public int markSquare(int square, char symbol) {
        board[square - 1] = symbol;
        return square;
    }

    public void print() {
        for (int i = 0; i < NUM_OF_SQUARES; ++i) {
            System.out.print(board[i] + "    ");
            if ((i + 1) % 3 == 0) System.out.println("\n");
        }
    }

    public boolean hasThreeInARow(int mostRecentSquare) {
        switch (mostRecentSquare - 1) {
            case 0:
                return (((board[0] == board[1] && board[1] == board[2])/* && board[0] != '\0'*/) ||
                        ((board[0] == board[3] && board[3] == board[6])/* && board[0] != '\0'*/) ||
                        ((board[0] == board[4] && board[4] == board[8])/* && board[0] != '\0'*/));
            case 1:
                return (((board[0] == board[1] && board[1] == board[2])/* && board[0] != '\0'*/) ||
                        ((board[1] == board[4] && board[4] == board[7])/* && board[1] != '\0'*/));
            case 2:
                return (((board[0] == board[1] && board[1] == board[2])/* && board[0] != '\0'*/) ||
                        ((board[2] == board[5] && board[5] == board[8])/* && board[2] != '\0'*/) ||
                        ((board[2] == board[4] && board[4] == board[6])/* && board[2] != '\0'*/));
            case 3:
                return (((board[3] == board[4] && board[4] == board[5])/* && board[3] != '\0'*/) ||
                        ((board[0] == board[3] && board[3] == board[6])/* && board[0] != '\0'*/));
            case 4:
                return (((board[3] == board[4] && board[4] == board[5])/* && board[3] != '\0'*/) ||
                        ((board[1] == board[4] && board[4] == board[7])/* && board[1] != '\0'*/) ||
                        ((board[0] == board[4] && board[4] == board[8])/* && board[0] != '\0'*/) ||
                        ((board[2] == board[4] && board[4] == board[6])/* && board[2] != '\0'*/));
            case 5:
                return (((board[3] == board[4] && board[4] == board[5])/* && board[3] != '\0'*/) ||
                        ((board[2] == board[5] && board[5] == board[8])/* && board[2] != '\0'*/));
            case 6:
                return (((board[6] == board[7] && board[7] == board[8])/* && board[6] != '\0'*/) ||
                        ((board[0] == board[3] && board[3] == board[6])/* && board[0] != '\0'*/) ||
                        ((board[2] == board[4] && board[4] == board[6])/* && board[2] != '\0'*/));
            case 7:
                return (((board[6] == board[7] && board[7] == board[8])/* && board[6] != '\0'*/) ||
                        ((board[1] == board[4] && board[4] == board[7])/* && board[1] != '\0'*/));
            case 8:
                return (((board[6] == board[7] && board[7] == board[8])/* && board[6] != '\0'*/) ||
                        ((board[2] == board[5] && board[5] == board[8])/* && board[2] != '\0'*/) ||
                        ((board[0] == board[4] && board[4] == board[8])/* && board[0] != '\0'*/));
            default:
                return false;
        }
    }

    public boolean isFull() {
        for (char c : board) {
            if (c >= CHAR_ONE && c <= CHAR_NINE) {
                return false;
            }
        }

        return true;
    }

    public void resetBoard() {
        initGameBoard();
    }
}

/* printing game board with borders
for (int j = 0; j < 1; ++j) {
    for (int i = 0; i < 9; ++i) {
        System.out.print("-  ");
    }

    System.out.println();

    for (int i = 0; i < gameboard.length; ++i) {

        System.out.print("|   " + (gameboard[i] == '\0' ? " " : gameboard[i]) + "   ");
        if ((i + 1) % 3 == 0) {
            System.out.println("|\n");
            for (int k = 0; k < 9; ++k) {
                System.out.print("-  ");
            }
            System.out.println("\n");
        }
    }
}
*/
