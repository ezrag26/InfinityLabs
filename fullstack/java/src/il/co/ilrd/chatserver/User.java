package il.co.ilrd.chatserver;

import java.nio.channels.Channel;

public class User {
	private static long registeredUsers = 0;
	private long ID;
	private String userName;
	private String groupName;
	private Channel channel;

	public User(Channel channel) {
		this.ID = ++registeredUsers;
		this.userName = "user" + ID;
		this.channel = channel;
	}

	public long getID() { return ID; }

	public String getIDAsString() { return String.valueOf(ID); }

	public void setUserName(String userName) { this.userName = userName; }

	public String getUserName() { return userName; }

	public void setGroupName(String groupName) {
		this.groupName = groupName;
	}

	public String getGroupName() { return groupName; }

	public Channel getChannel() { return channel; }
}
