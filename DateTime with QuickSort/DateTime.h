//-----------------------------------------------------------------------------
//	File: DateTime.h
//
//	class: DateTime
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//    Class:			DateTime
//    File:             DateTime.h
//    Title:            DateTime Class
//    Description:		This file contains the class definition for DateTime
//    Programmer:		Kyle Graham 
//    Date:             4/26/2015
//    Version:          1.0  
//    Environment:   Hardware: Intel i7  
//                   Software:  Windows 7
//    Compiles under Microsoft C++ 2005 
//	  class Date:
//	  Properties:			
//	  Methods:
//			Inline:
//				short getHour()const    -- accessor for m_hour
//				short getMinute()const  -- accessor for m_minute  
//				short getSecond()const  -- accessor for m_second
//
//			Non-inline:
//				DateTime(short dayOfMonth, short month = 0 , short year = 0,
//					int hour = 0, int minute = 0, int second = 0);
//				DateTime(void);
//				virtual ~DateTime(void) {}	
//				virtual bool equals(const Comparable &other)const
//				virtual lessthan(const Comparable &other)const
//				virtual void input(istream& sin)
//				virtual void print(ostream& sout)const
//				virtual void print(ostream& sout)const
//			Non-Class
//				ostream& operator<<(ostream& sout, const DateTime& dateTime)
//				istream& operator>>(istream& sin, DateTime& dateTime)
//    History Log:
//                      4/26/15  KG  completed version 1.0
// ----------------------------------------------------------------------------
#ifndef DATETIME_H
#define DATETIME_H
#include "Date.h"
#include "CTime.h"
namespace KG_DATETIME
{
	class DateTime : public Date, public CTime
	{
	public:
		DateTime(short dayOfMonth, short month = ZERO , short year = ZERO,
			int hour = ZERO, int minute = ZERO, int second = ZERO);
		DateTime(void);
		DateTime(const Date& date, const CTime& time);
		virtual ~DateTime(void) {}
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
	private:
	};
	ostream& operator<<(ostream& sout, const DateTime& dateTime);
	istream& operator>>(istream& sin, DateTime& dateTime);
}

#endif