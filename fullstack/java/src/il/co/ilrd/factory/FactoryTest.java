package il.co.ilrd.factory;

import org.junit.jupiter.api.Test;

import java.util.function.Function;

class FactoryTest {

	@Test
	public void testFactoryAnonymousClass() {
		Factory<String, Car, String> factory = new Factory<>();
		Function<String, Car> action = new Function<String, Car>() {
			@Override
			public Car apply(String s) {
				return getCar(s);
			}
		};

		factory.add("Car", action);
		Car mercedes = factory.create("Car", "Mercedes");
		Car honda = factory.create("Car", "Honda");
		Car toyota = factory.create("Car", "Toyota");

		System.out.println(mercedes.whoAmI());
		System.out.println(honda.whoAmI());
		System.out.println(toyota.whoAmI());
	}

	private Car getCar(String s) {
		switch (s) {
			case "Mercedes":
				return new Mercedes();
			case "Honda":
				return new Honda();
			case "Toyota":
				return new Toyota();
			default:
				return null;
		}
	}

	@Test
	public void testFactoryLambda() {
		Factory<String, Car, String> factory = new Factory<>();
		factory.add("Car", s -> {
			return getCar(s);
		});
		Car mercedes = factory.create("Car", "Mercedes");
		Car honda = factory.create("Car", "Honda");
		Car toyota = factory.create("Car", "Toyota");

		System.out.println(mercedes.whoAmI());
		System.out.println(honda.whoAmI());
		System.out.println(toyota.whoAmI());
	}

	@Test
	public void testFactoryInstanceMethodRef() {
		Factory<String, Car, String> factory = new Factory<>();
		factory.add("Car", this::getCar);
		Car mercedes = factory.create("Car", "Mercedes");
		Car honda = factory.create("Car", "Honda");
		Car toyota = factory.create("Car", "Toyota");

		System.out.println(mercedes.whoAmI());
		System.out.println(honda.whoAmI());
		System.out.println(toyota.whoAmI());
	}

	@Test
	public void testFactoryClassRef() {
		Factory<String, Integer, int[]> factory = new Factory<>();
		factory.add("Car", Car::multiply);
		int[] arr1 = {2, 3};
		int[] arr2 = {1, 4};
		int[] arr3 = {0, 3};
		Integer ret1 = factory.create("Car", arr1);
		Integer ret2 = factory.create("Car", arr2);
		Integer ret3 = factory.create("Car", arr3);

		System.out.println(ret1);
		System.out.println(ret2);
		System.out.println(ret3);
	}

	@Test
	public void testFactoryCtor() {
		Factory<String, Car, String> factory = new Factory<>();
		factory.add("Mercedes", Mercedes::new);
		Car mercedes = factory.create("Mercedes", "I'm a Mercedes");

		factory.add("Honda", Honda::new);
		Car honda = factory.create("Honda", "I'm a Honda");

		factory.add("Toyota", Toyota::new);
		Car toyota = factory.create("Toyota", "I'm a Toyota");

		System.out.println(mercedes.whoAmI());
		System.out.println(honda.whoAmI());
		System.out.println(toyota.whoAmI());
	}
}

class Mercedes implements Car {
	public Mercedes() {
		System.out.println("New Mercedes just created");
	}

	public Mercedes(String s) {
		System.out.println(s);
	}

	public String whoAmI() {
		return "I am a Mercedes";
	}
}

class Honda implements Car {
	public Honda() {
		System.out.println("New Honda just created");
	}

	public Honda(String s) {
		System.out.println(s);
	}

	public String whoAmI() {
		return "I am a Honda";
	}
}

class Toyota implements Car {
	public Toyota() {
		System.out.println("New Toyota just created");
	}

	public Toyota(String s) {
		System.out.println(s);
	}

	public String whoAmI() {
		return "I am a Toyota";
	}
}