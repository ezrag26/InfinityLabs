package il.co.ilrd.reviews.vendingmachinetom;

public class Product {
	private double price;
	private int quantity;


public Product(double price, int quantity) throws Exception {

		if (Double.compare(price, 0.0) <= 0) {
			throw new InvalidPriceException("the price must be more than 0");
		}

		if (0 > quantity) {
			throw new InvalidQuantityException("quantity must be more than zero");
		}

		this.price = price;
		this.quantity = quantity;
	
	}
	/**
	 * @return the price of the specific product.
	 */
	public final double getPrice() { return this.price; }

	/**
	 * @return the quantity in the stock of the specific product..
	 */
	public final int getStock() { return this.quantity; }

	/**
	 * @return decrease the quantity in the stock of the specific product..
	 */
	public final void decreaseQuantity() {if (this.quantity > 0) --this.quantity; }

	/**
	 * @return return true if the quantity of this product in the stock is 0, otherwise return false.
	 */
	public final boolean isEmpty() { return this.quantity == 0; }
}

