package il.co.ilrd.decoratordesignpattern;

interface Outfit {
    double getPrice();
    String getDescription();

    default String adding(String name) {
        return "Adding " + name;
    }
}
