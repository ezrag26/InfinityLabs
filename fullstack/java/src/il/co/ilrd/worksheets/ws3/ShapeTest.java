package il.co.ilrd.worksheets.ws3;

public class ShapeTest {
	public static void main(String[] args) {
		testEx2();
		testCircle();
		testRectangle();
		testSquare();
	}

	static void testEx2() {
		Shape defaultShape = new Shape();
		Shape orangeNotFilled = new Shape("orange", false);

		System.out.println(defaultShape.getColor());
		System.out.println(defaultShape.isFilled());
		System.out.println(defaultShape.toString());
		defaultShape.setColor("brown");
		defaultShape.setFilled(false);
		System.out.println(defaultShape.getColor());
		System.out.println(defaultShape.isFilled());
		System.out.println(defaultShape.toString());

		System.out.println(orangeNotFilled.getColor());
		System.out.println(orangeNotFilled.isFilled());
		System.out.println(orangeNotFilled.toString());
		orangeNotFilled.setColor("red");
		orangeNotFilled.setFilled(true);
		System.out.println(orangeNotFilled.getColor());
		System.out.println(orangeNotFilled.isFilled());
		System.out.println(orangeNotFilled.toString());
	}

	static void testCircle() {
		Circle circle = new Circle(4.0, "Red", false);

		System.out.println("Radius: " + circle.getRadius());
		System.out.println("Color: " + circle.getColor());
		System.out.println("Filled: " + circle.isFilled());
		System.out.println("Area: " + circle.getArea());
		System.out.println("Perimeter: " + circle.getPerimeter());
		System.out.println(circle.toString());

	}

	static void testRectangle() {
		Rectangle rectangle = new Rectangle(4.0, 4.0, "Black", false);

		System.out.println("Width: " + rectangle.getWidth());
		System.out.println("Length: " + rectangle.getLength());
		System.out.println("Color: " + rectangle.getColor());
		System.out.println("Filled: " + rectangle.isFilled());
		System.out.println("Area: " + rectangle.getArea());
		System.out.println("Perimeter: " + rectangle.getPerimeter());
		System.out.println(rectangle.toString());

		rectangle.setWidth(2);
		rectangle.setLength(5);
		rectangle.setColor("Red");
		rectangle.setFilled(true);
		System.out.println("Width: " + rectangle.getWidth());
		System.out.println("Length: " + rectangle.getLength());
		System.out.println("Color: " + rectangle.getColor());
		System.out.println("Filled: " + rectangle.isFilled());
		System.out.println("Area: " + rectangle.getArea());
		System.out.println("Perimeter: " + rectangle.getPerimeter());
		System.out.println(rectangle.toString());

	}

	static void testSquare() {
		Square square = new Square(2.0, "Blue", true);

		System.out.println("Side: " + square.getSide());
		System.out.println("Color: " + square.getColor());
		System.out.println("Filled: " + square.isFilled());
		System.out.println("Area: " + square.getArea());
		System.out.println("Perimeter: " + square.getPerimeter());
		System.out.println(square.toString());

		square.setSide(6);
		square.setColor("Brown");
		square.setFilled(false);
		System.out.println("Side: " + square.getSide());
		System.out.println("Color: " + square.getColor());
		System.out.println("Filled: " + square.isFilled());
		System.out.println("Area: " + square.getArea());
		System.out.println("Perimeter: " + square.getPerimeter());
		System.out.println(square.toString());

	}
}
