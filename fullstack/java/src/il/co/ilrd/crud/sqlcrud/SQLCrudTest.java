package il.co.ilrd.crud.sqlcrud;

import java.sql.SQLException;

public class SQLCrudTest {
    public static void main(String[] args) throws SQLException {
        SQLCrud sqlCrud = new SQLCrud();

        sqlCrud.create("NULL, 'Ezra', 'Gordon', 'ezrag26', 24, 'ezrag26@gmail.com'");
        sqlCrud.create("NULL, 'Shiri', 'Gordon', 'shiri22577', 23, 'toni22577@gmail.com'");

        try {
            sqlCrud.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
