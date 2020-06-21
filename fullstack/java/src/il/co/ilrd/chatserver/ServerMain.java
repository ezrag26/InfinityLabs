package il.co.ilrd.chatserver;

import java.net.InetAddress;
import java.net.UnknownHostException;

public class ServerMain {
	public static void main(String[] args) throws UnknownHostException {
		String hostName = InetAddress.getLocalHost().getHostName();
		int port = 8080;

		Server server = new Server(hostName, port);
	}
}