package il.co.ilrd.decoratordesignpattern;

public abstract class Clothing implements Outfit {
    private Outfit outfit;

    public Clothing(Outfit outfit) {
        this.outfit = outfit;
    }

    @Override
    public double getPrice() {
        return outfit.getPrice();
    }

    @Override
    public String getDescription() {
        return outfit.getDescription();
    }
}
