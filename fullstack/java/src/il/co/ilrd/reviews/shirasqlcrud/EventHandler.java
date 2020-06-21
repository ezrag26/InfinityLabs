package il.co.ilrd.reviews.shirasqlcrud;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.net.*;
import java.nio.file.Path;
import java.nio.file.WatchEvent;
import java.util.function.Consumer;

public class EventHandler {
    Observer<WatchEvent<?>> obs;
    Path watchedPath;
    UdpAdapter adapter;
    FileReader fr;
    BufferedReader bf;

    public EventHandler(String watchedPath, String address, int port) throws SocketException, UnknownHostException, FileNotFoundException {
        this.watchedPath = Path.of(watchedPath);
        adapter = new UdpAdapter(address, port);

        //TODO: The FileReader instance could be created in the BufferedReader
        // ctor. If the reason for this was in order to close the FileReader,
        // the BufferedReader is supposed to close the FileReader when it closes
        fr = new FileReader(watchedPath);
        bf = new BufferedReader(fr);
        obs = new Observer<>(adapter, new onDeath());
    }

    private String readAllLines() throws IOException {
        StringBuilder content = new StringBuilder();
        String line;

        while ((line = bf.readLine()) != null) {
            content.append(line).append(System.lineSeparator());
        }
        return content.toString();
    }

    public void close() throws Exception {
        adapter.close();
        bf.close();
        fr.close();
    }

    class UdpAdapter implements Consumer<WatchEvent<?>>, AutoCloseable {
        DatagramSocket socket;
        InetAddress address;
        int port;

        public UdpAdapter(String address, int port) throws SocketException, UnknownHostException {
            socket = new DatagramSocket();
            this.address = InetAddress.getByName(address);
            this.port = port;
        }

        @Override
        public void accept(WatchEvent<?> watchEvent) {
            if (watchEvent.context().equals(watchedPath)) {
                try {
                    byte[] buf = readAllLines().getBytes();
                    DatagramPacket packet
                            = new DatagramPacket(buf, buf.length, address, port);
                    socket.send(packet);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        @Override
        public void close() throws Exception {
            socket.close();
        }
    }

    static class onDeath implements Consumer<Void> {
        @Override
        public void accept(Void v) {
            System.out.println("CRUD service is no longer available.");
        }
    }
}
