package il.co.ilrd.decoratordesignpattern;

public class PlainOutfit implements Outfit {
    private String name = "Under Garments";
    private double cost = 1.00;
    
    public PlainOutfit() {
        System.out.println(adding(name));
    }

    @Override
    public double getPrice() {
        return cost;
    }

    @Override
    public String getDescription() {
        return name;
    }

    @Override
    public String adding(String name) {
        return "Adding " + name;
    }
}
