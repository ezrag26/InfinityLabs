package il.co.ilrd.worksheets.ws3;

public class ShapeAbstractTest {
	public static void main(String[] args) {
		System.out.println("CircleAbs Test...");
		testCircle();
		System.out.println("RectangleAbs Test...");
		testRectangle();
		System.out.println("SquareAbs Test...");
		testSquare();
		System.out.println("Exercise Test...");
		exTest();
	}

	static void testCircle() {
		CircleAbs circle = new CircleAbs(4.0, "Red", false);

		System.out.println("Radius: " + circle.getRadius());
		System.out.println("Color: " + circle.getColor());
		System.out.println("Filled: " + circle.isFilled());
		System.out.println("Area: " + circle.getArea());
		System.out.println("Perimeter: " + circle.getPerimeter());
		System.out.println(circle.toString());

	}

	static void testRectangle() {
		RectangleAbs rectangle = new RectangleAbs(4.0, 4.0, "Black", false);

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
		SquareAbs square = new SquareAbs(2.0, "Blue", true);

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

	static void exTest() {
		ShapeAbs s1 = new CircleAbs(5.5, "RED", false);
		System.out.println(s1);
		System.out.println(s1.getArea());
		System.out.println(s1.getPerimeter());
		System.out.println(s1.getColor());
		System.out.println(s1.isFilled());
		/* s1 is of type ShapeAbs and therefore does not know about getRadius. To use,
		must cast as ((CircleAbs)s1).getRadius() */
//		System.out.println(s1.getRadius());

		CircleAbs c1 = (CircleAbs)s1;
		System.out.println(c1);
		System.out.println(c1.getArea());
		System.out.println(c1.getPerimeter());
		System.out.println(c1.getColor());
		System.out.println(c1.isFilled());
		System.out.println(c1.getRadius());

//		ShapeAbs s2 = new ShapeAbs();                 /* cannot make an instance of an abstract class */

		ShapeAbs s3 = new RectangleAbs(1.0, 2.0, "RED", false);
		System.out.println(s3);
		System.out.println(s3.getArea());
		System.out.println(s3.getPerimeter());
		System.out.println(s3.getColor());
//		System.out.println(s3.getLength());     /* same as for what happened with s1 */

		RectangleAbs r1 = (RectangleAbs)s3;
		System.out.println(r1);
		System.out.println(r1.getArea());
		System.out.println(r1.getColor());
		System.out.println(r1.getLength());

		ShapeAbs s4 = new SquareAbs(6.6);
		System.out.println(s4);
		System.out.println(s4.getArea());
		System.out.println(s4.getColor());
//		System.out.println(s4.getSide());       /* same as for what happened with s1, s3 */

		RectangleAbs r2 = (RectangleAbs)s4;
		System.out.println(r2);
		System.out.println(r2.getArea());
		System.out.println(r2.getColor());
//		System.out.println(r2.getSide());       /* rectangle does not know about getSide */
		System.out.println(r2.getLength());

		SquareAbs sq1 = (SquareAbs)r2;
		System.out.println(sq1);
		System.out.println(sq1.getArea());
		System.out.println(sq1.getColor());
		System.out.println(sq1.getSide());
		System.out.println(sq1.getLength());
	}
}
