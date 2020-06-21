package il.co.ilrd.vendingmachine;

import java.util.List;

public class VendingMachine {
	private double currentAmount = 0.0;
	private VendingState currentState = VendingState.IDLE;
	private List<Product> inventory;
	private Thread thread = null;
	private ThreadRunnable runnable = null;

	/**
	 * Enum that indicates the VendingMachine's current state, allowing it to
	 * perform the correct operations in a given state upon user action
	 */
	private enum VendingState {
		IDLE {
			@Override
			VendingState insertMoney(VendingMachine machine, double amount) {
				if (Double.compare(0.0, amount) >= 0) {
					throw new IllegalArgumentException("amount must be positive");
				}

				machine.currentAmount += amount;

				machine.interruptThread();

				return MENU;
			}

			@Override
			VendingState cancelPurchase(VendingMachine machine) {
				return IDLE;
			}

			@Override
			VendingState chooseItem(VendingMachine machine, int itemNumber)
					throws Exception {
				throw new InsufficientFundsException("No money was inserted");
			}
		},
		MENU {
			@Override
			VendingState insertMoney(VendingMachine machine, double amount) {
				machine.interruptThread();

				if (Double.compare(0.0, amount) >= 0) {
					throw new IllegalArgumentException("amount must be positive");
				}

				machine.currentAmount += amount;

				return MENU;
			}

			@Override
			VendingState cancelPurchase(VendingMachine machine) {
				machine.interruptThread();

				return IDLE;
			}

			@Override
			VendingState chooseItem(VendingMachine machine, int itemNumber)
					throws Exception {
				machine.interruptThread();

				Product item = machine.inventory.get(itemNumber);

				if (item.isEmpty()) {
					throw new OutOfStockException("Sorry, item sold out");
				}

				if (Double.compare(item.getPrice(), machine.currentAmount) > 0) {
					throw new InsufficientFundsException("Not enough money");
				}

				/* decrease accumulated amount by the item's price */
				machine.currentAmount -= item.getPrice();
				item.decreaseQty();

				return IDLE;
			}
		};

		/**
		 * Receives money and updates accumulated amount of money inserted
		 *
		 * @param machine the VendingMachine receiving the money
		 * @param amount  the amount to insert to the specified vending machine
		 * @return the next state
		 *
		 * @throws IllegalArgumentException if amount is less than or equal to 0
		 */
		abstract VendingState insertMoney(VendingMachine machine, double amount);

		/**
		 * Goes to the correct state
		 *
		 * @param machine the VendingMachine upon which to cancel
		 * @return the next state
		 */
		abstract VendingState cancelPurchase(VendingMachine machine);

		/**
		 * Decreases quantity of selected item, and decreases accumulated money
		 * received
		 *
		 * @param machine the VendingMachine being purchased from
		 * @param itemNumber index of item to purchase
		 * @return the next state
		 *
		 * @throws IndexOutOfBoundsException if the item is not found in the
		 * specified vending machine
		 * @throws OutOfStockException if there is no more of the specified item
		 * @throws InsufficientFundsException if there is not enough money in
		 * the specified vending machine for the specified item
		 */
		abstract VendingState chooseItem(VendingMachine machine, int itemNumber)
				throws Exception;
	}

	/**
	 * Constructs a VendingMachine object.
	 *
	 * @param inventory a List of Products that make up the vending machine
	 */
	public VendingMachine(List<Product> inventory) {
		this.inventory = inventory;

		runnable = new ThreadRunnable();
		thread = new Thread(runnable);
		thread.start();
	}

	private class ThreadRunnable implements Runnable {
		boolean threadIsRunning = true;
		void stopRunning() {
			threadIsRunning = false;
			thread.interrupt();
		}

		@Override
		public void run() {
			while (threadIsRunning) {
				try {
					Thread.sleep(5L * 1000L);
					System.out.println("Timeout occurred: Change returned: "
							+ cancelPurchase());
				} catch (InterruptedException ignore) {}
			}
		}
	}

	private double getChange() {
		double change = this.currentAmount;
		this.currentAmount = 0.0;

		return change;
	}

	/**
	 * Receives money and updates accumulated amount of money inserted
	 *
	 * @param amount the amount to insert to the specified vending machine
	 *
	 * @throws IllegalArgumentException if amount is less than or equal to 0
	 */
	public void insertMoney(double amount) {
		currentState = currentState.insertMoney(this, amount);
	}

	/**
	 * Cancels the current purchase session
	 *
	 * @return the current amount in this VendingMachine since last cancel or
	 * successful purchase {@see chooseItem()}
	 */
	public double cancelPurchase() {
		currentState = currentState.cancelPurchase(this);

		return getChange();
	}

	/**
	 * Decreases quantity of selected item, and resets the accumulated money
	 * received
	 *
	 * @param itemNumber index of item to purchase
	 * @return the amount of change left over after the purchase
	 *
	 * @throws IndexOutOfBoundsException if the item is not found in the
	 * specified vending machine
	 * @throws OutOfStockException if there is no more of the specified item
	 * @throws InsufficientFundsException if there is not enough money in
	 * the specified vending machine for the specified item
	 */
	public double chooseItem(int itemNumber) throws Exception {
		currentState = currentState.chooseItem(this, itemNumber);
		return getChange();
	}

	private void interruptThread() {
		thread.interrupt();
	}

	/**
	 * Stops checking a timeout for this VendingMachine. Should be called after
	 * its last use.
	 */
	public void stopThread() {
		runnable.stopRunning();
	}
}