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
void Q1(string userName, string password) {
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
	driver = get_driver_instance();
	con = driver->connect(connection_properties);
	con->setSchema("book_store");
	
	pstmt = con->prepareStatement("SELECT s.book_name FROM all_books b INNER JOIN stock s ON b.book_name = s.book_name");
	cout << "the following books are in stock" << endl;
	res = pstmt->executeQuery();
	while (res->next())
		cout<<endl<<"book name: "<<res->getString(1) << endl;

	delete con;
	delete res;
	delete pstmt;

}
void Q2(string userName, string password) {
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
	driver = get_driver_instance();
	con = driver->connect(connection_properties);
	con->setSchema("book_store");

	pstmt = con->prepareStatement("SELECT * FROM orders");
	cout << "These are the following active orders" << endl;
	res = pstmt->executeQuery();
	while (res->next())
		cout << endl << "book name: " << res->getString(1) << " Buyer ID: " << res->getInt(2) << " " << " Amount: " << res->getInt(3)<< " Status: " << res->getString(4) << endl;
	delete con;
	delete res;
	delete pstmt;

}
void Q3(string userName, string password) {
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
	driver = get_driver_instance();
	con = driver->connect(connection_properties);
	con->setSchema("book_store");
	pstmt = con->prepareStatement("SELECT * FROM customers");
	res = pstmt->executeQuery();
	cout << "These are the store customers" << endl;
	while (res->next())
		cout << "Customer ID: " << res->getInt(1) << " Full Name: " << res->getString(2) << " " << " Date Joined: " << res->getString(3) << endl;
	delete con;
	delete res;
	delete pstmt;

}
void Q4(string userName, string password) {
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
	driver = get_driver_instance();
	con = driver->connect(connection_properties);
	con->setSchema("book_store");
	pstmt = con->prepareStatement("SELECT * FROM providers");
	res = pstmt->executeQuery();
	cout << "These are the store providers" << endl;
	while (res->next())
		cout << "Name: " << res->getString(1) << endl;
	delete con;
	delete res;
	delete pstmt;
}