/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>
#include "db.h"
#include "Q.h"
#define usr "root"
#define pass "1234"
using namespace std;

int main()
{
	setupdb(usr,pass);
	Q1(usr, pass);
	getchar();
}