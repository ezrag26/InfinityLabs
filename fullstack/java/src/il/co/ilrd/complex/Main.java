package il.co.ilrd.complex;

public class Main {

    public static void main(String[] args) {
        testDefaultCtor();
        testArgCtor();
        testIsReal();
        testIsImaginary();
        testAdd();
        testStaticAdd();
        testSubtract();
        testStaticSubtract();
        testToString();
        testEquals();
        testCompareTo();
        testParse();
    }

    static void testDefaultCtor() {
        Complex complex = new Complex();

        if (complex.getReal() != 0f) {
            System.out.println("Expected Real: " + 0f);
            System.out.println("Returned Real: " + complex.getReal());
        }
        if (complex.getImaginary() != 0f) {
            System.out.println("Expected i: " + 0f);
            System.out.println("Returned i: " + complex.getImaginary());
        }
    }

    static void testArgCtor() {
        double[] real = {2, 0, -3, 4};
        double[] imaginary = {-1, 8, 0, 1};

        for (int i = 0; i < real.length; ++i) {
            Complex complex = new Complex(real[i], imaginary[i]);

            if (complex.getReal() != real[i]) {
                System.out.println("Expected Real: " + real[i]);
                System.out.println("Returned Real: " + complex.getReal());
            }

            if (complex.getImaginary() != imaginary[i]) {
                System.out.println("Expected Real: " + imaginary[i]);
                System.out.println("Returned Real: " + complex.getImaginary());
            }
        }
    }

    static void testIsReal() {
        double[] real = {2, 0, -3, 4};
        double[] imaginary = {-1, 0, 0, 1};
        boolean[] exp = {false, true, true, false};

        for (int i = 0; i < real.length; ++i) {
            Complex complex = new Complex(real[i], imaginary[i]);

            if (complex.isReal() != exp[i]) {
                System.out.println("Expected: " + exp[i]);
                System.out.println("Returned: " + complex.isReal());
            }
        }
    }

    static void testIsImaginary() {
        double[] real = {0, 0, -3, 4};
        double[] imaginary = {-1, 0, 0, 1};
        boolean[] exp = {true, false, false, true};

        for (int i = 0; i < real.length; ++i) {
            Complex complex = new Complex(real[i], imaginary[i]);

            if (complex.isImaginary() != exp[i]) {
                System.out.println("Expected: " + exp[i]);
                System.out.println("Returned: " + complex.isImaginary());
            }
        }
    }

    static void testAdd() {
        double[] real = {2, 0, -3, 4};
        double[] imaginary = {-1, 8, 0, 1};

        for (int i = 0; i < real.length; ++i) {
            Complex cmp1 = new Complex(real[i], imaginary[i]);
            ++i;
            Complex cmp2 = new Complex(real[i], imaginary[i]);

            System.out.println(cmp1.add(cmp2));
        }
    }

    static void testStaticAdd() {
        double[] real = {2, 0, -3, 4};
        double[] imaginary = {-1, 8, 0, 1};

        for (int i = 0; i < real.length; ++i) {
            Complex cmp1 = new Complex(real[i], imaginary[i]);
            ++i;
            Complex cmp2 = new Complex(real[i], imaginary[i]);

            System.out.println(Complex.add(cmp1, cmp2));
        }
    }

    static void testSubtract() {
        double[] real = {2, 0, -3, 4};
        double[] imaginary = {-1, 8, 0, 1};

        for (int i = 0; i < real.length; ++i) {
            Complex cmp1 = new Complex(real[i], imaginary[i]);
            ++i;
            Complex cmp2 = new Complex(real[i], imaginary[i]);

            System.out.println(cmp1.subtract(cmp2));
        }
    }

    static void testStaticSubtract() {
        double[] real = {2, 0, -3, 4};
        double[] imaginary = {-1, 8, 0, 1};

        for (int i = 0; i < real.length; ++i) {
            Complex cmp1 = new Complex(real[i], imaginary[i]);
            ++i;
            Complex cmp2 = new Complex(real[i], imaginary[i]);

            System.out.println(Complex.subtract(cmp1, cmp2));
        }
    }

    static void testToString() {
        double[] real = {2, 0, -3, 4};
        double[] imaginary = {-1, 8, 0, 1};
        String[] expString = {"2.0 - 1.0i", "0 + 8.0i", "-3.0 + 0i", "4.0 + 1.0i"};

        for (int i = 0; i < real.length; ++i) {
            String complexString = new Complex(real[i], imaginary[i]).toString();

            if (0 != complexString.compareTo(expString[i])) {
                System.out.println("Expected: " + expString[i]);
                System.out.println("Returned: " + complexString);
            }
        }
    }

    static void testEquals() {
        double[] real = {2, 0, -3, 4, 2, 2};
        double[] imaginary = {-1, 8, 0, 1, 1, 1};
        boolean[] exp = {true, false, true, true, false, true, true, true, true};
        int j = 0;

        for (int i = 0; i < real.length; ++i) {
            Complex cmp1 = new Complex(real[i], imaginary[i]);
            ++i;
            Complex cmp2 = new Complex(real[i], imaginary[i]);

            boolean[] result = {cmp1.equals(cmp1), cmp1.equals(cmp2), cmp2.equals(cmp2)};
            int k = 0;
            while (k < result.length) {
                if (exp[j] != result[k]) {
                    System.out.println("Expected: " + exp[j]);
                    System.out.println("Returned: " + result[k]);
                }
                ++k;
                ++j;
            }
        }
    }

    static void testCompareTo() {
        double[] real = {2, 0, -3, 4, 2, 2};
        double[] imaginary = {-1, 8, 0, 1, 1, 1};
        int[] exp = {1, -1, 0};
        int j = 0;

        for (int i = 0; i < real.length; ++i) {
            Complex cmp1 = new Complex(real[i], imaginary[i]);
            ++i;
            Complex cmp2 = new Complex(real[i], imaginary[i]);

            int result = cmp1.compareTo(cmp2);
            if (exp[j] != result) {
                System.out.println("Expected: " + exp[j]);
                System.out.println("Returned: " + result);
            }
            ++j;
        }
    }

    static void testParse() {
        String[] expLegal = {"-1.0 + 3.0i", "+1 + 23.3i", "3.1 + -4i", "42.52+31i", "  -18  -  -31  i  "};
        String[] expIllegal = {"3..0432-312i", "3.1 +-+ 4.2i", "3..0432-312i3", "3.1 +- 4.2i", "3.1 - 4.2"};

        for (int i = 0; i < expLegal.length; ++i) {
            try {
                Complex parseRet = Complex.parse(expLegal[i]);
//                System.out.println(parseRet.getReal());
//                System.out.println(parseRet.getImaginary());
//                System.out.println(parseRet);
            } catch (IllegalArgumentException e) {
                System.out.println("Legal failed at index: " + i);
            }

        }

        for (int i = 0; i < expIllegal.length; ++i) {
            try {
                Complex parseRet = Complex.parse(expIllegal[i]);
                System.out.println("Illegal failed at index: " + i);
            } catch (IllegalArgumentException e) {
            }

        }
    }
}
