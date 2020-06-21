package il.co.ilrd.worksheets.ws6;

import java.lang.reflect.Field;
import java.lang.reflect.Method;

public class SyntheticContructsTest {

    class NestedClass {
        private int aField = 0;
    }

    public int getAField() {
        return new NestedClass().aField;
    }

    public void checkIfClassHasSyntheticField() {
        Field[] fields = SyntheticContructsTest.NestedClass.class.getDeclaredFields();
        for (Field f : fields) {
            System.out.print(f.getName() + ": ");
            System.out.println(f.isSynthetic());
        }
    }

    public void checkIfClassHasSyntheticMethod() {
        Method[] methods = SyntheticContructsTest.NestedClass.class.getDeclaredMethods();
        for (Method m : methods) {
            System.out.print(m.getName() + ": ");
            System.out.println(m.isSynthetic());
        }
    }

    public static void main(String[] args) {
        SyntheticContructsTest inst = new SyntheticContructsTest();
        int i = inst.getAField();
        inst.checkIfClassHasSyntheticField();
        inst.checkIfClassHasSyntheticMethod();
    }
}
