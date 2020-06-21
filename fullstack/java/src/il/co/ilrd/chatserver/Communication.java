package il.co.ilrd.chatserver;

public abstract class Communication {
	Protocol protocol = new ProtocolV1();

	public abstract void send(User user, String message);
	public abstract String receive(User user);
}
