package il.co.ilrd.reviews.lidancomplex;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;


public class ComplexTest {
	private static double[] real = {-1, -1.5, -0.24, 0, 0.0, 0.1, 1, 1.0, 1.33, 1.9};
	private static double[] imaginary = {0, 4, 2.5, -5.42, -3, 2.1, 9.99, -1, 0.0, -2.4};


	@Test
	public void testDefaultCtor() {
		Complex complex = new Complex();

		assertEquals(0.0, complex.getReal(), 0.0);
		assertEquals(0.0, complex.getImg(), 0.0);
	}
	@Test
	public void testArgCtor() {

		for (int i = 0; i < real.length; ++i) {
			Complex complex = new Complex(real[i], imaginary[i]);

			assertEquals(complex.getReal(), real[i], 0.0);
			assertEquals(complex.getImg(), imaginary[i], 0.0);
		}
	}
	@Test
	public void testIsReal() {
		boolean[] exp = {true, false, false, false, false, false, false, false, true, false};

		for (int i = 0; i < real.length; ++i) {
			Complex complex = new Complex(real[i], imaginary[i]);

			assertEquals(complex.isReal(), exp[i]);
		}
	}
	@Test
	public void testIsImaginary() {
		boolean[] exp = {false, true, true, true, true, true, true, true, false, true};

		for (int i = 0; i < real.length; ++i) {
			Complex complex = new Complex(real[i], imaginary[i]);

			assertEquals(complex.isImaginary(), exp[i]);
		}
	}
	@Test
	public void testAdd() {

		for (int i = 0; i < real.length; i += 2) {

			Complex cmp1 = new Complex(real[i], imaginary[i]);
			Complex cmp2 = new Complex(real[i + 1], imaginary[i + 1]);

			cmp1.add(cmp2);

			assertEquals(real[i] + real[i + 1], cmp1.getReal(), 0.0);
			assertEquals(imaginary[i] + imaginary[i + 1], cmp1.getImg(), 0.0);
		}
	}
	@Test
	public void testStaticAdd() {

		for (int i = 0; i < real.length; i += 2) {
			Complex cmp1 = new Complex(real[i], imaginary[i]);
			Complex cmp2 = new Complex(real[i + 1], imaginary[i + 1]);

			Complex complex = Complex.add(cmp1, cmp2);

			assertEquals(real[i] + real[i + 1], complex.getReal(), 0.0);
			assertEquals(imaginary[i] + imaginary[i + 1], complex.getImg(), 0.0);
		}
	}
	@Test
	public void testSubtract() {

		for (int i = 0; i < real.length; i += 2) {
			Complex cmp1 = new Complex(real[i], imaginary[i]);
			Complex cmp2 = new Complex(real[i + 1], imaginary[i + 1]);

			cmp1.subtract(cmp2);

			assertEquals(real[i] - real[i + 1], cmp1.getReal(), 0.0);
			assertEquals(imaginary[i] - imaginary[i + 1], cmp1.getImg(), 0.0);

		}
	}
	@Test
	public void testStaticSubtract() {

		for (int i = 0; i < real.length; i += 2) {
			Complex cmp1 = new Complex(real[i], imaginary[i]);
			Complex cmp2 = new Complex(real[i + 1], imaginary[i + 1]);

			Complex complex = Complex.subtract(cmp1, cmp2);

			assertEquals(real[i] - real[i + 1], complex.getReal(), 0.0);
			assertEquals(imaginary[i] - imaginary[i + 1], complex.getImg(), 0.0);
		}
	}
	@Test
	public void testToString() {
		String[] expString = {"-1.0 + 0.0i", "-1.5 + 4.0i", "-0.24 + 2.5i", "0.0 - 5.42i", "0.0 - 3.0i",
				"0.1 + 2.1i", "1.0 + 9.99i", "1.0 - 1.0i", "1.33 + 0.0i", "1.9 - 2.4i"};

		for (int i = 0; i < real.length; ++i) {
			String complexString = new Complex(real[i], imaginary[i]).toString();
			assertEquals(0, complexString.compareTo(expString[i]));
		}
	}
	@Test
	public void testEquals() {
		double[] real = {2, 0, -3, 4, 2, 2};
		double[] imaginary = {-1, 8, 0, 1, 1, 1};
		boolean[] exp = {true, false, true, true, false, true, true, true, true};
		int j = 0;

		for (int i = 0; i < real.length; ++i) {
			Complex cmp1 = new Complex(real[i], imaginary[i]);
			++i;
			Complex cmp2 = new Complex(real[i], imaginary[i]);

			@SuppressWarnings("EqualsWithItself") boolean[] result = {cmp1.equals(cmp1), cmp1.equals(cmp2), cmp2.equals(cmp2)};
			for (int k = 0; k < result.length; ++j, ++k) {
				assertEquals(exp[j], result[k]);
			}
		}
	}
	@Test
	public void testCompareTo() {
		double[] real = {2, 0, -3, 4, 2, 2};
		double[] imaginary = {-1, 8, 0, 1, 1, 1};
		int[] exp = {1, -1, 0};

		for (int i = 0, j = 0; i < real.length; ++i, ++j) {
			Complex cmp1 = new Complex(real[i], imaginary[i]);
			++i;
			Complex cmp2 = new Complex(real[i], imaginary[i]);

			int result = cmp1.compareTo(cmp2);
			assertEquals(exp[j], result);
		}
	}
	@Test
	public void testLegalParse() {
		String[] expLegal = {"-1.0 + 3.0i", "+1 + 23.3i", "3.1 + -4i", "42.52+31i", "  -18  -  -31  i  "};

		for (String s : expLegal) {
			Complex.parse(s);
//            System.out.println(parseRet.getReal());
//            System.out.println(parseRet.getImg());
//            System.out.println(parseRet);

		}
	}

	@Test
	public void testIllegalParse() {
		String[] expIllegal = {"3..0432-312i", "3.1 +-+ 4.2i", "3..0432-312i3", "3.1 +- 4.2i", "3.1 - 4.2"};

		for (String s : expIllegal) {
			assertThrows(IllegalArgumentException.class, () -> Complex.parse(s));
		}
	}
}
