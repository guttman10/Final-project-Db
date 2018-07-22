#pragma once
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
/*sorry but were not using any design pattern not to complaccait thing to much we are on a short time so please understand*/
void setupdb(string userName, string password);
