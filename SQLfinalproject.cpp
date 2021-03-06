/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>
#include "db.h"
#include "Q.h"
#define usr "root"
#define pass "38383838"
using namespace std;

int main()
{
	int switchy;
	setupdb(usr,pass);
	cout << "Pick a choice" << endl <<"0. Exit the program"<< endl << "1. Show all books in stock" << endl << "2. Show all active orders" << endl
		<< "3. Show all customers" << endl << "4. Show all providers" << endl << "5. Show purchases from selected date" << endl
		<< "6. Show all books with discount" << endl << "7. Check if specific book has discount" << endl
		<< "8. List of providers of a certain book" << endl << "9. How many copies of a certain book sold from a certain date" << endl 
		<< "10. How many copies a certain customer bought from a certain date" << endl
		<< "11. Details of the customer who bought the most book from a certain date" << endl << "12. Get the provider who we bought the most book from a certain date" << endl
		<< "13. Number of orders of books from date X to date Y" << endl
		<< "14. Number of how many orders from date X to Y became sales" << endl << "15. Total discount a customer got for Y year" << endl 
		<< "16. Total income of the store for fiscal quarter for year X" << endl << "17. How many new customers has been added since Y year" << endl 
		<< "18. Total purchases from provider X between date Z and date Y" << endl << "19. Total sales of salesman X between date Z and date Y" << endl 
		<< "20. List of top 10 most sold books between date X and date Y" << endl;
	while (1) {
		cin >> switchy;
		switch (switchy)
		{
		case 0:
			return 0;
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
		case 5:
			Q5(usr, pass);
			break;
		case 6:
			Q6(usr, pass);
			break;
		case 7:
			Q7(usr, pass);
			break;
		case 8:
			Q8(usr, pass);
			break;
		case 9:
			Q9(usr, pass);
			break;
		case 10:
			Q10(usr, pass);
			break;
		case 11:
			Q11(usr, pass);
			break;
		case 12:
			Q12(usr, pass);
			break;
		case 13:
			Q13(usr, pass);
			break;
		case 14:
			Q14(usr, pass);
			break;
		case 15:
			Q15(usr, pass);
			break;
		case 16:
			Q16(usr, pass);
			break;
		case 17:
			Q17(usr, pass);
			break;
		case 18:
			Q18(usr, pass);
			break;
		case 19:
			Q19(usr, pass);
			break;
		case 20:
			Q20(usr, pass);
			break;
		}
	}
	getchar();
}