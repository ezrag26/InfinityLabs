package il.co.ilrd.worksheets.ws14;

import java.io.*;
import java.net.MalformedURLException;
import java.net.Socket;
import java.net.URL;

public class Ex1 {
	public static void main(String[] args) throws IOException {
		URL url = new URL("https://www.nhl.com");
		BufferedReader in = new BufferedReader(new InputStreamReader(url.openStream()));
		BufferedWriter writer = new BufferedWriter(new FileWriter("./src/il/co/ilrd/worksheets/ws14/outFile.html"));
		String input;
		while ((input = in.readLine()) != null) {
			writer.write(input);
		}
		writer.close();
		in.close();
		
		//		try (Socket clientSocket = new Socket("www.nhl.com", 80);
//		     PrintWriter out = new PrintWriter(clientSocket.getOutputStream());
//		     BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
//		     BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
//		) {
//			String input;
//			while ((input = in.readLine()) != null) {
//				System.out.println(input);
//			}
//		} catch (IOException e) {
//			e.printStackTrace();
//		}
		
		

//		String hostName = "www.martinbroadhurst.com";
//		int portNumber = 80;
//
//		try {
//			Socket socket = new Socket(hostName, portNumber);
//			PrintWriter out =
//					new PrintWriter(socket.getOutputStream(), true);
//			BufferedReader in =
//					new BufferedReader(
//							new InputStreamReader(socket.getInputStream()));
//			out.println("GET / HTTP/1.1\nHost: www.martinbroadhurst.com\n\n");
//			String inputLine;
//			while ((inputLine = in.readLine()) != null) {
//				System.out.println(inputLine);
//			}
//		} catch (Exception e) {
//			System.err.println("Don't know about host " + hostName);
//			System.exit(1);
//			System.err.println("Couldn't get I/O for the connection to " +
//					hostName);
//			System.exit(1);
//		}
	}
}
