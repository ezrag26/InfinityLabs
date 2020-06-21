package il.co.ilrd.reviews.vendingmachinetom;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

public class VendingMachineTom {

	static final double[] price = {1.0, 2.5, 2.0, 5.75};
	static final int[] quantity = {3, 6, 2, 4};
	static final List<Product> initInventory = new ArrayList<Product>();
	static List<Product> inventory;
	static VendingMachine vm = null;

	@BeforeEach
	public void initializeList() throws InterruptedException {
		inventory = initInventory;
		for (int i = 0; i < price.length; ++i) {
			try {
				inventory.add(new Product(price[i], quantity[i]));
			} catch (Exception e) {
				System.out.println("Caught: " + e);
			}
		}
		vm = new VendingMachine(inventory);
	}

	@AfterEach
	public void endThread() throws InterruptedException {
		vm.stopThread();
	}

	@Test
	public void testInvalidPrice() {
		assertThrows(InvalidPriceException.class, () -> {
			inventory.add(new Product(0.0, 2));
		});

		assertThrows(InvalidPriceException.class, () -> {
			inventory.add(new Product(-0.01, 2));
		});
	}

	@Test
	public void testInvalidQuantity() {
		assertThrows(InvalidQuantityException.class, () -> {
			inventory.add(new Product(2.0, -1));
		});

		assertDoesNotThrow(() -> {
			inventory.add(new Product(3, 0));
		});
	}

	@Test
	public void testLegalInsert() {
		double[] insert = {1.0, 4.3, 2.7, 3};
		double total = 0;


		for (double money : insert) {
			total += money;
			vm.insertMoney(total);
			double change = vm.cancelPurchase();
			assertEquals(total, change);
		}

	}

	@Test
	public void testIllegalInsert() throws Exception {
		double[] insert = {-1.0, -3.5, 0.0};


		for (int i = 0; i < insert.length; ++i) {

			int finalI = i;
			assertThrows(IllegalArgumentException.class, () -> {
				vm.insertMoney(insert[finalI]);
			});

		}
	}

	@Test
	public void testLegalPurchase() throws Exception {
		double[] insert = {4.0, 2.0, 1.75};
		double change = 0;


		for (double money : insert) {
			vm.insertMoney(money);
		}

		try {
			change = vm.chooseItem(3);
			assertEquals(2.0, change);
		} catch (IndexOutOfBoundsException /*| InsufficientFundsException | OutOfStockException*/ e) {
			System.out.println("Caught: " + e);
		}

		try {
			vm.insertMoney(change);
			change = vm.chooseItem(0);
			assertEquals(1.0, change);
		} catch (IndexOutOfBoundsException /*| InsufficientFundsException | OutOfStockException*/ e) {
			System.out.println("Caught: " + e);
		}

		try {
			vm.insertMoney(change);
			change = vm.chooseItem(0);
			assertEquals(0.0, change);
		} catch (IndexOutOfBoundsException /*| InsufficientFundsException | OutOfStockException*/ e) {
			System.out.println("Caught: " + e);
		}
	}

	@Test
	public void testIndexOutOfBounds() {
		double[] insert = {4.0, 2.0, 1.75};


		for (double money : insert) {
			vm.insertMoney(money);
		}

		assertThrows(IndexOutOfBoundsException.class, () -> {
			vm.chooseItem(inventory.size());
		});
	}

	@Test
	public void testInsufficientFunds() throws Exception {
		double[] insert = {4.0, 2.0, 1.75};
		double total = 0;


		for (double money : insert) {
			vm.insertMoney(money);
			total += money;
		}

		double finalTotal = total;
		assertThrows(InsufficientFundsException.class, () -> {
			assertEquals(finalTotal - inventory.get(3).getPrice(), vm.chooseItem(3));
			vm.chooseItem(3);
		});
	}

	@Test
	public void testOutOfStock() throws Exception {
		double[] insert = {4.0, 2.0, 1.75};
		double total = 0;


		for (double money : insert) {
			vm.insertMoney(money);
			total += money;
		}

		vm.insertMoney(1000);
		assertThrows(OutOfStockException.class, () -> {
			for (int i = 0; i < quantity[0] + 1; ++i) {
				vm.insertMoney(vm.chooseItem(0));
			}
		});
	}

	@Test
	public void testCancelNoMoney() throws Exception {
		double[] insert = {1.0, 3.5, 1.3, 4};


		assertEquals(0.0, vm.cancelPurchase());

	}

	@Test
	public void testCancelWithMoney() throws Exception {
		double[] insert = {1.0, 3.5, 1.3, 4};


		for (double money : insert) {
			vm.insertMoney(money);
		}

		assertEquals(9.8, vm.cancelPurchase());
		assertEquals(0.0, vm.cancelPurchase());

		for (int i = 0; i < insert.length; ++i) {
			vm.insertMoney(insert[i]);
		}

		assertEquals(9.8, vm.cancelPurchase());
		assertEquals(0.0, vm.cancelPurchase());
	}

	@Test
	public void testTimeOut() throws Exception {
		double[] insert = {1.0/*, 3.5, 1.3, 4*/};


		for (double money : insert) {
			vm.insertMoney(money);
			Thread.sleep(8000);
			assertEquals(0.0, vm.cancelPurchase());
		}
	}

	@Test
	public void testTimeOutAfterPurchase() throws Exception {
		double[] insert = {6.0};


		for (double money : insert) {
			vm.insertMoney(money);
			Thread.sleep(2000);
			assertDoesNotThrow(() -> {
				vm.chooseItem(3);
			});
		}

		for (double money : insert) {
			vm.insertMoney(money);
			Thread.sleep(8000);
			assertThrows(InsufficientFundsException.class, () -> {
				vm.chooseItem(3);
			});
		}
	}
}
