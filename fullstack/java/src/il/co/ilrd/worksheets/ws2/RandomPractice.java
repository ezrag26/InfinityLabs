package il.co.ilrd.worksheets.ws2;

class SuperClass {
	void SuperClass(String s) {
		System.out.println(s);
	}
}
	/* this class does not have a no-argument constructor */
class SubClass extends SuperClass {
	int x = 0;
}

public class RandomPractice {
	public static void main(String[] args) {

		SubClass subInstanace = new SubClass();

	}
}
