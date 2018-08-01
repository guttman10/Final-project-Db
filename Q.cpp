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
sql::Connection * getcon(string userName, string password) {
	sql::Driver *driver;
	sql::Connection *con;
	sql::ConnectOptionsMap connection_properties;

	connection_properties["hostName"] = "tcp://127.0.0.1/";
	connection_properties["port"] = 3306;
	connection_properties["OPT_RECONNECT"] = true;
	connection_properties["password"] = password;
	connection_properties["userName"] = userName;
	driver = get_driver_instance();
	con = driver->connect(connection_properties);
	con->setSchema("book_store");
	return con;
}
void Q1(string userName, string password) {

	sql::ResultSet *res;
	sql::PreparedStatement *pstmt;
	sql::Connection *con;
	con = getcon(userName, password);
	
	
	pstmt = con->prepareStatement("SELECT s.book_name FROM all_books b INNER JOIN stock s ON b.book_name = s.book_name");
	cout << "the following books are in stock" << endl;
	res = pstmt->executeQuery();
	while (res->next())
		cout<<"book name: "<<res->getString(1) << endl;

	delete con;
	delete res;
	delete pstmt;

}
void Q2(string userName, string password) {
	sql::ResultSet *res;
	sql::PreparedStatement *pstmt;
	sql::Connection *con;
	con = getcon(userName, password);


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
	sql::ResultSet *res;
	sql::PreparedStatement *pstmt;
	sql::Connection *con;
	con = getcon(userName, password);

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
	sql::ResultSet *res;
	sql::PreparedStatement *pstmt;
	sql::Connection *con;
	con = getcon(userName, password);

	pstmt = con->prepareStatement("SELECT * FROM providers");
	res = pstmt->executeQuery();
	cout << "These are the store providers" << endl;
	while (res->next())
		cout << res->getString(1) << endl;
	delete con;
	delete res;
	delete pstmt;
}

void Q5(string userName, string password) {
	sql::ResultSet *res;
	sql::PreparedStatement *pstmt;
	sql::Connection *con;
	con = getcon(userName, password);
	string start;
	string finish;
	string temp;
	cout << "Insert starting date yyyy/mm/dd: ";
	cin >> start;
	cout << "Insert ending date yyyy/mm/dd: ";
	cin >> finish;

	pstmt = con->prepareStatement("SELECT * FROM previous_purchases");
	res = pstmt->executeQuery();
	cout << "These are all the purchases from the selected dates:" << endl;
	while (res->next())
	{
		string temp = res->getString(5);
		if ((start <= temp) && (temp <= finish))
			cout << "Book Name: " << res->getString(1) << "employee ID: " << res->getString(2) << " " << "Buyer ID: " << res->getString(3) << " " << "Amount: " << res->getString(4) << " " << "Date: " << res->getString(5) << endl;
	}
	delete con;
	delete res;
	delete pstmt;
}

void Q6(string userName, string password) {
	try {
		sql::ResultSet *res;
		sql::PreparedStatement *pstmt;
		sql::Connection *con;
		con = getcon(userName, password);

		pstmt = con->prepareStatement("SELECT s.book_name,price_bought FROM all_books b INNER JOIN stock s ON b.book_name = s.book_name AND s.discount = 1");
		res = pstmt->executeQuery();
		while (res->next()) {
			int p = res->getInt(2)*1.1; 
			cout << "Book Name: " <<res->getString(1) << " Price before discount: "<<p<<" Price after discount: "<< res->getInt(2) << endl;
		}
		delete con;
		delete res;
		delete pstmt;
	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

}
void Q7(string userName, string password) {
	try {
		sql::ResultSet *res;
		sql::PreparedStatement *pstmt;
		sql::Connection *con;
		con = getcon(userName, password);

		string s;
		getchar();
		cout << "Enter the book you wish to check" << endl;
		getline(cin, s);
		pstmt = con->prepareStatement("SELECT book_name FROM stock where book_name = ?");
		pstmt->setString(1, s);
		pstmt->executeUpdate();
		res = pstmt->executeQuery();
		if (res->first())
			cout << "The book: " << res->getString(1) << " is in stock" << endl;
		else
			cout << "The book: " << s << " is not in stock" << endl;
		delete con;
		delete res;
		delete pstmt;
	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

}
void Q8(string userName, string password) {
	try {
		sql::ResultSet *res;
		sql::PreparedStatement *pstmt;
		sql::Connection *con;
		con = getcon(userName, password);

		string s;
		getchar();
		cout << "Enter the book you wish to check" << endl;
		getline(cin, s);
		pstmt = con->prepareStatement("SELECT provider_name FROM all_books where book_name = ? ");
		pstmt->setString(1, s);
		pstmt->executeUpdate();
		res = pstmt->executeQuery();
		cout << "These are the book: " << s << " provirders" << endl;
		if (res->first())
			cout << res->getString(1) << endl;
		else
			cout << "The book: " << s << " does not exists" << endl;
		delete con;
		delete res;
		delete pstmt;
	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

}
void Q9(string userName, string password) {
	try {
		sql::ResultSet *res;
		sql::PreparedStatement *pstmt;
		sql::Connection *con;
		con = getcon(userName, password);

		string name;
		string date;
		string tempName;
		string tempDate;
		int counter = 0;
		getchar();
		cout << "Enter the book you wish to check: ";
		getline(cin, name);
		cout << "Enter the Date (yyyy/mm/dd): ";
		cin >> date;
		pstmt = con->prepareStatement("SELECT * FROM previous_purchases");
		res = pstmt->executeQuery();
		while (res->next())
		{
			tempName = res->getString(1);
			tempDate = res->getString(5);
			if ((tempDate >= date) && (name == tempName))
				counter++;
		}
		cout << "The numbers of copies of this book is :" << counter << endl;
		delete con;
		delete res;
		delete pstmt;
	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
	}