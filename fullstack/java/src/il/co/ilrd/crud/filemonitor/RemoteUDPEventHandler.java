package il.co.ilrd.crud.filemonitor;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.nio.file.Path;

public class RemoteUDPEventHandler implements EventHandler {
    private String fileToObserve;
    private final BufferedReader reader;

    public RemoteUDPEventHandler(String directoryPath, String fileToObserve) throws FileNotFoundException {
        this.fileToObserve = fileToObserve;
        reader = new BufferedReader(new FileReader(directoryPath + "/" + fileToObserve));
    }

    private DatagramPacket createPacket(String data) {
        byte[] buf = data.getBytes();
        return new DatagramPacket(buf, buf.length);
    }

    @Override
    public void accept(Path changedFile) {
        /* There was a modification in the file being observed */
        if (changedFile.endsWith(fileToObserve)) {
            try (DatagramSocket client = new DatagramSocket()) {
                /* connect to server's socket */
                client.connect(InetAddress.getByName("localhost"), 4444);

                String data;

                /* read and send each line to server */
                while ((data = reader.readLine()) != null) {

                    /* user no longer wants file to be watched */
//                    if (data.equals("end")) break;

                    /* takes care of empty lines */
                    if (data.equals("")) continue;

                    /* send to server */
                    client.send(createPacket(data));
                }
            } catch (IOException e) {
                System.out.println("send failed");
            }
        }
    }
}
