package il.co.ilrd.worksheets.ws3;

public abstract class ShapeAbs {
    protected String color;
    protected boolean filled;

    ShapeAbs() {
        color = "green";
        filled = true;
    }

    ShapeAbs(String color, boolean filled) {
        this.color = color;
        this.filled = filled;
    }

    public String getColor() {
        return this.color;
    }

    public boolean isFilled() {
        return this.filled;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public void setFilled(boolean filled) {
        this.filled = filled;
    }

    public abstract double getArea();

    public abstract double getPerimeter();

    @Override
    public String toString() {
        return "A ShapeAbs with color of " + this.color + " and " + (filled ? "filled" : "not filled");
    }

}

class CircleAbs extends ShapeAbs {
    protected double radius;

    static final double PI = 3.141;

    CircleAbs() {
        this.radius = 1.0;
    }

    CircleAbs(double radius) {
        this.radius = radius;
    }

    CircleAbs(double radius, String color, boolean filled) {
        super(color, filled);
        this.radius = radius;
    }

    public double getRadius() {
        return this.radius;
    }

    public void setRadius(double radius) {
        this.radius = radius;
    }

    public double getArea() {
        return PI * Math.pow(radius, 2);
    }

    public double getPerimeter() {
        return PI * radius * 2;
    }

    @Override
    public String toString() {
        return "A CircleAbs with radius=" + this.radius + ", which is a subclass of " + super.toString();
    }
}

class RectangleAbs extends ShapeAbs {
    protected double width;
    protected double length;

    RectangleAbs() {
        this(1.0, 1.0);
    }

    RectangleAbs(double width, double length) {
        this.width = width;
        this.length = length;
    }

    RectangleAbs(double width, double length, String color, boolean filled) {
        super(color, filled);
        this.width = width;
        this.length = length;
    }

    public double getWidth() {
        return this.width;
    }

    public double getLength() {
        return this.length;
    }

    public void setWidth(double width) {
        this.width = width;
    }

    public void setLength(double length) {
        this.length = length;
    }

    public double getArea() {
        return this.width * this.length;
    }

    public double getPerimeter() {
        return 2 *(this.width + this.length);
    }

    @Override
    public String toString() {
        return "A RectangleAbs with width=" + this.width + " and length=" + this.length + ", which is a subclass of " + super.toString();
    }
}

class SquareAbs extends RectangleAbs {

    SquareAbs() {
        this(1.0);
    }

    SquareAbs(double side) {
        super(side, side);
    }

    SquareAbs(double side, String color, boolean filled) {
        super(side, side, color, filled);
    }

    public double getSide() {
        return getLength();
    }

    public void setSide(double side) {
        super.setWidth(side);
        super.setLength(side);
    }

    @Override
    public void setWidth(double side) {
        setSide(side);
    }

    @Override
    public void setLength(double side) {
        setSide(side);
    }

    @Override
    public String toString() {
        return "A SquareAbs with side=" + getLength() + ", which is a subclass of " + super.toString();
    }

}