package il.co.ilrd.vendingmachine;

public class InvalidPriceException extends Exception {
	public InvalidPriceException(String message) {
		super(message);
	}
}