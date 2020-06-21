package il.co.ilrd.crud.filemonitor;

import il.co.ilrd.crud.directorymonitor.DirectoryMonitor;
import il.co.ilrd.observerdesignpattern.Observer;

import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.WatchEvent;
import java.nio.file.WatchKey;
import java.util.function.Consumer;

public class FileMonitor {
	private final DirectoryMonitor directoryMonitor;
	private final EventHandler clientEventHandler;

	private final Consumer<WatchKey> observerEventHandler = new Consumer<>() {
		@Override
		public void accept(WatchKey watchKey) {
			/* go through each event that occurred, see if a change happened
			in watched file */
			for (WatchEvent<?> event : watchKey.pollEvents()) {
				Path changedFile = (Path) event.context();
				clientEventHandler.accept(changedFile);
			}
		}
	};

	private final Consumer<Void> deathHandler = new Consumer<>() {
		@Override
		public void accept(Void aVoid) {
			try {
				directoryMonitor.close();
			} catch (Exception ignored) {}
		}
	};

	/**
	 * Creates a new FileMonitor object.
	 *
	 * @param directoryPath the path to the directory to observe for changes
	 * @param fileToObserve the name and extension of the file to observe
	 * @throws IOException if an I/O error occurs
	 */
	public FileMonitor(String directoryPath, String fileToObserve) throws IOException {
		directoryMonitor = new DirectoryMonitor(directoryPath);
		directoryMonitor.getDispatcher().subscribe(new Observer<>(observerEventHandler, deathHandler));
		clientEventHandler = new RemoteUDPEventHandler(directoryPath, fileToObserve);
	}

	/**
	 * Starts monitoring over the directory given at object instantiation.
	 * This method blocks until thread that calls startObserving() is
	 * interrupted, so this method should be called in another thread.
	 */
	public void startObserving() {
		directoryMonitor.run();
	}

	/**
	 * Stops monitoring over the directory given at object instantiation.
	 */
	public void stopObserving() { directoryMonitor.close(); }
}
