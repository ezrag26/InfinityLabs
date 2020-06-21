package il.co.ilrd.vendingmachine;

public class OutOfStockException extends Exception {
	public OutOfStockException(String message) {
		super(message);
	}
}
