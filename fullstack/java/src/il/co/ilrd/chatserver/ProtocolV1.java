package il.co.ilrd.chatserver;

public class ProtocolV1 implements Protocol {
	private static String version = "v1";
	private static final String STX = "\002", ETX = "\003", DC1 = "\021";

	@Override
	public String encode(String action, String content) {

		return STX + DC1 + version + DC1 + action + DC1 + content + DC1 + ETX;
	}

	@Override
	public String[] decode(String message) {
		//TODO: regex pattern matcher
//		Pattern pattern = Pattern.compile("(\002)(\021)(.)+(\021)(.)+(\021)(.)+(\021)(\003)");
//		Matcher matcher = pattern.matcher(message);
//		System.out.println(matcher.matches());
		String[] strings = message.split(DC1);
		String[] decodedString = new String[3];

		decodedString[0] = strings[1];
		decodedString[1] = strings[2];
		decodedString[2] = strings[3];

		return decodedString;
	}
}
