package il.co.ilrd.quizzes.quiz4;

class BaseQ1 {
	public BaseQ1() {
		System.out.println("Base");
	}
}
class DerivedQ1 extends BaseQ1 {
	public DerivedQ1() {
		System.out.println("Derived");
	}
}
	
class DeriDerivedQ1 extends DerivedQ1 {
	public DeriDerivedQ1() {
		System.out.println("DeriDerived");
	}
}

class Test {
	public static void main(String[] args) {
		DerivedQ1 b = new DeriDerivedQ1();
	}
}
