package il.co.ilrd.worksheets.ws3;

public class Shape {
    String color;
    boolean filled;

    Shape() {
        color = "green";
        filled = true;
    }

    Shape(String color, boolean filled) {
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

    @Override
    public String toString() {
        return "A Shape with color of " + this.color + " and " + (filled ? "filled" : "not filled");
    }

}

class Circle extends Shape {
    double radius;

    static final double PI = 3.141;

    Circle() {
        this.radius = 1.0;
    }

    Circle(double radius) {
        this.radius = radius;
    }

    Circle(double radius, String color, boolean filled) {
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
        return "A Circle with radius=" + this.radius + ", which is a subclass of " + super.toString();
    }
}

class Rectangle extends Shape {
    double width;
    double length;

    Rectangle() {
        this(1.0, 1.0);
    }

    Rectangle(double width, double length) {
        this.width = width;
        this.length = length;
    }

    Rectangle(double width, double length, String color, boolean filled) {
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
        return "A Rectangle with width=" + this.width + " and length=" + this.length + ", which is a subclass of " + super.toString();
    }
}

class Square extends Rectangle {

    Square() {
        this(1.0);
    }

    Square(double side) {
        super(side, side);
    }

    Square(double side, String color, boolean filled) {
        super(side, side, color, filled);
    }

    public double getSide() {
        return getLength();
    }

    public void setSide(double side) {
        setWidth(side);
        setLength(side);
    }

    public String toString() {
        return "A Square with side=" + getLength() + ", which is a subclass of " + super.toString();
    }

}