package il.co.ilrd.decoratordesignpattern;

public class DecoratorMain {
    

    public static void main(String[] args) {
        Outfit outfit = new Socks(new Pants(new Shirt(new PlainOutfit())));
        
        System.out.println("Price: $" + outfit.getPrice());
        System.out.println("Outfit: " + outfit.getDescription());
    }
}
