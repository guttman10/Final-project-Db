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
	int switchy;
	setupdb(usr,pass);
	cout << "Pick a choice" << endl << "1. Show all books in stock" << endl << "2. Show all active orders" << endl;
	while (1) {
		cin >> switchy;
		switch (switchy)
		{
		case 1:
			Q1(usr, pass);
			break;
		case 2:
			Q2(usr, pass);
			break;
		case 3:
			Q3(usr, pass);
			break;
		case 4:
			Q4(usr, pass);
			break;
		case 6:
			Q6(usr, pass);
			break;
		case 7:
			Q7(usr, pass);
			break;

		}
	}
	getchar();
}