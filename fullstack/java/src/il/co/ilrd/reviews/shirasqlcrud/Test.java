package il.co.ilrd.reviews.shirasqlcrud;

import java.io.IOException;
import java.sql.SQLException;

public class Test {
    public static void main(String[] args) throws IOException, SQLException, InterruptedException {
        new UDPServer().start();
        new FileObs("watched.txt", "localhost", 4500).observe();
    }
}
