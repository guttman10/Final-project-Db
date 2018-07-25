#pragma once
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

void Q1(string userName, string password);