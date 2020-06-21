package il.co.ilrd.chatserver;

import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.util.Scanner;

public class Client {
	public static void main(String[] args) throws IOException {
		Protocol protocol = new ClientProtocolV1();
		String hostName = InetAddress.getLocalHost().getHostName();
		int port = 8080;

		SocketChannel socketChannel = SocketChannel.open(new InetSocketAddress(hostName, port));
		ByteBuffer buffer = ByteBuffer.allocate(4096);

		try {
			buffer.clear();
			socketChannel.read(buffer);
		} catch (IOException ignored) {}
		String[] decodedMessage = protocol.decode(new String(buffer.array()).trim());
		System.out.println(decodedMessage[0]);

		buffer.flip();

		Thread writeThread = new Thread(new ClientWriteThread(protocol, socketChannel, buffer));
		Thread readThread = new Thread(new ClientReadThread(protocol, socketChannel, buffer));
		writeThread.start();
		readThread.start();

	}
}

class ClientWriteThread implements Runnable {

	private SocketChannel socketChannel;
	private ByteBuffer buffer;
	private Protocol protocol;

	public ClientWriteThread(Protocol protocol, SocketChannel socketChannel, ByteBuffer buffer) {
		this.socketChannel = socketChannel;
		this.buffer = buffer;
		this.protocol = protocol;
	}

	@Override
	public void run() {
		while (socketChannel.isConnected()) {
			Scanner clientInput = new Scanner(System.in);
			String encodedString = protocol.encode(null, clientInput.nextLine());

			if (encodedString == null) {
				System.out.println("Illegal input. Required valid action in format 'action: message'");
				continue;
			}

			buffer.clear();
			buffer.put(encodedString.getBytes());
			buffer.flip();
			try {
				while (buffer.hasRemaining()) {
					socketChannel.write(buffer);
				}
				buffer.clear();
			} catch (IOException ignored) {}
		}
	}
}

class ClientReadThread implements Runnable {

	private SocketChannel socketChannel;
	private ByteBuffer buffer;
	private Protocol protocol;

	public ClientReadThread(Protocol protocol, SocketChannel socketChannel, ByteBuffer buffer) {
		this.socketChannel = socketChannel;
		this.buffer = buffer;
		this.protocol = protocol;
	}

	@Override
	public void run() {
		while (socketChannel.isConnected()) {
			int bytesRead = 0;
			try {
				buffer.clear();
				bytesRead = socketChannel.read(buffer);
				buffer.flip();
			} catch (IOException ignored) {}

			if (bytesRead > 0) {
				String[] messageToUser = protocol.decode(new String(buffer.array()).trim());

				if (messageToUser[0] == null) continue;

				System.out.println(messageToUser[0]);
			}

			if (bytesRead == -1) {
				try {
					socketChannel.close();
				} catch (IOException ignored) {}
			}
		}
	}
}