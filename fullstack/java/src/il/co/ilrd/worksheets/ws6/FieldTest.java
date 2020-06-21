package il.co.ilrd.worksheets.ws6;

import java.lang.reflect.Field;

public class FieldTest {
	public static void main(String[] args) throws NoSuchFieldException {
		Class someClass = SomeClass.class;
		String className = someClass.getName();
		Field field = someClass.getField("anInt");
		String fieldName = field.getName();
		Object fieldType = field.getType();
		System.out.println("someClass.getName()                     : " + className);
		System.out.println("someClass.getField(\"anInt\")             : " + field);
		System.out.println("someClass.getField(\"anInt\").getName()   : " + fieldName);
		System.out.println("someClass.getField(\"anInt\").getType()   : " + fieldType);
	}
}

class SomeClass {
	public int anInt = 0;
	public String aString = "String";

	SomeClass() {

	}
}
