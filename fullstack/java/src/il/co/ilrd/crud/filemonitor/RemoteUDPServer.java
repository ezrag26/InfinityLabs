package il.co.ilrd.crud.filemonitor;

import il.co.ilrd.crud.Crud;
import il.co.ilrd.crud.sqlcrud.SQLCrud;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.sql.SQLException;

public class RemoteUDPServer {

    private static DatagramPacket createPacket() {
        byte[] buf = new byte[1024];
        return new DatagramPacket(buf, buf.length);
    }

    private static String extractPacketData(DatagramPacket packet) {
        return new String(packet.getData()).trim();
    }

    public static void main(String[] args) throws IOException, SQLException, Exception {
        try (Crud<Integer, String> crud = new SQLCrud(/*"user"*/);
        	 DatagramSocket server = new DatagramSocket(4444)) {
        	
        	System.out.println("Connected to socket.");
        	
        	while (true) {
        		DatagramPacket packet = createPacket();
        		
        		server.receive(packet);
        		String data = extractPacketData(packet);
        		
        		/* insert data */
        		crud.create(data);
        	}
        }
    }
}
