package il.co.ilrd.crud.directorymonitor;

import il.co.ilrd.observerdesignpattern.Dispatcher;

import java.io.IOException;
import java.nio.file.*;

public class DirectoryMonitor implements AutoCloseable {
	private final WatchService watchService = FileSystems.getDefault().newWatchService();
	private final Dispatcher<WatchKey> dispatcher = new Dispatcher<>();

	/**
	 * Creates new DirectoryMonitor object.
	 *
	 * @param directoryPath the path to the directory to observe
	 * @throws IOException if an I/O error occurs
	 */
	public DirectoryMonitor(String directoryPath) throws IOException {
		Paths.get(directoryPath).register(watchService, StandardWatchEventKinds.ENTRY_MODIFY);
	}

	/**
	 * Starts monitoring of the directory given at object instantiation.
	 */
	public final void run() {
		System.out.println("File being watched.");
		try {
			while(true) {
				/* wait for a change to be make */
				WatchKey watchKey = watchService.take();

				/* notify all observers of a change */
				dispatcher.notifyAll(watchKey);

				watchKey.reset();
			}
		} catch (InterruptedException e) {
			System.out.println("File no longer being watched.");
		}
	}

	/**
	 * Gets the dispatcher of this monitor object
	 *
	 * @return the dispatcher of this monitor object
	 */
	public Dispatcher<WatchKey> getDispatcher() { return dispatcher; }

	/**
	 * Stops monitoring of the directory given at object instantiation.
	 */
	@Override
	public void close() { Thread.currentThread().interrupt(); }
}
