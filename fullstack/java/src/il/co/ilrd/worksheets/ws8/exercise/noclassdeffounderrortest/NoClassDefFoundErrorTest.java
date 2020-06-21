package il.co.ilrd.worksheets.ws8.exercise.noclassdeffounderrortest;

public class NoClassDefFoundErrorTest {
	public static void main(String[] args) {
		Derived2 derived2 = new Derived2();
	}
}

class Derived extends NoClassDefFoundErrorTest {
	public Derived() {

	}
}

class Derived2 extends Derived {
	Derived derived = new Derived();
	public Derived2() {}
}
