package il.co.ilrd.chatserver;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Server implements ChatServer {

	private String hostName;
	private int port;

	private Map<String, List<User>> groupMap = new HashMap<>();
	private Communication communication;
	private static final char US = 0x1F;

	private enum Actions {
		CONNECT("1"),
		CREATE("2"),
		JOIN("3"),
		SET_USERNAME("4"),
		MESSAGE("5"),
		ERROR("6"),
		EXIT("7");

		String id;

		Actions(String id) { this.id = id; }
	}

	public Server(String hostName, int port) {
		this.hostName = hostName;
		this.port = port;
		communication = new TCPCommunication(this);
		((TCPCommunication)communication).run();
	}

	public String getHostName() { return this.hostName; }

	public int getPort() { return this.port; }

	public Map<String, List<User>> getGroupMap() { return groupMap; }

	public String connectUser(User user) {
		return communication.protocol.encode(Actions.CONNECT.id, user.getIDAsString());
	}

	@Override
	public String createGroup(String groupName) {
		String content;
		String action;

		if (groupMap.containsKey(groupName)) {
			action = Actions.ERROR.id;
			content = Actions.CREATE.id + US + groupName;
		} else {
			groupMap.put(groupName, new ArrayList<>());
			action = Actions.CREATE.id;
			content = groupName;
		}

		return communication.protocol.encode(action, content);
	}

	@Override
	public String addUserToGroup(User user, String groupName) {
		String content;
		String action;

		if (user.getGroupName() != null) {
			action = Actions.ERROR.id;
			content = Actions.JOIN.id + US + "Already assigned to group " + user.getGroupName();
		} else if (!groupMap.containsKey(groupName)) {
			action = Actions.ERROR.id;
			content = Actions.JOIN.id + US + "Group '" + groupName + "' does not exist.";
		} else {
			groupMap.get(groupName).add(user);
			user.setGroupName(groupName);
			action = Actions.JOIN.id;
			content = user.getIDAsString() + US + user.getUserName() + US + groupName;
		}

		return communication.protocol.encode(action, content);
	}

	@Override
	public String setUserName(User user, String userName) {
		user.setUserName(userName);
		return communication.protocol.encode(Actions.SET_USERNAME.id, userName);
	}

	@Override
	public String messageGroup(User user, String message) {
		String content;
		String action;

		if (user.getGroupName() == null) {
			action = Actions.ERROR.id;
			content = Actions.JOIN.id + US + "Join a group in order to send a message";
		} else {
			action = Actions.MESSAGE.id;
			content = user.getIDAsString() + US + user.getUserName() + US + message;
		}

		return communication.protocol.encode(action, content);
	}

	@Override
	public String sendErrorMessage(String message) {
		return communication.protocol.encode(Actions.ERROR.id, message);
	}

	@Override
	public String removeUserFromGroup(User user, String message) {
		String content;
		String action;

		if (user.getGroupName() == null) {
			content = Actions.EXIT.id + US + user.getUserName() + " is not part of any group.";
			action = Actions.ERROR.id;
		} else {
			content = user.getIDAsString() + US + user.getUserName() + US + message;
			action = Actions.EXIT.id;
		}

		return communication.protocol.encode(action, content);
	}
}
