package il.co.ilrd.worksheets.ws14;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.Socket;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) throws IOException, InterruptedException {
        String hostName = args[0];
        int port = Integer.parseInt(args[1]);

        Socket clientSocket = new Socket(hostName, port);
        PrintWriter out = new PrintWriter(clientSocket.getOutputStream());
        Scanner input = new Scanner(System.in);
        System.out.println("What is your name?");
        String userName = input.nextLine();
        System.out.println("Welcome to the chat session, " + userName + "! You are now connected.");
        out.write(userName + " has entered the chat session!\n");
        out.flush();

        MulticastSocket multicastSocket = new MulticastSocket(port);
        InetAddress group = InetAddress.getByName("224.0.0.1");
        multicastSocket.joinGroup(group);

        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

        Thread sendMessage = new Thread(new SendMessageRunnable(out));
        Thread readMessage = new Thread(new ReadMessageRunnable(multicastSocket));

        sendMessage.setName(userName);
        readMessage.start();
        sendMessage.start();
        sendMessage.join();

        multicastSocket.leaveGroup(group);
        multicastSocket.close();
    }
}

class SendMessageRunnable implements Runnable {
    PrintWriter out;
    public SendMessageRunnable(PrintWriter out) {
        this.out = out;
    }

    static boolean run = true;
    public static void stop() {
        run = false;
    }

    @Override
    public void run() {
        while (run) {
            Scanner input = new Scanner(System.in);
            String message = input.nextLine();
            out.write(Thread.currentThread().getName() + ": " + message + "\n");
            out.flush();
        }
    }
}

class ReadMessageRunnable implements Runnable {
    MulticastSocket multicastSocket;

    public ReadMessageRunnable(MulticastSocket multicastSocket) {
        this.multicastSocket = multicastSocket;
    }

    private boolean shouldExit(String message) {
        String byeString = message.substring(0, Thread.currentThread().getName().length() + ": bye".length() - 1);

        return  (byeString.equals(Thread.currentThread().getName() + ": bye"));
    }

    static boolean run = true;
    public void stop() {
        run = false;
        SendMessageRunnable.stop();
    }

    @Override
    public void run() {
        while (run) {
            try {
                byte[] buf = new byte[256];
                DatagramPacket packet = new DatagramPacket(buf, buf.length);
                multicastSocket.receive(packet);

                String received = new String(packet.getData());
                if (shouldExit(received)) {
                    stop();
                } else {
                    System.out.println(received);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
