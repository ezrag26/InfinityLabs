package il.co.ilrd.quizzes.runlengthencodingdecoding;
// This problem was asked by Amazon.
// Run-length encoding is a fast and simple method of encoding strings. The basic idea is to
// represent repeated successive characters as a single count and character. For example, the
// string "AAAABBBCCDAA" would be encoded as "4A3B2C1D2A".
// Implement run-length encoding and decoding. You can assume the string to be encoded have
// no digits and consists solely of alphabetic characters. You can assume the string to be decoded
// is valid.
public class RunLength {
    public static void main(String[] args) {
        String[] toEncode = {"AAAABBBCCDAA", "AAAAA", ""};
        String[] expEncode = {"4A3B2C1D2A", "5A", ""};
        String[] toDecode = {"4A3B2C1D2A", "5A", ""};
        String[] expDecode = {"AAAABBBCCDAA", "AAAAA", ""};

        for (int i = 0; i < toEncode.length; ++i) {
            String encoded = encode(toEncode[i]);
            if (!encoded.equals(expEncode[i])) {
                System.out.println("Encode failed at i: " + i);
                System.out.println(encoded);

            }

            String decoded = decode(toDecode[i]);
            if (!decoded.equals(expDecode[i])) {
                System.out.println("Decode failed at i: " + i);
                System.out.println(decoded);
            }
        }
    }

    public static String encode(String s) {
        StringBuilder encoded = new StringBuilder();
        int len = s.length();
        int i = 0;
        
        while (i < len) {
            char ch = s.charAt(i++);
            int count = 1; // has one of itself at least

            // count total times the same char appears
            while (i < len && ch == s.charAt(i)) {
                ++count;
                ++i;
            }

            encoded.append(count).append(ch);
        }

        return encoded.toString();
    }
    
    public static String decode(String s) {
        StringBuilder decoded = new StringBuilder();
        
        for (int i = 0; i < s.length(); i += 2) {
            int count = s.charAt(i) - '0'; // convert char to int, total times the char appears
            char ch = s.charAt(i + 1); // char to write

            // add char total times it appears in a row
            for (int j = 0; j < count; ++j) decoded.append(ch);
        }
        
        return decoded.toString();
    }
}
