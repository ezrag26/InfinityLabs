package il.co.ilrd.decoratordesignpattern;

public class Socks extends Clothing {
    private String name = "Socks";
    private double cost = 1.00;

    public Socks(Outfit outfit) {
        super(outfit);
        System.out.println(adding(name));
    }

    @Override
    public double getPrice() {
        return super.getPrice() + cost;
    }

    @Override
    public String getDescription() {
        return super.getDescription() + ", " + name;
    }
}
