#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>

int main() {
    // Create a MySQL driver instance
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;

    // Initialize the MySQL driver
    driver = sql::mysql::get_mysql_driver_instance();

    // Establish a connection to the database
    try {
        con = driver->connect("tcp://127.0.0.1:3306", "your_username", "your_password");
        con->setSchema("your_database_name");

        // Create a statement
        sql::PreparedStatement *pstmt;
        pstmt = con->prepareStatement("SELECT * FROM your_table_name");

        // Execute the query
        sql::ResultSet *res;
        res = pstmt->executeQuery();

        // Process the result set
        while (res->next()) {
            std::cout << "Column 1: " << res->getString(1) << std::endl;
            std::cout << "Column 2: " << res->getString(2) << std::endl;
        }

        // Clean up
        delete res;
        delete pstmt;
        delete con;
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    return 0;
}