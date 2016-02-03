//-----------------------------------------------------------------------------
//	File: Date.h
//
//	class: Date
//-----------------------------------------------------------------------------
#ifndef DATE_H
#define DATE_H

//-----------------------------------------------------------------------------
//    Class:			Date
//    File:             Date.h
//    Title:            Date Class
//    Description:		This file contains the class definition for Date
//    Programmer:		Kyle Graham
//    Date:             4/30/2015 
//    Version:          1.0 
//    Environment:   Hardware: Intel I7 
//                   Software:  WinXP or later or .NET for execution;
//    Compiles under Microsoft C++ 2012
//	  class Date:
//	  Properties:
//			short m_year;		// full year, i.e., 2006
//			short m_month;		// 0 - 11
//			short m_dayOfMonth; // 1 - days in that month
//			short m_dayOfYear;  // 1 - 365 or 366
//			short m_dayOfWeek;	// 0 - 6
//	  Methods:
//			Inline:
//				Static:
//					static bool isLeapYear(short year) 
//						true if year is a leap year; false otherwise
//					static short daysInMonth(short month, short year) 
//						returns the number of days in month for that year
//					static const char* monthName(int monthNum) 
//						returns a string representation of monthNum
//					static const char* weekdayName(int weekdayNum) 
//						returns a string representation of weekdayNum
//				Non-Static:
//					short getDayOfWeek()const
//					short getDayOfMonth()const
//					short getMonth()const
//					short getYear()const
//					short getDayOfYear()const
//			Non-inline:				
//					virtual bool equals(const Comparable &other)const
//					virtual lessthan(const Comparable &other)const
//					virtual void input(istream& sin)
//					virtual void print(ostream& sout)const
//					void setMonth(short monthIn)
//					void setYear(short yearIn)
//					void setCurrentDate(void)
//					void setDayOfYear(void)
//					void setDayOfWeek(void)
//					void setDayOfMonth(short dayOfMonth)
//					Date tomorrow()const
//					Date yesterday()const
//					short countLeaps(short year)const
//					void print(ostream& sout)const;
//    History Log:
//                      4/30/15  KG  completed version 1.0
// ----------------------------------------------------------------------------
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <cctype>
#include <exception>
#include "Comparable.h"
using namespace std;
namespace KG_DATETIME
{
	const short LOWYEAR = 1760;
    const short DAYSINYEAR = 365;
    const short STARTDAYOFWEEK = 2;
    const short MONTHSINYEAR = 12;
    const short DAYSINWEEK = 7;
	const int MONTH_SIZE_ARRAYSIZE = 12;
	const int WEEK_SIZE_ARRAYSIZE = 7;
	const int ZERO = 0;
	const int ONE = 1;
	const int TWO = 2;
	const int DATE_DEFAULT = -1;
	const int THREE = 3;
	const int FOUR = 4;
	const int ONEHUNDRED = 100;
	const int FOURHUNDRED = 400;
	const int SEVEN = 7;
	class Date : virtual public Comparable
	{
	public:
		enum Months
	{
		NO_MONTH,	// 0
		January,	// 1 (1-5) -- used only for owner
		Febuary,	// 2
		March,		// 3
		April,		// 4
		May,		// 5
		June,		// 6 (6-7)-- used only for other side
		July,		// 7
		August,		// 8
		September,	// 9
		October,	//10
		November,	//11 
		December,	//12
		OVERFLOW_MONTH, //13
	}; 	
		enum Week
	{       NO_DAY,			//0
			Sunday,			//1
			Monday,			//2
			Tuesday,		//3
			Wednesday,		//4
			Thursday,		//5
			Friday,			//6
			Saturday,		//7	
			OVERFLOW_DAY,	//8
	};
		Date(short day = DATE_DEFAULT, short month = DATE_DEFAULT , short year = DATE_DEFAULT);
	
		virtual ~Date(void) {}
		// pure virtuals that MUST be defined
		virtual bool operator==(const Comparable &other)const;
		virtual bool operator!=(const Comparable &other)const
			{return !((*this) == other);}
		virtual bool operator<(const Comparable &other)const;
		virtual bool operator>(const Comparable &other)const
			{return !((*this) < other) && !((*this) == other);}
		virtual bool operator<=(const Comparable &other)const
			{return !((*this) > other);}
		virtual bool operator>=(const Comparable &other)const
			{return !((*this) < other);}
		virtual void input(istream& sin);
		virtual void print(ostream& sout)const;
		// mutators
	private:
		void setDayOfYear(void);
		void setDayOfWeek(void);
	public:
		void setDay(Week dayOfWeek){m_dayOfWeek = dayOfWeek;}
		void setCurrentDate(void);
		void setDayOfMonth(short dayOfMonth);
		void setMonth(Months month);
		void setYear(short yearIn);
		short countLeaps(short year)const;
		//accessors
		short getDayOfWeek()const {return m_dayOfWeek;}
		short getDayOfMonth()const {return m_dayOfMonth;}
		short getMonth()const {return m_month;}
		short getYear()const {return m_year;}
		short getDayOfYear()const {return m_dayOfYear;}
		Date tomorrow()const;
		Date yesterday()const;
		//statics
		static bool isLeapYear(short year);
		static short daysInMonth(short month, short year);
		static const string monthName(int monthNum);	
		static const string weekdayName(int weekdayNum);
		operator Week() const{return m_dayOfWeek;} 
	protected:
		short m_year;  // full year, i.e., 2012
		Months m_month;
		short m_dayOfMonth; // 1 - days in that month
		short m_dayOfYear;  // 1 - 365 or 366
		Week m_dayOfWeek;	// 0 - 6
	};
	ostream& operator<<(ostream& sout, const Date& date);
	istream& operator>>(istream& sin, Date& date);
}
#endif
