package il.co.ilrd.worksheets.ws3;

// Using reflection to show all the methods of
// a class, even if the methods are defined in
// the base class.
import java.lang.reflect.*;

public class ClassInfo {
	public static void main(String[] args) {
		String userInput = args[0];

		try {
			Class loadClass = Class.forName(userInput);;
			Method[] methods = loadClass.getMethods();

			for (int i = 0; i < methods.length; ++i)
			{
				System.out.println(methods[i]);
			}
		} catch (ClassNotFoundException e) {
			System.err.println(e);
		}

	}
}
