package il.co.ilrd.reviews.eranfactory;

import org.junit.jupiter.api.Test;

import java.util.function.Function;

public class FactoryTest {
    private Car makeCar(String s) {//create Factory method that calls Ctors based on name
        switch (s) {
            case ("Mercedes"): {
                return new merc();
            }
            case ("Ford"): {
                return new ford();
            }
            case ("Audi"): {
                return new audi();
            }
            default:
                return null;
        }
    }

    @Test
    public void AnonymousFactory() {
        Factory<String, Car, String> carFactory = new Factory<>();//create a new factory to hold Ctors.
        Function<String, Car> func = new Function<String, Car>() {//populate factory method with Ctor above.
            @Override
            public Car apply(String s) {
                return makeCar(s);
            }
        };

        carFactory.add("car", func);//add an entry for Ctors

        Car a = carFactory.create("car", "Mercedes");//call Ctors by name
        Car b = carFactory.create("car", "Ford");

        System.out.println(a.make() + " with wheels " + a.wheelSize() + " inches big");
        System.out.println(b.make() + " with wheels " + b.wheelSize() + " inches big");
    }

    @Test
    public void FactoryCtor() {
        Factory<String, Car, String> carFactory = new Factory<>();//create a new factory to hold Ctors.

        carFactory.add("merc", merc::new);//add a new factory method - "merc" creates a new merc object, calls Ctor
        carFactory.create("merc", "merc Ctor");//call the Ctor with data

        carFactory.add("ford", ford::new);
        Car b = carFactory.create("ford", "ford Ctor");

        System.out.println(b.make() + " with wheels " + b.wheelSize() + " inches big");
    }

    @Test
    public void FactoryLambda() {
        Factory<String, Car, String> carFactory = new Factory<>();//create a new factory to hold Ctors.
        carFactory.add("car", s -> {//add a lambda that calls the correct Ctor, according to the name given as data.
            return makeCar(s);
        });

        Car a = carFactory.create("car", "Mercedes");
        Car b = carFactory.create("car", "Audi");

        System.out.println(b.make() + " with wheels " + b.wheelSize() + " inches big");
        System.out.println(a.make() + " with wheels " + a.wheelSize() + " inches big");

    }

    @Test
    public void FactoryClassRef() {
        Factory<String, Integer, String> carFactory = new Factory<>();//create a new factory to hold Ctors. middle type is method return type
        carFactory.add("car", Car::printer);//create a reference to a static method of base class
        System.out.println("car creation returned " + carFactory.create("car", "merc"));//call the method at key
    }

    @Test
    public void FactoryInstRef(){
        Factory<String, Car, String> carFactory = new Factory<>();
        carFactory.add("car", this::makeCar);//populate Factory with factory method
        Car mercedes = carFactory.create("car", "Mercedes");//create instance
        System.out.println(mercedes.make() + " with wheels of size " +mercedes.wheelSize());//call method of that instance
    }

    class merc extends Car {
        public merc() {
            System.out.println("new Mercedes");
        }

        public merc(String s) {
            System.out.println("new " + s);
        }

        @Override
        public String make() {
            return "Mercedes";
        }

        @Override
        public int wheelSize() {
            return 18;
        }
    }

    class ford extends Car {
        public ford() {
            System.out.println("new Ford");
        }

        public ford(String s) {
            System.out.println("new " + s);
        }

        @Override
        public String make() {
            return "Ford";
        }

        @Override
        public int wheelSize() {
            return 16;
        }
    }

    class audi extends Car {
        public audi() {
            System.out.println("new Audi");
        }

        public audi(String s) {
            System.out.println("new " + s);
        }

        @Override
        public String make() {
            return "Audi";
        }

        @Override
        public int wheelSize() {
            return 20;
        }
    }
}
