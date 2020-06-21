package il.co.ilrd.decoratordesignpattern;

public class Pants extends Clothing {
    private String name = "Pants";
    private double cost = 6.00;

    public Pants(Outfit outfit) {
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
