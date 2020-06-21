package il.co.ilrd.crud.sqlcrud;

import il.co.ilrd.crud.filemonitor.FileMonitor;

import java.io.IOException;

public class SQLCrudClient {
    public static void main(String[] args) throws IOException, InterruptedException {
        FileMonitor fileMonitor = new FileMonitor("src/il/co/ilrd/crud/sqlcrud", "sql_crud_file.txt");
        Thread thread = new Thread(fileMonitor::startObserving);
        thread.start();
//        Thread.sleep(10 * 1000);
//        thread.interrupt();
    }
}