package il.co.ilrd.chatserver;


import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.time.Instant;
import java.util.*;
import java.util.HashMap;

public class TCPCommunication extends Communication {
	private Server chatServer;
	private String hostName;
	private final int port;

	private static String US = "\037";
	private static final int BUFFER_SIZE = 4096;
	private ByteBuffer buffer = ByteBuffer.allocate(BUFFER_SIZE);

	private Map<Channel, User> userMap = new HashMap<>();

	public TCPCommunication(Server chatServer) {
		this.chatServer = chatServer;
		this.hostName = chatServer.getHostName();
		this.port = chatServer.getPort();
	}

	//TODO: enum for sending and receiving message
//	enum SendMessage {
//		CONNECT {
//			@Override
//			void sendMessage(User sendingUser, String message) {
//
//			}
//		},
//
//		CREATE,
//		JOIN,
//		SET_USERNAME,
//		MESSAGE,
//		ERROR,
//		EXIT;
//
//		abstract void sendMessage(User sendingUser, String message);
//	}

	@Override
	public void send(User sendingUser, String message) {
		String[] decodedPacket = protocol.decode(message);
		String action = getAction(decodedPacket);
		List<User> usersToSendMessage = new ArrayList<>();

		switch (action) {
			case "1": // connect
			case "2": // create
			case "4": // setUserName
			case "6": // error
				usersToSendMessage.add(sendingUser);
				break;
			case "3": // join
			case "5": // message
				String userGroup = sendingUser.getGroupName();
				usersToSendMessage.addAll(chatServer.getGroupMap().get(userGroup));
				break;
			case "7": // exit
				userGroup = sendingUser.getGroupName();
				List<User> users = chatServer.getGroupMap().get(userGroup);
				usersToSendMessage.addAll(users);

				/* remove from groupMap */
				sendingUser.setGroupName(null);
				users.remove(sendingUser);
				break;
			default:
		}

		for (User user : usersToSendMessage) {
			SocketChannel clientSocketChannel = (SocketChannel) user.getChannel();

			if (!clientSocketChannel.isOpen()) {
				removeUserFromGroupAfterClosedConnection(user, clientSocketChannel);
				continue;
			}

			sendMessageToUser(clientSocketChannel, message);
		}
	}

	@Override
	public String receive(User user) {

		SocketChannel clientSocketChannel = (SocketChannel)user.getChannel();
		buffer.clear();
		try {
			if (clientSocketChannel.read(buffer) == -1) {
				clientSocketChannel.close();
				System.err.println(Date.from(Instant.now()).toString() + ": " + clientSocketChannel + " has disconnected.");
				return null;
			}
		} catch (IOException ignored) {}

		String message = new String(buffer.array());
		buffer.flip();

		String[] decodedPacket = protocol.decode(message);
//		String version = getVersion(decodedPacket);
		String action = getAction(decodedPacket);
		String content = getContent(decodedPacket);

		switch (action) {
			case "2": // create
				return chatServer.createGroup(content);
			case "3": // join
				return chatServer.addUserToGroup(user, content);
			case "4": // setUserName
				return chatServer.setUserName(user, content);
			case "5": // message
				return chatServer.messageGroup(user, content);
			case "6": // error
				return chatServer.sendErrorMessage(action + US + "Illegal request.");
			case "7": // exit
				return chatServer.removeUserFromGroup(user, content);
			default: // any other number
				return chatServer.sendErrorMessage(action + US + "No such action.");
		}
	}

	public void run() {
		try {
			ServerSocketChannel serverSocketChannel = ServerSocketChannel.open();
			serverSocketChannel.configureBlocking(false);
			SocketAddress socketAddress = new InetSocketAddress(hostName, port);
			serverSocketChannel.bind(socketAddress);

			Selector selector = Selector.open();
			serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT);

			while (true) {
				selector.select();

				Set<SelectionKey> keys = selector.selectedKeys();
				Iterator<SelectionKey> iter = keys.iterator();

				while (iter.hasNext()) {
					SelectionKey key = iter.next();

					if (key.isAcceptable()) {
						/* connect new socket channel */
						SocketChannel clientSocketChannel = serverSocketChannel.accept();
						clientSocketChannel.configureBlocking(false);

						/* register to the selector */
						clientSocketChannel.register(selector, SelectionKey.OP_READ);

						/* create new user and add to userMap */
						User newUser = new User(clientSocketChannel);
						userMap.put(clientSocketChannel, newUser);
						String connectMessage = chatServer.connectUser(newUser);

						/* send connect message to user */
						send(newUser, connectMessage);

					} else if (key.isReadable()) {
						/* user of the channel */
						User user = userMap.get(key.channel());

						/* encode message from buffer */
						String encodedPacket = receive(user);

						/* send message to relevant users */
						if (encodedPacket != null) send(user, encodedPacket);
					}

					iter.remove();
				}
			}
		} catch (IOException ignored) {}
	}

	private void removeUserFromGroupAfterClosedConnection(User user, SocketChannel client) {
		chatServer.getGroupMap().get(user.getGroupName()).remove(user);
		userMap.remove(client);
		System.err.println(Date.from(Instant.now()).toString() + ": " + client + " is disconnected.");
	}

	private void sendMessageToUser(SocketChannel client, String message) {
		buffer.clear();
		buffer.put(message.getBytes());
		buffer.flip();
		try {
			client.write(buffer);
			System.err.println(Date.from(Instant.now()).toString() + ": Message sent to client " + client);
		} catch (IOException ignored) {}
	}

	public String getVersion(String[] decodedPacket) {
		return decodedPacket[0];
	}

	public String getAction(String[] decodedPacket) {
		return decodedPacket[1];
	}

	public String getContent(String[] decodedPacket) {
		return decodedPacket[2];
	}
}
