package il.co.ilrd.crud.filecrud;

import il.co.ilrd.crud.filemonitor.FileMonitor;

import java.io.IOException;

public class FileCrudMain {
	public static void main(String[] args) throws IOException, InterruptedException {
		FileMonitor fileMonitor = new FileMonitor("src/il/co/ilrd/crud/filecrud", "syslog");
		fileMonitor.startObserving();
		fileMonitor.stopObserving();
	}
}
