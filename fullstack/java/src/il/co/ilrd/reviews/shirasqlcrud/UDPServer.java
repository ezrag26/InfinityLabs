package il.co.ilrd.reviews.shirasqlcrud;

import il.co.ilrd.crud.Crud;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.sql.SQLException;

public class UDPServer extends Thread {
    Crud<Integer, String> crud;
    DatagramSocket socket;
    byte[] buffer;

    public UDPServer() throws SocketException, SQLException {
        socket = new DatagramSocket(4500);
        crud = new SqlCrud();
        buffer = new byte[1024];
    }

    public void run() {
        boolean isRunning = true;
        while (isRunning) {
            try {
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
                socket.receive(packet);
                String receivedMsg = new String(packet.getData(), 0, packet.getLength());

                if (receivedMsg.endsWith("end\n")) {
                    isRunning = false;
                }
                crud.create(receivedMsg);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        try {
            //TODO: socket.close()
            crud.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}
