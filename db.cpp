#include "db.h"
#include <stdlib.h>
#include <iostream>
#include "stdafx.h"
#include "mysql_connection.h"
#include <string>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <boost/tokenizer.hpp>

using namespace std;

void setupdb(string userName, string password) {
	try {
		sql::Driver *driver;
		sql::Connection *con;

		sql::ConnectOptionsMap connection_properties;

		connection_properties["hostName"] = "tcp://127.0.0.1/";
		connection_properties["port"] = 3306;
		connection_properties["OPT_RECONNECT"] = true;
		connection_properties["password"] = password;
		connection_properties["userName"] = userName;
		sql::Statement *stmt;
		sql::ResultSet *res;
		sql::PreparedStatement *pstmt;
		/* Create a connection */
		driver = get_driver_instance();
		//con = driver->connect("tcp://127.0.0.1:3306", user, pw);
		con = driver->connect(connection_properties);
		/* Connect to the MySQL test database */

		stmt = con->createStatement();
		stmt->execute("CREATE DATABASE if not exists book_store;");
		con->setSchema("book_store");
		stmt->execute("CREATE TABLE if not exists  stock (book_id int primary key,quantity int,discount bool)");
		stmt->execute("truncate stock");
		stmt->execute("INSERT INTO stock values(1, 3, 1), (2, 6, 0), (3, 8, 0), (4, 1, 0), (5, 6, 0)");
		stmt->execute(
			"CREATE TABLE if not exists all_books(book_id int unique,book_name varchar(20),author_fname varchar(20),"
			"author_lname varchar(20),provider_name varchar(20),price_bought int,price_sold int)");
		stmt->execute("truncate all_books;");
		stmt->execute(
			"INSERT INTO all_books VALUES"
			"(1, 'GuttyStory', 'Omer', 'Guttman', 'Vjump', 30, 60),"
			"(2, 'HTML5', 'Yonit', 'Rosho', 'Hod-Ami', 40, 50),"
			"(3, 'Algebra', 'Beni', 'Goren', 'mathOfun', 80, 110),"
			"(4, 'assa', 'Omer', 'Guttmen', 'Vjump', 30, 60),"
			"(5, 'sadas', 'Homer', 'Guttmen', 'Vjump', 30, 60),"
			"(6, 'Gflewjefwl', 'Tsomer', 'Guttmen', 'Vjump', 30, 60),"
			"(7, 'fwjknkwfe', 'Chlomer', 'Guttmen', 'Vjump', 30, 60),"
			"(8, 'wflekwefm', 'Blomer', 'Guttmen', 'Vjump', 30, 60),"
			"(9, 'nfwkjnwef', 'Stomer', 'Guttmen', 'Vjump', 30, 60),"
			"(10, 'fwnwef', 'Fomer', 'Guttmen', 'Vjump', 30, 60);"
		);
		delete stmt;

		/* '?' is the supported placeholder syntax */

		stmt = con->createStatement();

		delete stmt;

		/* Select in ascending order */
		pstmt = con->prepareStatement("SELECT * from all_books");
		res = pstmt->executeQuery();

		/* Fetch in reverse = descending order! */
		while (res->next())
			cout  << res->getInt(1)<<"   "<< res->getString(2) << "   " << res->getString(3) << "   " << res->getString(4) << "   " << res->getString(5)
			<< "   " << res->getInt(6) << "   " << res->getInt(7) << endl;
		delete res;
		delete pstmt;
		delete con;

	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
	cout << endl;
}