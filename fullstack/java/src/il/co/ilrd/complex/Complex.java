package il.co.ilrd.complex;

import java.util.Objects;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * @author Ezra Gordon
 * @version 1.0, 12/12/2019
 * @since 1.0
 */
public class Complex implements Comparable<Complex> {
    private double real;
    private double imaginary;

    /**
     * Initializes this object's real and imaginary values to 0
     */
    public Complex() {
        this.real = 0;
        this.imaginary = 0;
    }

    /**
     * Initializes this object's real and imaginary values to the specified real
     * and imaginary
     *
     * @param real      the value to set this object's real to
     * @param imaginary the value to set this object's imaginary to
     */
    Complex(double real, double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    /**
     * Gets the real value of this object.
     *
     * @return the Complex object's real value
     */
    public double getReal() {
        return this.real;
    }

    /**
     * Gets the imaginary value of this object.
     *
     * @return the Complex object's imaginary value
     */
    public double getImaginary() {
        return this.imaginary;
    }

    /**
     * Sets the real value of this object.
     *
     * @param real the real value to set
     */
    public void setReal(double real) {
        this.real = real;
    }

    /**
     * Sets the imaginary value of this object.
     *
     * @param imaginary the imaginary value to set
     */
    public void setImaginary(double imaginary) {
        this.imaginary = imaginary;
    }

    /**
     * Checks if this object holds a real number.
     *
     * @return {@code true} if this object holds a real number, {@code false} if
     * it holds an imaginary number
     */
    public boolean isReal() {
        return Double.compare(this.imaginary, 0.0) == 0;
    }

    /**
     * Checks if this object holds an imaginary number.
     *
     * @return {@code true} if this object holds an imaginary number, {@code
     * false} if it holds a real number
     */
    public boolean isImaginary() {
        return !(this.isReal());
    }

    /**
     * Adds two Complex objects.
     *
     * @param toAdd the Complex object to add to this object
     * @return this object, updated with added value
     */
    public Complex add(Complex toAdd) {
        this.real += toAdd.getReal();
        this.imaginary += toAdd.getImaginary();

        return this;
    }

    /**
     * Adds two Complex objects.
     *
     * @param complex1 one of the Complex objects to be added
     * @param complex2 the other Complex object to be added
     * @return a Complex object with the added value of complex1 and complex2
     */
    static Complex add(Complex complex1, Complex complex2) {
        return new Complex(complex1.getReal(),
                           complex1.getImaginary()).add(complex2);
    }

    /**
     * Subtracts two Complex objects.
     *
     * @param toSubtract the Complex object to subtract from this object
     * @return this object, updated with subtracted value
     */
    public Complex subtract(Complex toSubtract) {
        this.real -= toSubtract.getReal();
        this.imaginary -= toSubtract.getImaginary();

        return this;
    }

    /**
     * Subtracts two Complex objects.
     *
     * @param complex1 the Complex object to be subtracted from
     * @param complex2 the other Complex object to be subtracted
     * @return a Complex object with the subtracted value of complex2 from
     * complex1
     */
    public static Complex subtract(Complex complex1,
                                   Complex complex2) {
        return new Complex(complex1.getReal(),
                           complex1.getImaginary()).subtract(complex2);
    }

    /**
     * Converts a complex number represented as a string into a Complex object.
     * exp must follow the following format:
     * {@code [space(s)][+|-]realValue[space(s)]+|-[space(s)][+|-]imaginaryValue[space(s)]i[space(s)]}.
     * Note: the format is subject to change, but only in a way where the
     * following holds:
     * <i>realNumber</i> precedes <i>+|-</i> which precedes
     * <i>imaginaryValue</i> which precedes <i>i</i>.
     *
     * @param exp the string representation of the complex number to be
     *            converted
     * @return a Complex object converted from the String exp
     * @throws IllegalArgumentException If exp does not follow the above format
     */
    public static Complex parse(String exp) {
        Complex complex = new Complex();
        final String regex =
          "^\\s*([-+]?\\d*\\.?\\d*)\\s*([-+])\\s*([-+]?\\d*\\.?\\d*)\\s*i\\s*$";
        Pattern p = Pattern.compile(regex);
        Matcher m = p.matcher(exp);

        if (m.find()) {
            /* real value */
            complex.setReal(Double.parseDouble(m.group(1)));

            /* imaginary multiplier */
            final double mult = Double.parseDouble(m.group(2) + "1");

            /* imaginary value*/
            complex.setImaginary(mult * Double.parseDouble(m.group(3)));
        } else {
            throw new IllegalArgumentException();
        }

        return complex;
    }

    /**
     * Creates a string of this object's complex number.
     *
     * @return a string representation of this object
     */
    @Override
    public String toString() {
//		/* no imaginary value */
//		if (this.isReal()) {
//			return this.real + " + 0.0i";
//		}
//
//		/* no real value */
//		if (this.real == 0) {
//			return "0.0" + (this.imaginary >= 0 ? " +
//			" + this.imaginary :
//			" - " + -this.imaginary) + "i";
//		}

        /* both real and imaginary values exist */
        return this.real + (Double.compare(this.imaginary, 0.0) >= 0 ?
                            " + " + this.imaginary :
                            " - " + -this.imaginary) + "i";
    }

    /**
     * Checks if two Complex objects have the same complex number.
     *
     * @param object object to compare this object with
     * @return {@code true} if the objects' complex numbers are the same, {@code
     * false} if they are not
     * @throws IllegalArgumentException If object is not an instance of Complex
     */
    @Override
    public boolean equals(Object object) {
        if (this == object) return true;

        if (!(object instanceof Complex)) {
            throw new IllegalArgumentException("Not a Complex object");
        }

        Complex complex = (Complex) object;

        return (0 == Double.compare(this.real, complex.getReal()) &&
                0 == Double.compare(this.imaginary, complex.getImaginary()));
    }

    /**
     * Creates a hash of this object.
     *
     * @return this object's hash value
     */
    @Override
    public int hashCode() {
        return Objects.hash(this.real, this.imaginary);
    }

    /**
     * Compares this object and another Complex object. A Complex object first
     * compares the real values of the number, and only compares the imaginary
     * values iff the real values are equal to each other.
     *
     * @param complex the Complex object to compare to this object
     * @return a negative integer, zero, or a positive integer if this object is
     * found to be respectively less than, equal to, or greater than complex
     */
    @Override
    public int compareTo(Complex complex) {
        int realCmp = Double.compare(this.real, complex.getReal());
        int imgCmp  = Double.compare(this.imaginary, complex.getImaginary());

        return 0 != realCmp ? realCmp : imgCmp;
    }
}
