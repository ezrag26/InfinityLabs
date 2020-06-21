package il.co.ilrd.reviews.shirasqlcrud;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.nio.file.Path;

public class FileObs {
    String fileToObserve;
    EventHandler handler;

    public FileObs(String fileToObserve, String address, int port) throws SocketException, UnknownHostException, FileNotFoundException {
        this.fileToObserve = fileToObserve;
        handler = new EventHandler(fileToObserve, address, port);
    }

    public void observe() throws IOException, InterruptedException {
        DirMonitor monitor = new DirMonitor(Path.of(fileToObserve).toAbsolutePath().getParent());
        monitor.subscribe(handler.obs);
        monitor.watch();
    }

    
}
