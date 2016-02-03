//-----------------------------------------------------------------------------
//	File: ArraySort.h
//
//	functions:
//	void quickSort(Comparable** array, int fromIndex, int toIndex);
//	int partition(Comparable** array, int fromIndex, int toIndex);
//	void SortFirstMiddleLast(Comparable** array, int fromIndex,
//			int midIndex, int toIndex);
//	void insertionSort(Comparable** array, int fromIndex, int toIndex);
//	void safeRead(istream& sin, Comparable* d, const char* prompt);
//	void printArray(ostream & sout, Comparable **array, int size);
//-----------------------------------------------------------------------------
#ifndef ARRAYSORT_H
#define ARRAYSORT_H
#include <iostream>
#include <fstream>
#include "DateTime.h"
using namespace std;
using namespace KG_DATETIME;
//----------------------------------------------------------------------------
// One of two choices for format of these function
// This set uses an array and indices within the array
//----------------------------------------------------------------------------
namespace KG_DATETIME
{	
	void quickSort(Comparable** array, int fromIndex, int toIndex);	
	int partition(Comparable** array, int fromIndex, int toIndex);
	void SortFirstMiddleLast(Comparable** array, int fromIndex,
		int midIndex, int toIndex);	
	void insertionSort(Comparable** array, int fromIndex, int toIndex);	
	void safeRead(istream& sin, Comparable* d, const char* prompt);
	void printArray(ostream & sout, Comparable **array, int size);
	void swap(Comparable*& a, Comparable*& b);
}
#endif