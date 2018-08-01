#include "db.h"
#include <stdlib.h>
#include <iostream>
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
		stmt->execute("INSERT INTO stock values('GuttyStory', 3, 1), ('HTML5', 6, 0), ('Algebra', 8, 0), ('Fairy Tail', 1, 0), ('Bleach', 6, 0)");
		stmt->execute("DROP TABLE IF EXISTS all_books");
		stmt->execute(
			"CREATE TABLE if not exists all_books(book_name varchar(20) unique,author_fname varchar(20),"
			"author_lname varchar(20),provider_name varchar(20),price_bought int,price_sold int)");
		stmt->execute(
			"INSERT INTO all_books VALUES"
			"( 'GuttyStory', 'Omer', 'Guttman', 'Vjump', 30, 60),"
			"('HTML5', 'Yonit', 'Rosho', 'Hod-Ami', 40, 50),"
			"('Algebra', 'Beni', 'Goren', 'mathOfun', 80, 110),"
			"('Fairy Tail', 'Malcolm', 'Howe', 'BK-fun', 50, 60),"
			"('Bleach', 'Jadine', 'Gray', 'Konda', 10, 20),"
			"('One Piece', 'Arla', 'Conway', 'Monda', 20, 40),"
			"('Death Note', 'Teagan', 'Griffin', 'Hoshima', 80, 160),"
			"('All my sons', 'Rabia', 'Goldsmith', 'Kadosh', 200, 350),"
			"('HOT', 'Stomer', 'Mitchell', 'Kovalovsky', 10, 15),"
			"('Yes', 'Fomer', 'Safah', 'Cohen books', 50, 100);"
		);
		stmt->execute("DROP TABLE IF EXISTS orders");
		stmt->execute("CREATE TABLE if not exists orders (book_name varchar(20),buyer_id int,employee_id int ,amount int, status varchar(20), date_order date )");
		stmt->execute("INSERT INTO orders values('Fairy Tail', 1, 1, 3, 'shipped','2017/03/25'),('All my sons',2,2,5, 'shipped','2013/05/18'),('Fairy Tail',3,3,9, 'shipped','2011/03/14') ,('GuttyStory',4,4,8, 'shipped','2016/05/04'), ('HTML5',2, 2,2, 'processing','2004/05/08'), ('Algebra', 3, 3,1, 'canceled','2005/05/08')");
		stmt->execute("DROP TABLE IF EXISTS customers");
		stmt->execute("CREATE TABLE if not exists customers(buyer_id int unique,buyer_name varchar(20),date_joined date);");
		stmt->execute("INSERT INTO customers VALUES(1, 'Ofir Cohen', '2000/01/13'),(2, 'Omer Guttman', '2010/03/09'),"
		"(3, 'Daniel Kovalevski', '1998/06/03'),(4, 'Tomer LoSMASH', '2008/04/19');");
		stmt->execute("DROP TABLE IF EXISTS providers");
		stmt->execute("CREATE TABLE if not exists providers (name varchar(20) unique)");
		stmt->execute("INSERT INTO providers VALUE('Hod-Ami'), ('Vjump'), ('mathOfun'), ('BK-fun'), ('Kadosh');");
		stmt->execute("DROP TABLE IF EXISTS previous_purchases_c");
		stmt->execute("CREATE TABLE if not exists previous_purchases_c (book_name varchar(20), employee_id int ,buyer_id int, amount int, date_sold date)");
		stmt->execute("INSERT INTO previous_purchases_c VALUES('Fairy Tail',1,1,3,'2017/03/25'),('All my sons',2,2,5,'2013/05/18'),('Fairy Tail',3,3,9,'2011/03/14'),('GuttyStory',4,4,8,'2016/05/04');");
		stmt->execute("DROP TABLE IF EXISTS previous_purchases_s");
		stmt->execute("CREATE TABLE if not exists previous_purchases_s (book_name varchar(20), provider_name varchar(20), amount int, date_sold date)");
		stmt->execute("INSERT INTO previous_purchases_s VALUES('Fairy Tail','BK-fun',3,'2017/03/25'),('All my sons','Kadosh',5,'2013/05/18'),('Fairy Tail','BK-fun',9,'2011/03/14'),('GuttyStory','Vjump',8,'2015/05/04');");

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
}