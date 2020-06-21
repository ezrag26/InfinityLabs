package il.co.ilrd.chatserver;

public interface ChatServer {
	String connectUser(User user);
	String createGroup(String groupName);
	String addUserToGroup(User user, String message);
	String setUserName(User user, String userName);
	String messageGroup(User user, String message);
	String sendErrorMessage(String message);
	String removeUserFromGroup(User user, String message);

}
