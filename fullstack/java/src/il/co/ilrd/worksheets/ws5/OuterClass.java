package il.co.ilrd.worksheets.ws5;

public class OuterClass {
	int i = 0;

	OuterClass() {
		System.out.println("Outer");
	}

	class InnerClass {
		int i = 3;

		InnerClass() {
			System.out.println("Inner");
		}

		public void doThis() {
			System.out.print("Inner doThis() calling ");
			OuterClass.this.doThis();
		}
		
		public void printOuterVariable() {
			System.out.println("InnerClass i = " + this.i);
			System.out.println("OuterClass i = " + OuterClass.this.i);
		}
	}
	
	public void doThis() {
		System.out.println("Outer doThis()");
	}
}
