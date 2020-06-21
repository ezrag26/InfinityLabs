package il.co.ilrd.randomtests.genericlistsandarrays;

public class GenericListVsArray {
    public static void main(String[] args) {
        Integer[] list = {1, 2, 3, 4};
        printThis(list);
    }
    
    static <E> void printThis(E[] list) {
        /* all give compilation errors */
//        ArrayList<E>[] l = new ArrayList<>[];
//        E[] l2 = new E[];
//        List<String>[] l3 = new List<String>[];
    }
}
