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
		cout<<"book name: "<<res->getString("book_name") << endl;

	delete con;
	delete res;
	delete pstmt;

}
void Q2(string userName, string password) {
	sql::ResultSet *res;
	sql::PreparedStatement *pstmt;
	sql::Connection *con;
	con = getcon(userName, password);


	pstmt = con->prepareStatement("SELECT * FROM orders where status = 'processing' ");
	cout << "These are the following active orders" << endl;
	res = pstmt->executeQuery();
	while (res->next())
		cout << endl << "book name: " << res->getString("book_name") << " Buyer ID: " << res->getInt("buyer_id") << " " << " Amount: " << res->getInt("amount")<< " Status: " << res->getString("status") << endl;
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
		cout << "Customer ID: " << res->getInt("buyer_id") << " Full Name: " << res->getString("buyer_name") << " " << " Date Joined: " << res->getString("date_joined") << endl;
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
		cout << res->getString("name") << endl;
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

	pstmt = con->prepareStatement("SELECT * FROM previous_purchases_s where date_sold between ? and ?");
	pstmt->setString(1, start);
	pstmt->setString(2, finish);
	pstmt->executeUpdate();
	res = pstmt->executeQuery();
	while (res->next())
		cout << "Book Name: " << res->getString("book_name") <<" "<< "Provider name: "<< " " << res->getString("provider_name") << " " << "amount: " << res->getInt("amount") << " " << "Date: " << res->getString("date_sold") << endl;
	
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
			int p = res->getInt("price_bought")*1.1; 
			cout << "Book Name: " <<res->getString("book_name") << " Price before discount: "<<p<<" Price after discount: "<< res->getInt("price_bought") << endl;
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
		cout << "Enter the book you wish to check: ";
		getline(cin, s);
		pstmt = con->prepareStatement("SELECT book_name FROM stock where book_name = ?");
		pstmt->setString(1, s);
		pstmt->executeUpdate();
		res = pstmt->executeQuery();
		if (res->first())
			cout << "The book: " << res->getString("book_name") << " is in stock" << endl;
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
		cout << "Enter the book you wish to check: ";
		getline(cin, s);
		pstmt = con->prepareStatement("SELECT provider_name FROM all_books where book_name = ? ");
		pstmt->setString(1, s);
		pstmt->executeUpdate();
		res = pstmt->executeQuery();
		cout << "These are the book " << s << " providers" << endl;
		if (res->first())
			cout << res->getString("provider_name") << endl;
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
		pstmt = con->prepareStatement("SELECT amount FROM previous_purchases_c where date_sold >= ? and book_name = ?");
		pstmt->setString(1, date);
		pstmt->setString(2, name);
		res = pstmt->executeQuery();
		cout << "These are the book: " << name << " amount" << endl;
		while (res->next())
			counter += res->getInt("amount");
		cout << "The amount is: " << counter;
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
void Q10(string userName, string password) {
	try {
		sql::ResultSet *res;
		sql::PreparedStatement *pstmt;
		sql::Connection *con;
		con = getcon(userName, password);

		int id;
		string date;
		string tempName;
		string tempDate;
		int counter = 0;
		getchar();
		cout << "Enter the customer id : ";
		cin >> id;
		cout << "Enter the Date (yyyy/mm/dd): ";
		cin >> date;
		pstmt = con->prepareStatement("SELECT amount FROM previous_purchases_c where date_sold >= ? and buyer_id = ?");
		pstmt->setString(1, date);
		pstmt->setInt(2, id);
		res = pstmt->executeQuery();
		cout << "These are the amount of customer: " << id << endl;
		while (res->next())
			counter += res->getInt("amount");
		cout << "The amount is:" << counter;
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
void Q11(string userName, string password) {
	try {
		sql::ResultSet *res, *res3;
		sql::PreparedStatement *pstmt;
		sql::Connection *con;
		con = getcon(userName, password);
		string date;
		int id, tid;
		int sum = 0, t = 0;
		cout << "Enter the Date (yyyy/mm/dd): ";
		cin >> date;
		pstmt = con->prepareStatement("SELECT * FROM customers");
		res = pstmt->executeQuery();
		while (res->next()) {
			tid = res->getInt(1);
			pstmt = con->prepareStatement("SELECT amount FROM previous_purchases_c where buyer_id = ? and date_sold >= ?");
			pstmt->setInt(1, tid);
			pstmt->setString(2, date);
			pstmt->executeUpdate();
			sql::ResultSet *res2 = pstmt->executeQuery();
			t = 0;
			while (res2->next()) {
				t += res2->getInt("amount");
			}
			if (t > sum) {
				sum = t;
				id = tid;
			}
			delete res2;
		}
		pstmt = con->prepareStatement("SELECT * FROM customers where buyer_id= ?");
		pstmt->setInt(1, id);
		pstmt->executeUpdate();
		res3 = pstmt->executeQuery();
		if (res3->first()) {
			cout << "The customer: " << res3->getString("buyer_name") << " ID: " << id << " who joined in: " << res3->getString("date_joined") << " has purchesed the most books as of " << date << endl
				<< "With a total of: " << sum << " purchases" << endl;
			delete res3;
		}
		else
			cout << "Something went worng" << endl;

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
void Q12(string userName, string password) {
	sql::ResultSet *res;
	sql::PreparedStatement *pstmt;
	sql::Connection *con;
	con = getcon(userName, password);
	string date;
	string Pname,maxPname;
	int sum=0, t = 0;
	cout << "Enter the Date (yyyy/mm/dd): ";
	cin >> date;
	pstmt = con->prepareStatement("SELECT * FROM providers");
	res = pstmt->executeQuery();
	while (res->next()) {
		Pname = res->getString(1);
		pstmt = con->prepareStatement("SELECT amount FROM previous_purchases_s where provider_name = ? and date_sold >= ?");
		pstmt->setString(1, Pname);
		pstmt->setString(2, date);
		pstmt->executeUpdate();
		sql::ResultSet *res2 = pstmt->executeQuery();
		t = 0;
		
		while (res2->next()) {
			t += res2->getInt("amount");
		}
		if (t > sum) {
			sum = t;
			maxPname = Pname;
		}
		delete res2;
	}
	if (t == 0) {
		cout << "No purcheses were made after this date" << endl;
		return;
	}
	cout << "The supplier: " << maxPname << " is the most purchesd from the date: " << date << " and onwards with " << sum << " books." << endl;

	delete con;
	delete res;
	delete pstmt;
}
void Q13(string userName, string password) {
	try {
		sql::ResultSet *res;
		sql::PreparedStatement *pstmt;
		sql::Connection *con;
		con = getcon(userName, password);

		string Sdate;
		string Edate;
		int counter = 0;
		getchar();
		cout << "Enter the start Date (yyyy/mm/dd): ";
		getline(cin, Sdate);
		cout << "Enter the start Date (yyyy/mm/dd): ";
		getline(cin, Edate);
		pstmt = con->prepareStatement("SELECT * FROM orders where date_order BETWEEN ? and ?");
		pstmt->setString(1, Sdate);
		pstmt->setString(2, Edate);
		res = pstmt->executeQuery();
		while (res->next())
			counter++;
		cout << "The number of orders is:" << counter;
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
void Q14(string userName, string password) {
	sql::ResultSet *res;
	sql::PreparedStatement *pstmt;
	sql::Connection *con;
	con = getcon(userName, password);
	string date1, date2;
	cout << "Enter the starting Date (yyyy/mm/dd): ";
	cin >> date1;
	cout << "Enter the end Date (yyyy/mm/dd): ";
	cin >> date2;
	pstmt = con->prepareStatement("SELECT * FROM previous_purchases_c where date_sold between ? and ?");
	pstmt->setString(1, date1);
	pstmt->setString(2, date2);
	pstmt->executeUpdate();
	res = pstmt->executeQuery();
	cout << "Those are the sale between " << date1 << " and " << date2 << endl;
	if (!res->first()) {
		cout << "No purcheses were made in those dates" << endl;
		return;
	}
	while (res->next()) {
		cout << "Book name: " << res->getString("book_name") <<" amount:  " <<res->getInt("amount")<<" date sold: "<< res->getString("date_sold") << endl;
	}
	delete con;
	delete res;
	delete pstmt;
}
void Q15(string userName, string password) {
	try {
		sql::ResultSet *res;
		sql::PreparedStatement *pstmt;
		sql::Connection *con;
		con = getcon(userName, password);
		string year;
		int id,flag=0,sum=0,dsum;
		cout << "Enter the id: ";
		cin >> id;
		cout << "Enter the Year: ";
		cin >> year;
		pstmt = con->prepareStatement("SELECT a.book_name,amount,b.price_sold FROM previous_purchases_c a inner join all_books b ON a.book_name=b.book_name AND a.buyer_id = ? AND year(date_sold) = ? order by date_sold ASC");
		pstmt->setInt(1, id);
		pstmt->setString(2, year);
		pstmt->executeUpdate();
		res = pstmt->executeQuery();
		while (res->next()) {
			sum += res->getInt("price_sold")* res->getInt("amount");
			if (sum >= 1000) {
				if (flag == 1)
				dsum += (res->getInt("price_sold")* res->getInt("amount"))*0.9;
				else {
					dsum = sum;
					flag = 1;
				}
			}
		}
		if (sum >= 1000) {
			cout << "Total discount for year: " << year << " was: " << float(sum - dsum) << endl;
		}
		else {
			cout << "No discount was given in that year" << endl;
		}
	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
}
void Q16(string userName, string password) {
	try {
		sql::ResultSet *res, *res2;
		sql::PreparedStatement *pstmt;
		sql::Connection *con;
		con = getcon(userName, password);
		int total = 0;
		int amountemp = 0;
		int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
		string bookN;
		string date;
		cout << "Type the year (yyyy): ";
		getchar();
		getline(cin, date);
		string q1s = "/01/01";
		string q1f = "/03/31";
		string q2s = "/03/01";
		string q2f = "/05/31";
		string q3s = "/07/01";
		string q3f = "/09/31";
		string q4s = "/10/01";
		string q4f = "/12/31";
		q1f.insert(0, date);
		q1s.insert(0, date);
		pstmt = con->prepareStatement("SELECT book_name,amount FROM previous_purchases_s WHERE date_sold between ? and ?");
		pstmt->setString(1, q1s);
		pstmt->setString(2, q1f);
		res = pstmt->executeQuery();
		while (res->next())
		{
			bookN = res->getString("book_name");
			amountemp = res->getInt("amount");
			pstmt = con->prepareStatement("SELECT price_sold from all_books WHERE book_name = ?");
			pstmt->setString(1, bookN);
			res2 = pstmt->executeQuery();
			while (res2->next())
				q1 += res2->getInt("price_sold")*amountemp;
		}

		pstmt = con->prepareStatement("SELECT book_name,amount FROM previous_purchases_s WHERE date_sold between ? and ?");
		pstmt->setString(1, q2s);
		pstmt->setString(2, q2f);
		res = pstmt->executeQuery();
		while (res->next())
		{
			bookN = res->getString("book_name");
			amountemp = res->getInt("amount");
			pstmt = con->prepareStatement("SELECT price_sold from all_books WHERE book_name = ?");
			pstmt->setString(1, bookN);
			res2 = pstmt->executeQuery();
			while (res2->next())
				q2 += res2->getInt("price_sold")*amountemp;
		}

		pstmt = con->prepareStatement("SELECT book_name,amount FROM previous_purchases_s WHERE date_sold between ? and ?");
		pstmt->setString(1, q3s);
		pstmt->setString(2, q3f);
		res = pstmt->executeQuery();
		while (res->next())
		{
			bookN = res->getString("book_name");
			amountemp = res->getInt("amount");
			pstmt = con->prepareStatement("SELECT price_sold from all_books WHERE book_name = ?");
			pstmt->setString(1, bookN);
			res2 = pstmt->executeQuery();
			while (res2->next())
				q3 += res2->getInt("price_sold")*amountemp;
		}

		pstmt = con->prepareStatement("SELECT book_name,amount FROM previous_purchases_s WHERE date_sold between ? and ?");
		pstmt->setString(1, q4s);
		pstmt->setString(2, q4f);
		res = pstmt->executeQuery();
		while (res->next())
		{
			bookN = res->getString("book_name");
			amountemp = res->getInt("amount");
			pstmt = con->prepareStatement("SELECT price_sold from all_books WHERE book_name = ?");
			pstmt->setString(1, bookN);
			res2 = pstmt->executeQuery();
			while (res2->next())
				q4 += res2->getInt("price_sold")*amountemp;
		}
		cout << "Total sales of year " << date << " is: " << endl << "Q1: " << q1 << " Q2: " << q2 << " Q3: " << q3 << " Q4: " << q4 << endl;
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
void Q17(string userName, string password) {
	try {
		sql::ResultSet *res;
		sql::PreparedStatement *pstmt;
		sql::Connection *con;
		con = getcon(userName, password);

		string date;
		getchar();
		cout << "Enter the Date (yyyy/mm/dd): ";
		getline(cin, date);
		pstmt = con->prepareStatement("SELECT COUNT(date_joined) FROM customers where date_joined >= ?");
		pstmt->setString(1, date);
		res = pstmt->executeQuery();
		if (res->first())
		cout << "The number of new customers is: " << res->getInt(1) << endl;
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
void Q18(string userName, string password) {
	try {
		sql::ResultSet *res, *res2;
		sql::PreparedStatement *pstmt;
		sql::Connection *con;
		con = getcon(userName, password);

		int sum = 0, amount;;
		string date1, date2,name;
		cout << "Enter the starting Date (yyyy/mm/dd): ";
		cin >> date1;
		cout << "Enter the end Date (yyyy/mm/dd): ";
		cin >> date2;
		cout << "Enter the Provider name: ";
		cin >> name;

		pstmt = con->prepareStatement("SELECT book_name,amount FROM previous_purchases_s where provider_name = ? AND date_sold between ? and ?");
		pstmt->setString(1, name);
		pstmt->setString(2, date1);
		pstmt->setString(3, date2);
		pstmt->executeUpdate();
		res = pstmt->executeQuery();
		while (res->next()) {
			pstmt = con->prepareStatement("SELECT price_bought FROM all_books where provider_name = ? AND book_name= ?");
			pstmt->setString(1, name);
			amount = res->getInt("amount");
			pstmt->setString(2, res->getString("book_name"));
			pstmt->executeUpdate();
			res2 = pstmt->executeQuery();
			while (res2->next()) {
				sum += res2->getInt("price_bought")*amount;
			}
		}
		cout << "Total purcheses from the provider: " << name << " between the dates " << date1 << " and " << date2 << " is: " << sum << endl;

	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
}
void Q19(string userName, string password) {
	try {
		sql::ResultSet *res, *res2;
		sql::PreparedStatement *pstmt;
		sql::Connection *con;
		con = getcon(userName, password);
		int id = 0;
		int total = 0;
		int amountemp = 0;
		string date;
		string bookN;
		cout << "Insert employee id: ";
		cin >> id;
		getchar();
		cout << "Type the date (yyyy/mm/dd): ";
		getline(cin, date);

		pstmt = con->prepareStatement("SELECT book_name,amount FROM previous_purchases_c WHERE employee_id = ? and date_sold >= ?");
		pstmt->setInt(1, id);
		pstmt->setString(2, date);
		res = pstmt->executeQuery();
		while (res->next())
		{
			bookN = res->getString("book_name");
			amountemp = res->getInt("amount");
			pstmt = con->prepareStatement("SELECT price_sold from all_books WHERE book_name = ?");
			pstmt->setString(1, bookN);
			res2 = pstmt->executeQuery();
			while (res2->next())
				total += res2->getInt("price_sold")*amountemp;
		}
		cout << "Total sales of employee id " << id << " is: " << total << endl;
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
void Q20(string userName, string password) {
	try {
		sql::ResultSet *res, *res2;
		sql::PreparedStatement *pstmt;
		sql::Connection *con;
		con = getcon(userName, password);
		string date1, date2;
		int counter = 0;
		cout << "Enter the starting Date (yyyy/mm/dd): ";
		cin >> date1;
		cout << "Enter the end Date (yyyy/mm/dd): ";
		cin >> date2;
		pstmt = con->prepareStatement("SELECT book_name,sum(amount) FROM previous_purchases_c where date_sold between ? and ? group by book_name order by sum(amount) desc LIMIT 10 ");
		pstmt->setString(1, date1);
		pstmt->setString(2, date2);
		pstmt->executeUpdate();
		res = pstmt->executeQuery();
		while (res->next()) {
			counter++;
			cout << counter<<". "<<res->getString("book_name") << " amount: " << res->getInt(2) << endl;;
		}
	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
}