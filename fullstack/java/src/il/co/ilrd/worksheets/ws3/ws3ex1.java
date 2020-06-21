package il.co.ilrd.worksheets.ws3;

class SuperClass {

    static {
        System.out.println("This is SuperClass's first static block");
    }

    {
        System.out.println("This is SuperClass's first instance block");
    }

    int x = 0;

    SuperClass() {
        System.out.println("This is SuperClass's constructor");
    }

    {
        System.out.println("This is SuperClass's second instance block");
    }

    static {
        System.out.println("This is SuperClass's second static block");
    }
}

class SubClass extends SuperClass {

    static {
        System.out.println("This is SubClass's first static block");
    }

    int c = 0;

    static {
        int y = 1;
        String s = "this is a string";
    }

    {
        System.out.println("This is SubClass's first instance block");
    }

    SubClass() {
        System.out.println("This is SubClass's constructor");
    }

    {
        System.out.println("This is SubClass's second instance block");
    }

    static {
        double subClassD = 3.5;
        System.out.println("This is SubClass's second static block, subClassD = " + subClassD);
    }

}
