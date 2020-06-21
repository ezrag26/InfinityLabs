package il.co.ilrd.worksheets.jdbc;

import java.sql.*;

public class IsolationLevel {
    public static void main(String[] args) {
        Connection connection = null;

        try {
//            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/Computer_Firm", "student", "ct,h kvmkhj");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/Computer_Firm", "ezragordon", "337731418");
            printIsolationLevel(connection);

            Statement stmt = null;
            try {
                stmt = connection.createStatement();
                ResultSet rs = stmt.executeQuery("SELECT * FROM Product");
                while (rs.next()) {
                    String maker = rs.getString("maker");
                    String model = rs.getString("model");
                    String type = rs.getString("type");
                    System.out.println("Maker: " + maker + "\nModel: " + model + "\nType: " + type);
                }

                try {
                    rs.close();
                } catch (SQLException e) {
                    System.out.println("ResultSet close() failed");
                }
            } catch (SQLException e) {
                System.out.println("createStatement() failed");
            } finally {
                try {
                    if (stmt != null) stmt.close();
                } catch (SQLException e) {
                    System.out.println("Statement close() failed");
                }
            }
        } catch (SQLException e) {
            System.out.println("getConnection() failed");
            e.printStackTrace();
        } finally {
            try {
                if (connection != null) connection.close();
            } catch (SQLException e) {
                System.out.println("Connection close() failed");
            }
        }
    }

    private static void printIsolationLevel(Connection connection) {
        int level = 0;
        try {
            level = connection.getTransactionIsolation();
        } catch (SQLException e) {
            System.out.println("getTransactionIsolation() failed");
        }

        switch (level) {
            case 1:
                System.out.println("Level: " + level + " - TRANSACTION_READ_UNCOMMITTED");
                return;
            case 2:
                System.out.println("Level: " + level + " - TRANSACTION_READ_COMMITTED");
                return;
            case 4:
                System.out.println("Level: " + level + " - TRANSACTION_REPEATABLE_READ");
                return;
            case 8:
                System.out.println("Level: " + level + " - TRANSACTION_SERIALIZABLE");
                return;
            default:
                System.out.println("Level: " + level + " - TRANSACTION_NONE");
        }
    }

}
