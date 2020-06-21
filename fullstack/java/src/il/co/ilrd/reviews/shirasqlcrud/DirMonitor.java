package il.co.ilrd.reviews.shirasqlcrud;

import java.io.IOException;
import java.nio.file.*;

public class DirMonitor implements AutoCloseable {
    Dispatcher<WatchEvent<?>> dispatcher;
    WatchService watcher;
    Path dirPath;
    WatchKey key;

    //TODO: For the purposes of our project, we don't need to check for a
    // creation or delete event, just modification.
    public DirMonitor(Path path) throws IOException {
        dispatcher = new Dispatcher<>();
        watcher = FileSystems.getDefault().newWatchService();
        dirPath = path;
        dirPath.register(watcher,
                StandardWatchEventKinds.ENTRY_CREATE,
                StandardWatchEventKinds.ENTRY_DELETE,
                StandardWatchEventKinds.ENTRY_MODIFY);
    }

    public void subscribe(Observer<WatchEvent<?>> handler){
        dispatcher.subscribe(handler);
    }

    public void watch() throws InterruptedException {
        //TODO: I don't think take() ever returns null... If there are no
        // events, it waits. So I think this should be key = watcher.take(),
        // within a while loop on some condition, maybe while(true), or whatever
        // you think the condition should be
        while ((key = watcher.take()) != null) {
            for (WatchEvent<?> event: key.pollEvents()) {
                dispatcher.notifyAll(event);
                key.reset();
            }
        }
    }

    @Override
    public void close() throws Exception {
        dispatcher.close();
        watcher.close();
    }
}
