package il.co.ilrd.extrapractice.tictactoe;

public class CPUPlayer extends Player {
    public CPUPlayer(char symbol, String name) {
        super(symbol, name);
    }

    @Override
    protected int chooseSquare() {
        return (int) (Math.random() * 9) + 1;
    }
}