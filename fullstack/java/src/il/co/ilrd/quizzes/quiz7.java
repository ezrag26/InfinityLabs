package il.co.ilrd.quizzes;

public class quiz7 {
	public static void main(String[] args) {
		Derived derived = new Derived();

	}
}

class Base {
	private int member1 = 1;
	private int member2 = 2;

	public Base() {
		System.out.println("Base Ctor");
		print();
	}

	public void print() {
		System.out.println(member1 + " " + member2);
	}
}

class Derived extends Base {
	private int member3 = 3;
	private int member4 = 4;

	public Derived() {
		System.out.println("Derived Ctor");
		print();
	}

	public void print() {
		System.out.println(member3 + " " + member4);
	}
}