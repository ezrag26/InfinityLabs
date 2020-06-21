package il.co.ilrd.worksheets.ws14;

import java.io.*;
import java.net.*;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ChatServer {
	public static void main(String[] args) throws IOException {
		ExecutorService executorService = Executors.newFixedThreadPool(2);

//		String hostName = "student-HP-EliteDesk-800-G4-SFF";
		int port = Integer.parseInt(args[0]);
		MulticastSocket multicastSocket = new MulticastSocket(port);
		InetAddress group = InetAddress.getByName("224.0.0.1");

		try (ServerSocket serverSocket = new ServerSocket(port)) {
			while (true) {
				Socket socket = serverSocket.accept();
				BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
//				PrintWriter out = new PrintWriter(socket.getOutputStream());
				BufferedWriter out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));

				executorService.submit(() -> {
					String input = null;
					try {
						while (((input = in.readLine()) != null)) {
							byte[] buf = input.getBytes();
							DatagramPacket packet = new DatagramPacket(buf, buf.length, group, 8080);
							multicastSocket.send(packet);
						}
					} catch (IOException ignored) {}

					return input;
				});
			}
		} catch (IOException ignored) {}
	}
}
