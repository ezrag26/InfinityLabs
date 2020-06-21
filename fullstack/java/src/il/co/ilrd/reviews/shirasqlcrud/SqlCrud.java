package il.co.ilrd.reviews.shirasqlcrud;

import il.co.ilrd.crud.Crud;

import java.sql.*;

public class SqlCrud implements Crud<Integer, String> {
    String tableName = "newTable";
    Connection con;

    public SqlCrud() throws SQLException {
        con = DriverManager.getConnection("jdbc:mysql://localhost/crud?" + "user=shira&password=284053");
        System.out.println("success!");
        createTable(tableName);
    }


    public void createTable(String tableName) throws SQLException {
        String creating = "CREATE TABLE IF NOT EXISTS " + tableName + " (TEXT VARCHAR(1024))";

        try (Statement stmt = con.createStatement()) {
            stmt.executeUpdate(creating);
        }
    }

    @Override
    public Integer create(String data) {
        String toInsert = "insert into " + tableName + " values(?)";
        //TODO: In my opinion, the parsing should be handled by the EventHandler,
        // sending each line as a "new" data to be inserted. It seems to me that
        // create should be responsible for inserting the info, not parsing it
        // first and then inserting.
        String[] parseData = data.split(Character.toString('\n'));

        try(PreparedStatement statement = con.prepareStatement(toInsert)) {
            con.setAutoCommit(false);
            for (String s: parseData) {
                if (s.equals("")) continue;
                if (s.equals("end")) break;
                statement.setString(1, s);
                statement.addBatch();
            }
            con.commit();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        finally {
            try {
                con.setAutoCommit(true);
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        //TODO: I know that we totally disregarded the whole intention of the
        // key/value in our project, but I do think that we can still mimic what
        // we were supposed to do by returning some integer string if the query
        // succeeded (as well as adding the key and data to some data structure,
        // in the even that we do implement the other methods at some point) and
        // null only if it didn't succeed
        return null;
    }

    @Override
    public String read(Integer key) {
        return null;
    }

    @Override
    public String update(Integer key, String data) {
        return null;
    }

    @Override
    public String delete(Integer key) {
        return null;
    }

    @Override
    public void close() throws Exception {
        con.close();
    }
}
