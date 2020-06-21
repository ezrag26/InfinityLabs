package il.co.ilrd.quizzes.quiz4;

class BaseQ2 {
	public BaseQ2() {
		System.out.println("Base ");
	}
	public BaseQ2(String s) {
		System.out.println("Base: " + s);
	}
}

class DerivedQ2 extends BaseQ2 {
	public DerivedQ2(String s) {
		super();
//		super(s);
		System.out.println("Derived ");
	}
}

class TestQ2 {
	public static void main(String[] args) {
		BaseQ2 a = new DerivedQ2("Hello ");
	}
}