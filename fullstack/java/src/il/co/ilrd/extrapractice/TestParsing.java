package il.co.ilrd.extrapractice;

import org.junit.Assert;
import org.junit.Test;

import java.util.HashMap;
import java.util.Map;

public class TestParsing {
	private static final String REP = "repetition";

	private int numOfRepetitions(String s, String cmpString) {
		int counter = 0;
		int length = cmpString.length();

		int index = s.indexOf(cmpString);

		while (index != -1) {
			++counter;
			index = s.indexOf(cmpString, index + length);
		}

		return counter;
	}

	@Test
	public void testParsing_String_1() {
		String input = "repetition foo 1 2 3, - repetition, *repetition*";
		int expected = 3;
		int actual = numOfRepetitions(input, REP);

		//TODO: identify how many times "repetition" appears
		Assert.assertEquals(expected, actual);
	}

	private String parseStringByType(String input, String key) {
		if (input == null) return null;

		/* doesn't take care of spaces that could be in the value, like a name
		key with value of first and last name */
		String[] keyValuesArr = input.split(" ");

		int splitLength = keyValuesArr.length;
		if (splitLength % 2 != 0) return null; //TODO: not sure if this is okay

		Map<String, String> map = new HashMap<>(splitLength / 2);

		for (int i = 0; i < splitLength; i += 2) {
			map.put(keyValuesArr[i], keyValuesArr[i + 1]);
		}

		return map.get(key);

		/* much more hardcoded */
//		Pattern pAge = Pattern.compile(" *age ([0-9]*) *");
//		Matcher mAge = pAge.matcher(input);
//
//		Pattern pName = Pattern.compile(" *name ([a-z|A-Z]*) *");
//		Matcher mName = pName.matcher(input);
//
//		switch (key) {
//			case "age":
//				if (mAge.find()) return mAge.group(1);
//			case "name":
//				if (mName.find()) return mName.group(1);
//			default:
//				return null;
//		}
	}

	@Test
	public void testParsing_String_2() {
		String input = "age 25 name joe";
		int expectedAge = 25;
		String expectedName= "joe";
		
		int actualAge = Integer.parseInt(parseStringByType(input, "age"));
		String actualName= parseStringByType(input, "name");
		
		
		//TODO: identify the age and name

		Assert.assertEquals(expectedAge, actualAge);
		Assert.assertEquals(expectedName, actualName);
	}

	private String reverseString(String s) {
		StringBuilder reversedString = new StringBuilder();
		for (int i = s.length() - 1; i >= 0; --i) {
			reversedString.append(s.charAt(i));
		}

		return reversedString.toString();
	}

	@Test
	public void testParsing_reverse_String() {
		String input = "abc123xyz";
		
		String expected = "zyx321cba";
		String actual = reverseString(input);
		
		//TODO: reverse the input string
		
		Assert.assertEquals(expected, actual);
	}
	

}
