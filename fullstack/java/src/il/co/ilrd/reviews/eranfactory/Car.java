package il.co.ilrd.reviews.eranfactory;

public abstract class Car {
    abstract String make();
    abstract int wheelSize();

    static Integer printer(String s){
        System.out.println(s);
        return 1;
    }
}
