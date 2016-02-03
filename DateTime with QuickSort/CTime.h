//-----------------------------------------------------------------------------
//	File: CTime.h
//
//	class: CTime
//-----------------------------------------------------------------------------
#pragma once
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <ctime>
#include <exception>
#include "Comparable.h"
using namespace std;
namespace KG_DATETIME
{
	const short MAXHOUR = 24;
    const short MAXMINSEC = 60;
	const short MINTIME = 0;
	
//-----------------------------------------------------------------------------
//    Class:			CTime
//    File:             CTime.h
//    Title:            CTime Class
//    Description:		This file contains the class definition for CTime
//    Programmer:		Kyle Graham  
//    Date:             4/28/2015
//    Version:          1.0 
//    Environment:   Hardware: Intel I7  
//                   Software:  WinXP or later or .NET for execution;
//    Compiles under Microsoft C++ 2012
//	  class Date:
//	  Properties:
//			int m_hour		-- 0 - 23
//			int m_minute	-- 0 - 59
//			int m_second	-- 0 - 59 
//	  Methods:
//			Inline:
//				short getHour()const    -- accessor for m_hour
//				short getMinute()const  -- accessor for m_minute  
//				short getSecond()const  -- accessor for m_second
//			Non-inline:	
//				virtual bool equals(const Comparable &other)const
//				virtual lessthan(const Comparable &other)const
//				virtual void input(istream& sin)
//				virtual void print(ostream& sout)const
//				virtual ~CTime() 
//				void setCurrentTime(void)
//				void setHour(short hour)
//				void setMinute(short minute)
//				void setSecond(short second)
//				void print(ostream& sout)const
//			Outside Of Class
//				ostream& operator<<(ostream& sout, const CTime& time);
//				istream& operator>>(istream& sin, CTime& time);
//
//    History Log:
//                      4/28/15  KG  completed version 1.0
// ----------------------------------------------------------------------------
	class CTime : virtual public Comparable
	{
	public:
		CTime(void);
		CTime(int hour, int minute = MINTIME, int second = MINTIME);	
		virtual void input(istream& sin);
		virtual void print(ostream& sout)const;
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
		// Accessors
		short getHour()const {return m_hour;}
		short getMinute()const {return m_minute;}
		short getSecond()const {return m_second;}
		// Mutators
		void setHour(short hour);
		void setMinute(short minute);
		void setSecond(short second);
		void setCurrentTime(void);
		virtual ~CTime() {}
	protected:
		int m_hour;
		int m_minute;
		int m_second;
	};
	ostream& operator<<(ostream& sout, const CTime& time);
	istream& operator>>(istream& sin, CTime& time);
}