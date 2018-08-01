#pragma once
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
sql::Connection* getcon(string userName, string password);
void Q1(string userName, string password);
void Q2(string userName, string password);
void Q3(string userName, string password);
void Q4(string userName, string password);
void Q5(string userName, string password);
void Q6(string userName, string password);
void Q7(string userName, string password);
void Q8(string userName, string password);
void Q9(string userName, string password);
void Q10(string userName, string password);
void Q11(string userName, string password);
void Q12(string userName, string password);
void Q13(string userName, string password);
void Q14(string userName, string password);