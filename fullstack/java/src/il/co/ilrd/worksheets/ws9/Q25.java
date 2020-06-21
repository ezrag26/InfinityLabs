package il.co.ilrd.worksheets.ws9;

import java.util.ArrayList;
import java.util.List;

public class Q25 {
	public static void main(String[] args) {

//		List<Object> objectList;
//		List<String> stringList;
//		objectList = stringList;

		List rawList/* = new ArrayList()*/;
//		rawList.add(1);
//		String s = rawList.get(0);
		List<?> listOfAnyType/* = new ArrayList<>()*/;
		List<Object> listOfObject = new ArrayList<Object>();
		List<String> listOfString = new ArrayList<String>();
		List<Integer> listOfInteger = new ArrayList<Integer>();

//		rawList = listOfAnyType;
		rawList = listOfString;
		rawList = listOfInteger;
		listOfAnyType = listOfString;
		listOfAnyType = listOfInteger;
//		listOfObject = (List<Object>) listOfString;
	}
}
