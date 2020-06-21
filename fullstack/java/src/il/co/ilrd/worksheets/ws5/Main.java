package il.co.ilrd.worksheets.ws5;

public class Main {
	public static void main(String[] args) {
		OuterClass outer = new OuterClass();
		OuterClass.InnerClass inner = outer.new InnerClass();
		OuterClass.InnerClass innerAnonymous = outer.new InnerClass() {
			String s = "test";
			@Override
			public void doThis() {
				System.out.println(s);
			}

			public void something() {
				System.out.println("This");
			}
		};


		inner.doThis();
		inner.printOuterVariable();

//		innerAnonymous.something(); // cannot invoke method that isn't originally in the class */
		innerAnonymous.doThis();
		innerAnonymous.printOuterVariable();

		System.out.println("----------------------------------------------------------------------");
		
		OuterClassStaticInner.StaticInnerClass.doThis();
		OuterClassStaticInner.StaticInnerClass.printOuterVariable();
	}
}
