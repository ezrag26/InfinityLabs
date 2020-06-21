package il.co.ilrd.command;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.time.LocalDateTime;

public class WriteLog implements Command {

    public WriteLog(Object o) {}

    @Override
    public boolean execute(Object o) {
        String dataToLog = (String) o;
        /* get data from request */

        try (BufferedWriter writer = new BufferedWriter(new FileWriter("src/il/co/ilrd/serverhttp/logfile.txt", true))) {
            writer.write(LocalDateTime.now() + ": " + dataToLog + System.lineSeparator());
        } catch (IOException e) {
            e.printStackTrace();
        }

        return true;
    }
}
