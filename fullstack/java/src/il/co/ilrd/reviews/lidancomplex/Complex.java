package il.co.ilrd.reviews.lidancomplex;

import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class Complex implements Comparable<Complex> {
    private double real;
    private double img;

    public Complex() {
        this.real = 0;
        this.img = 0;
    }

    public Complex(double real, double img) {
        this.real = real;
        this.img = img;
    }

    public double getReal() {
        return real;
    }

    public double getImg() {
        return img;
    }

    public void setReal(double real) {
        this.real = real;
    }

    public void setImg(double img) {
        this.img = img;
    }

    public boolean isReal() {
        return Double.compare(img, 0.0) == 0;
    }

    public boolean isImaginary() {
        return !this.isReal();
    }

    public Complex add(Complex toAdd) {
        this.real += toAdd.getReal();
        this.img += toAdd.getImg();

        return this;
    }

    public static Complex add(Complex cmp1, Complex cmp2) {
        return new Complex(cmp1.getReal() + cmp2.getReal(), cmp1.getImg() + cmp2.getImg());
    }

    public Complex subtract(Complex toSubtract) {
        this.real -= toSubtract.getReal();
        this.img -= toSubtract.getImg();

        return this;
    }

    public static Complex subtract(Complex cmp1, Complex cmp2) {
        return new Complex(cmp1.getReal() - cmp2.getReal(), cmp1.getImg() - cmp2.getImg());
    }

    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;
        if (!(o instanceof Complex))
            return false;
        Complex compTo = (Complex) o;

        return 0 == (Double.compare(this.real, compTo.getReal()) +
                     Double.compare(this.img, compTo.getImg()));
    }

    @Override
    public int hashCode() {
        return 31 * Double.hashCode(this.real) + Double.hashCode(this.img);
    }

    @Override
    public int compareTo(Complex complex) {
        int compReals = Double.compare(this.real, complex.getReal());
        int compImgs = Double.compare(this.img, complex.getImg());

        return 0 != compReals ? compReals : compImgs;
    }

    @Override
    public String toString() {
        return (this.real + (Double.compare(this.img, 0.0) >= 0 ? "+" : "") + this.img + "i");
    }

    static Complex parse(String exp) {
        String patternStr = "([\\+-]?\\d+\\.*\\d*)([\\+-]?\\d+\\.*\\d*)[i]";
        Pattern pattern = Pattern.compile(patternStr);
        Matcher matcher = pattern.matcher(exp);

        if (!matcher.matches()) return null;

        double real = Double.parseDouble(matcher.group(1));
        double img = Double.parseDouble(matcher.group(2));

        return new Complex(real, img);
    }
}
