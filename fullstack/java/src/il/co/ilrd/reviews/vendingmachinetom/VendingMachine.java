package il.co.ilrd.reviews.vendingmachinetom;

import java.util.List;
import java.util.concurrent.atomic.AtomicBoolean;

public class VendingMachine {
    private List<Product> inventory;
    private double moneyReceived = 0.0;
    private VendingState currentState = VendingState.IDLE;
    private Thread t1;
    ThreadRunnable runnable;
    /*private java.lang.Thread Thread;*/

    private enum VendingState {

        IDLE {
            @Override
            VendingState insertMoney(VendingMachine machine, double amount) throws IllegalArgumentException {
                if (Double.compare(amount, 0.0) <= 0) {
                    throw new IllegalArgumentException();
                }
                machine.moneyReceived += amount;
                return MENU;
            }

            @Override
            VendingState cancelPurchase(VendingMachine machine) {

                return IDLE;
            }

            @Override
            VendingState chooseItem(VendingMachine machine, int itemNumber) throws InsufficientFundsException {

                throw new InsufficientFundsException("not enough money for that product");
            }
        },
        MENU {
            @Override
            VendingState insertMoney(VendingMachine machine, double amount) throws IllegalArgumentException {
                machine.t1.interrupt();
                if (Double.compare(amount, 0.0) <= 0) {
                    throw new IllegalArgumentException();
                }
                machine.moneyReceived += amount;
                return MENU;
            }

            @Override
            VendingState cancelPurchase(VendingMachine machine) {

                machine.moneyReceived = 0.0;
                return IDLE;
            }

            @Override
            VendingState chooseItem(VendingMachine machine, int itemNumber) throws OutOfStockException, InsufficientFundsException {

                if (machine.inventory.get(itemNumber).getStock() == 0) {
                    machine.t1.interrupt();
                    throw new OutOfStockException("item not in stock");
                }

                if (Double.compare(machine.moneyReceived, machine.inventory.get(itemNumber).getPrice()) < 0)
                    throw new InsufficientFundsException(
                            "the money received is less than the price of this product");


                machine.moneyReceived -= machine.inventory.get(itemNumber).getPrice();
                machine.inventory.get(itemNumber).decreaseQuantity();

                return IDLE;
            }
        };


        abstract VendingState insertMoney(VendingMachine machine, double amount) throws IllegalArgumentException;

        abstract VendingState cancelPurchase(VendingMachine machine);

        abstract VendingState chooseItem(VendingMachine machine, int itemNumber) throws OutOfStockException, InsufficientFundsException;
    }


    public VendingMachine(List<Product> inventory)  {
        this.inventory = inventory;
        runnable = new ThreadRunnable();
        t1 = new Thread(runnable);

        t1.start();
    }

    /**
     * by this method the user can insert money to the VendingMachine
     *
     * @param moneyReceived- the money that recived by the user.
     */
    public void insertMoney(double moneyReceived) throws IllegalArgumentException {


        this.currentState = this.currentState.insertMoney(this, moneyReceived);
    }

    /**
     * by this method the user can cancel his Purchase
     *
     * @return - the money that the user inserted.
     */
    public double cancelPurchase() {

        double change = this.moneyReceived;

        this.currentState = this.currentState.cancelPurchase(this);

        return change;
    }

    /**
     * by this method the user can choose the product from the VendingMachine
     *
     * @return - the user change.
     */
    public double chooseItem(int itemNumber) throws OutOfStockException, IllegalArgumentException, InsufficientFundsException {


        /*System.out.println("money" + moneyReceived);*/
        this.currentState = this.currentState.chooseItem(this, itemNumber);

        double change = moneyReceived;
        moneyReceived = 0.0;
        return change;
    }

    /**
     * test method
     * by this method the user can choose the product from the VendingMachine
     *
     * @param - item number in the Vending Machine.
     * @return - the amount of this item in stock.
     */
    /*public final int getStockk(int itemNumber) {
        return inventory.get(itemNumber).getStock();
    }*/

    public void stopThread() {
        runnable.stop();
    }

    public class ThreadRunnable implements Runnable {
        /*    Thread t;*/

        private final AtomicBoolean running = new AtomicBoolean(false);

        public void stop() {
            running.set(false);
        }

        /**
         * this method define the thread behaviour
         */
        public void run() {

            running.set(true);
            while (running.get()) {
                if (currentState == VendingState.MENU) {

                    try {
                        Thread.sleep(5000);
                        System.out.println("Timeout: This is your change " + cancelPurchase());
                    } catch (InterruptedException e) {

                    }


                }
            }

        }
    }
}
