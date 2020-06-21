package il.co.ilrd.worksheets.ws6;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;

public class ObjectAnalyzer {

	public int aField = 0;
	private int aPrivateField = 0;
	
	private static void printArray(Object[] array) {
		for (Object o : array) {
			System.out.println(o);
		}
	}

	public static void printAncestor(String className) throws ClassNotFoundException {
		System.out.println("Ancestors:");
		for (Class<?> ancestor = Class.forName(className).getSuperclass(); ancestor != null; ancestor = ancestor.getSuperclass()) {
			System.out.println(ancestor);
		}
	}

	public static void listModifiersAndInterfaces(String className) throws ClassNotFoundException {
		System.out.println("\nClass Modifiers: ");
		System.out.println(Modifier.toString(Class.forName(className).getModifiers()));
		System.out.println("\nInterfaces: ");
		printArray(Class.forName(className).getInterfaces());
		System.out.println("\nConstructors: ");
		printArray(Class.forName(className).getConstructors());
	}

	public static void listMembers(String className) throws ClassNotFoundException {
		System.out.println("\nFields: ");
		printArray(Class.forName(className).getDeclaredFields());
		System.out.println("\nMethods: ");
		printArray(Class.forName(className).getDeclaredMethods());
	}

	public static Object createNewInstance(String className, Class<?>[] paramTypes, Object ... ctorArgs) throws ClassNotFoundException, NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException {
		return Class.forName(className).getConstructor(paramTypes).newInstance(ctorArgs);
	}

	public static Object callMethod(Object o, String methodName, Class<?>[] methodParamTypes, Object ... methodArgs) throws NoSuchMethodException, InvocationTargetException, IllegalAccessException {
		Method method = o.getClass().getDeclaredMethod(methodName, methodParamTypes);
		return method.invoke(o, methodArgs);
	}

	@Override
	public String toString() {
		return "ObjectAnalyzer{" +
				"aField=" + aField +
				", aPrivateField=" + aPrivateField +
				'}';
	}

	private void printThis(String s) {
		System.out.println(s);
	}

	public static void main(String[] args) throws InvocationTargetException, NoSuchMethodException, InstantiationException, IllegalAccessException, ClassNotFoundException {
		String objectAnalyzerString = "il.co.ilrd.worksheets.ws6.ObjectAnalyzer";
		printAncestor(objectAnalyzerString);
		listModifiersAndInterfaces(objectAnalyzerString);
		listMembers(objectAnalyzerString);
		ObjectAnalyzer newInstance = (ObjectAnalyzer)createNewInstance(objectAnalyzerString, null, null);
		System.out.println("\nNew Instance: " + newInstance + "\n");
		String methodToCall = "printThis";
		Object[] methodArgs = {"printThis exists"};
		System.out.println("Calling: " + methodToCall);
		callMethod(newInstance, methodToCall, new Class<?>[]{String.class}, methodArgs);
	}
}
