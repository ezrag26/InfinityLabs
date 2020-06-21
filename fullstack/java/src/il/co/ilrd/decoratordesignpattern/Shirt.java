package il.co.ilrd.decoratordesignpattern;

public class Shirt extends Clothing {
    private String name = "Shirt";
    private double cost = 4.00;

    public Shirt(Outfit outfit) {
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
