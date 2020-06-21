package il.co.ilrd.crud.filemonitor;

import java.nio.file.Path;

public interface EventHandler {
    void accept(Path changedFile);
}
