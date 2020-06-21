package il.co.ilrd.extrapractice.tictactoe;

public abstract class Player {
    private char symbol;
    private String playerName;
    int wins;

    public Player(char symbol, String playerName) {
        this.symbol = symbol;
        this.playerName = playerName;
    }

    public char getSymbol() {
        return symbol;
    }

    public void setSymbol(char symbol) {
        this.symbol = symbol;
    }

    public String getPlayerName() {
        return playerName;
    }

    public void addWin() {
        ++wins;
    }

    public int getWins() { return wins; }

    protected abstract int chooseSquare();

    public int makeMove(TicTacToeBoard board) {
        int square;

        do {
            square = this.chooseSquare();
        } while (!board.isOpen(square));

        return board.markSquare(square, symbol);
    }
}
