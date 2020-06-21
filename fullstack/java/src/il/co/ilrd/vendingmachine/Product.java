package il.co.ilrd.vendingmachine;

public class Product {
	private double price;
	private int quantity;

	/**
	 * Constructs a Product object.
	 *
	 * @param price the price to purchase the product
	 * @param quantity the total number of items of the product
	 *
	 * @throws InvalidPriceException if the price is not greater than 0
	 * @throws InvalidQuantityException if the quantity is not greater than or
	 * equal to 0
	 */
	public Product(double price, int quantity) throws Exception {

		if (Double.compare(0.0, price) >= 0) {
			throw new InvalidPriceException("Price must be greater than 0");
		}

		if (0 > quantity) {
			throw new InvalidQuantityException("Cannot have negative quantity");
		}

		this.price = price;
		this.quantity = quantity;
	}

	/**
	 * Gets the price of this Product
	 * @return the price of this Product
	 */
	public final double getPrice() { return this.price; }

	/**
	 * Gets the quantity of this Product
	 * @return the number of items of this Product
	 */
	public final int getQuantity() { return this.quantity; }

	/**
	 * Decreases this Product's quantity by 1.
	 * Note: calling decreaseQty() on a Product with a quantity of 0 will not
	 * decrease the quantity any further
	 */
	public final void decreaseQty() {
		if (this.quantity > 0) --this.quantity;
	}

	/**
	 * Checks if there are no items of this Product
	 * @return true if there are no items, false otherwise
	 */
	public final boolean isEmpty() { return this.quantity == 0; }
}
