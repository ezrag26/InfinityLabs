package il.co.ilrd.crud.sqlcrud;

import il.co.ilrd.crud.Crud;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.HashMap;
import java.util.Map;

public class SQLCrud implements Crud<Integer, String> {
    private final Map<Integer, String> rows = new HashMap<>();
    private Integer key = 0;
//    private String database;
    private String table = "user";
    private String url = "jdbc:mysql://localhost:3306/user_info";
//    private final String user = "ezragordon";
//    private final String pass = "337731418";
    private String user = "student";
    private String pass = "ct,h kvmkhj";
    private final Connection connection;

    public SQLCrud(/*String database, String table*/) throws SQLException {
//        this.database = database;
//        this.url = "jdbc:mysql://localhost:3306/" + database;
        connection = DriverManager.getConnection(url, user, pass);
        createTable();
    }

    private void createTable() {
        try (Statement stmt = connection.createStatement()) {
            stmt.executeUpdate("CREATE TABLE IF NOT EXISTS " + table +
                    "(id int NOT NULL AUTO_INCREMENT, " +
                    "first varchar(20) NOT NULL, " +
                    "last varchar(20) NOT NULL, " +
                    "user_name varchar(20) NOT NULL, " +
                    "age smallint, " +
                    "email varchar(50) NOT NULL, " +
                    "PRIMARY KEY (id))");
        } catch (SQLException e) { System.out.println("create table failed");}
    }

    private String sqlInsertDataToTable(String table, String data) {
        return "INSERT INTO " + table + " VALUES(" + data + ")";
    }

    /**
     * Inserts data into this SQLCrud database's table
     *
     * @param data the data to insert to the table
     * @return the key associated with this row if the data was successfully
     * inserted, or null if the data could not be inserted
     */
    @Override
    public Integer create(String data) {
        try (Statement stmt = connection.createStatement()) {
            stmt.executeUpdate(sqlInsertDataToTable(table, data));

            rows.put(++key, data);

            return key;
        } catch (SQLException ignored) {
            System.out.println("Could not insert data. Make sure inserted data follows correct format.");
        }

        return null;
    }

    @Override
    public String read(Integer key) {
        throw new UnsupportedOperationException();
    }

    @Override
    public String update(Integer key, String data) {
        throw new UnsupportedOperationException();
    }

    @Override
    public String delete(Integer key) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void close() throws Exception { connection.close(); }
}
