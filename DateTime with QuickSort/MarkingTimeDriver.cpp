//-----------------------------------------------------------------------------
//	File:		MarkingTimeDriver.cpp
//
//	Function:	main()
//-----------------------------------------------------------------------------
#include <cstdlib>
#include <iostream>
#include "ArraySort.h"
//-----------------------------------------------------------------------------
//
//	Function:	main()
//	Title:		Making a date, marking time
//	Description:	This file contains function main()
//						which tests the date/time/datetime classes and sorts
//	Programmer:	Kyle Graham   
//	Date:		5/17/15
//	Version:	1.02
//	Environment:	PC 
//				Software:   MS Windows 7
//				Compiles under Microsoft Visual C++.Net 2012
//	Input:		number of datetime objects, number of date objects, 
//				datetime objects, date objects
//	Output:		cout screen display 
//	Calls:		DateTime()
//				Date()
//				safeRead()
//				printArray()
//				quickSort()
//	Called By:	n/a
//	Exceptions: bad_cast e
//	Parameters:	None
//	Returns:	EXIT_SUCCESS  = successful 
//	History Log:
//			
//			4/28/15   KG  completed version 1.01
//			5/17/15  KG  completed verison 1.02
//-----------------------------------------------------------------------------
using namespace std;
using namespace KG_DATETIME;
int main()
{
	char c = ' ';
	int arraySize = 0;
	int arraySize2 = 0;
	Comparable** a = nullptr;
	Comparable** b = nullptr;
	DateTime current;
	CTime time;
	do
	{
		cout << "The current day and time is" << endl << current << endl;
		cout << "Enter a time (hh:mm:ss): ";
		cin >> time;
		while(!(cin))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "Bad entry.  Enter a NUMBER: " << endl;
			cin >> time;
		}
		cout << time;
		cout << "enter number of date times" << endl;
		cin >> arraySize;
		while(!cin)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "Bad entry.  Enter a NUMBER: " << endl;
			cin >> arraySize;
		}
		{
		a = new Comparable*[arraySize];
		for(int i = 0; i <  arraySize;  i++)
			a[i] = new DateTime();
		cout << "Enter " << arraySize << 
			" date(s) in dd/mm/yyyy format and time(s) in HH:MM:SS format" 
			<< endl;
		for(int i = 0; i < arraySize; i++)
		{
			cout << "Enter date/time " << i + 1 << ": ";
			safeRead(cin, a[i], 
			"Enter a date in dd/mm/yyyy format and a time in HH:MM:SS format");	
		}
		cout << "Original Array" << endl;
		try
		{
		printArray(cout, a, arraySize);
		quickSort(a, 0, arraySize - 1);
		}
		catch(bad_cast e)
		{
			cerr << "bad_cast caught: " << e.what() << endl;
		}
		cout << "Sorted Array" << endl;
		printArray(cout, a, arraySize);
		//Ran second time with only dates
		cout << "enter number of dates" << endl;
		while(!(cin >> arraySize2))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "Bad entry.  Enter a NUMBER: " << endl;
			cin >> arraySize2;
		}
		b = new Comparable*[arraySize2];
		for(int i = 0; i <  arraySize2;  i++)
			b[i] = new Date();
		cout << "Enter " << arraySize2 << 
			" date(s) in dd/mm/yyyy format " << endl;
		for(int i = 0; i <  arraySize2;  i++)
		{
			cout << "Enter date " << i + 1 << ": ";
			safeRead(cin, b[i], "Enter a date in dd/mm/yyyy format");
		}
		cout << "Original Array" << endl;
		try
		{
		printArray(cout, b, arraySize2);
		quickSort(b, 0, arraySize2 - 1);
		}
		catch(bad_cast e)
		{
			cerr << "bad_cast caught: " << e.what() << endl;
		}
		cout << "Sorted Array" << endl;
		printArray(cout, b, arraySize2);
		Date *earliestDate = dynamic_cast<Date*>(b[0]);
		Date *mostRecentDate = dynamic_cast<Date*>(b[arraySize2 - 1]);
		Date Date2 = mostRecentDate->tomorrow();
		Date Date1 = earliestDate->yesterday();
		cout <<"Day after most recent date: " << Date2 << endl;
		cout << "Day before earliest date: " << Date1 << endl;
		cout << "Run again? n for no, any key for yes" << endl;
		cin >> c;
		}	
	}
	while(c != 'n');
	delete[] a;
	delete[] b;
	for(int i = 0; i < arraySize; i++)
		{
			delete a[i];
		}
	for(int i = 0; i < arraySize2; i++)
	{
		delete b[i];
	}
	cin.get();
	return EXIT_SUCCESS;
}
