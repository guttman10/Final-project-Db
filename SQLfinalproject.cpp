/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>
#include "db.h"
#include "Q.h"
#include "Q2.h"
#define usr "root"
#define pass "38383838"
using namespace std;

int main()
{
	int switchy;
	setupdb(usr,pass);
	cout << "Pick a choice" << endl << "1. Show all books in stock" << endl << "2. Show all active orders" << endl;
	cin >> switchy;
	switch (switchy)
	{
	case 1:
		Q1(usr, pass);
		break;
	case 2:
		Q2(usr, pass);
		break;

	}
	getchar();
}