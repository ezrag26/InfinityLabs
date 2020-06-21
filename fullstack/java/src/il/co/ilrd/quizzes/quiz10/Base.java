package il.co.ilrd.quizzes.quiz10;

public abstract class Base {
	public Base() {
		System.out.println("In Base");
		foo();
	}
	
	public void foo() {
		System.out.println("Need to implement by " + getName());
	}
	
	abstract public String getName();
}

class Derived extends Base {
	String ds1;
	int x;
	
	public Derived() {
		this.ds1 = "Derived";
		System.out.println("In Derived ");
	}
	
	public void foo() {
		System.out.println("In Override 'foo' " + ds1);
	}

	public String getName() {
		return this.ds1;
	}

	public static void main(String[] args) {
		Base ab = new Derived();
	}
}
