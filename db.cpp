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
		stmt->execute("DROP TABLE IF EXISTS stock");
		stmt->execute("CREATE TABLE if not exists  stock (book_name varchar(20) primary key,quantity int,discount bool)");
		stmt->execute("INSERT INTO stock values('GuttyStory', 3, 1), ('HTML5', 6, 0), ('Algebra', 8, 0), ('assa', 1, 0), ('sadas', 6, 0)");
		stmt->execute("DROP TABLE IF EXISTS all_books");
		stmt->execute(
			"CREATE TABLE if not exists all_books(book_name varchar(20) unique,author_fname varchar(20),"
			"author_lname varchar(20),provider_name varchar(20),price_bought int,price_sold int)");
		stmt->execute(
			"INSERT INTO all_books VALUES"
			"( 'GuttyStory', 'Omer', 'Guttman', 'Vjump', 30, 60),"
			"('HTML5', 'Yonit', 'Rosho', 'Hod-Ami', 40, 50),"
			"('Algebra', 'Beni', 'Goren', 'mathOfun', 80, 110),"
			"('assa', 'Omer', 'Guttmen', 'Vjump', 30, 60),"
			"('sadas', 'Homer', 'Guttmen', 'Vjump', 30, 60),"
			"('Gflewjefwl', 'Tsomer', 'Guttmen', 'Vjump', 30, 60),"
			"('fwjknkwfe', 'Chlomer', 'Guttmen', 'Vjump', 30, 60),"
			"('wflekwefm', 'Blomer', 'Guttmen', 'Vjump', 30, 60),"
			"('nfwkjnwef', 'Stomer', 'Guttmen', 'Vjump', 30, 60),"
			"('fwnwef', 'Fomer', 'Guttmen', 'Vjump', 30, 60);"
		);
		delete stmt;
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