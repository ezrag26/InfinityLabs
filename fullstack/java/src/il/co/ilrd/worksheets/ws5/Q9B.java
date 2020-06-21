package il.co.ilrd.worksheets.ws5;

public class Q9B {
	public void foo() {
		class AIC {
			public /*static*/ void foo2() {} // cannot be declared static
		}
		/*
		 * when the above method is not static, foo2 can be invoked by the
		 * following code: new AIC().foo2();
		 */
//		AIC.foo2(); // cannot call foo2 from a static context
	}
}
