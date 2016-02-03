//-----------------------------------------------------------------------------
//	File: DateTime.cpp
//
//	class: DateTime
//	methods:
//		DateTime(short dayOfMonth, short month = ZERO , short year = ZERO, int hour = ZERO, int minute = ZERO, int second = ZERO);
//		DateTime(void);
//		DateTime(const Date& date, const CTime& time);
//		virtual ~DateTime(void) {}
//		virtual bool operator==(const Comparable &other)const;
//		virtual bool operator!=(const Comparable &other)const
//			{return !((*this) == other);}
//		virtual bool operator<(const Comparable &other)const;
//		virtual bool operator>(const Comparable &other)const
//			{return !((*this) < other) && !((*this) == other);}
//		virtual bool operator<=(const Comparable &other)const
//			{return !((*this) > other);}
//		virtual bool operator>=(const Comparable &other)const
//			{return !((*this) < other);}
//		virtual void input(istream& sin);
//		virtual void print(ostream& sout)const;
//	Outside Of Class
//		ostream& operator<<(ostream& sout, const CTime& time);
//		istream& operator>>(istream& sin, CTime& time);
//-----------------------------------------------------------------------------
#include "DateTime.h"
namespace KG_DATETIME
{
//-----------------------------------------------------------------------------
//    Class:			DateTime
//	  Method:			DateTime::DateTime(void)
//	  Description:		default constructor for DateTime objects
//    Calls:           	CTime::setCurrentTime()
//						Date::setCurrentDate
//    Parameters:		void
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	DateTime::DateTime(void)
	{}
//-----------------------------------------------------------------------------
//    Class:			DateTime
//	  Method:			DateTime::DateTime(short dayOfMonth, short month, 
//							short year, int hour, int minute, int second)
//	  Description:		default constructor for DateTime objects
//    Calls:           	Date(dayOfMonth, month, year);
//						CTime(hour, minute, second);
//    Parameters:		short dayOfMonth, short month, short year, 
//							int hour, int minute, int second
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	DateTime::DateTime(short dayOfMonth, short month, short year, int hour, int minute, int second)
	{
		Date(dayOfMonth, month, year);
		CTime(hour, minute, second);
	}
//-----------------------------------------------------------------------------
//    Class:			DateTime
//	  Method:			DateTime::DateTime(const Date& date, const CTime& time)
//	  Description:		default constructor for DateTime objects
//    Calls:           	CTime::setCurrentTime()
//						Date::setCurrentDate
//    Parameters:		const Date& date, const CTime& time
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	DateTime::DateTime(const Date& date, const CTime& time)
	{}
//-----------------------------------------------------------------------------
//    Class:			DateTime
//	  Method:			Bool DateTime::operator==(const Comparable &other)const
//	  Description:		returns true if both the Comparable objects are exactly
//							the same         				
//	  Exceptions:		throws bad_cast if other is not a Date					
//    Parameters:		const Comparable &other
//	  Returns:			True or False
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	bool DateTime::operator==(const Comparable &other)const
	{
		try
		{
			const DateTime &otherDateTime = dynamic_cast<const DateTime&>(other);
			if(m_year == otherDateTime.m_year && m_dayOfYear ==
				otherDateTime.m_dayOfYear && m_hour == otherDateTime.m_hour &&
				m_minute == otherDateTime.m_minute)
			return true;
			return false;   
		}
		catch(bad_cast e)
		{
			return false;
		}
		return false;
    }
//-----------------------------------------------------------------------------
//    Class:			DateTime
//	  Method:			Bool DateTime::operator<(const Comparable &other)const
//	  Description:		returns true if one of the comparable objects is smaller
//							than the other				
//	  Throws:			bad_cast exception from main() if other is not a 
//							datetime
//    Called by:		partition(), SortFirstMiddleLast()
//    Parameters:		const Comparable &other
//	  Returns:			True or False
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	bool DateTime::operator<(const Comparable &other)const
	{
			const DateTime &otherDateTime = dynamic_cast<const DateTime&>(other);
			if(m_year < otherDateTime.m_year ||
				m_year == otherDateTime.m_year && m_dayOfYear < otherDateTime.m_dayOfYear ||
				m_year == otherDateTime.m_year && m_dayOfYear ==
				otherDateTime.m_dayOfYear && m_hour < otherDateTime.m_hour ||
				m_year == otherDateTime.m_year && m_dayOfYear == otherDateTime.m_dayOfYear && 
				m_hour == otherDateTime.m_hour && m_minute < otherDateTime.m_minute)
				return true;
			else
			return false;   
    }
//-----------------------------------------------------------------------------
//    Class:			DateTime
//	  Method:			void DateTime::input(istream& sin)
//	  Description:		calls the input functions for Date and CTime	
//	  Input:			sin
//	  Calls:			Date::input()
//						CTime::input()
//    Parameters:		istream& sin
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	 void DateTime::input(istream& sin)
		{
			Date::input(sin);
			CTime::input(sin);
		}
//-----------------------------------------------------------------------------
//    Class:			DateTime
//	  Method:			void DateTime::print(ostream& sout)const
//	  Description:		calls the print functions for Date and CTime
//	  Output:			sout
//	  Calls:			Date::print()
//						CTime::print()
//    Parameters:		ostream& sout
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	 void DateTime::print(ostream& sout)const
	 {
		 Date::print(sout);
		 CTime::print(sout);
	 }
//-----------------------------------------------------------------------------
//    Class:			ostream
//	  Method:			ostream& operator <<
//	  Description:		output ostream operator that calls print function
//	  Output:			sout
//    Calls:            dateTime.print(sout)
//    Parameters:		ostream& sout - output ostream function, const 
//							DateTime& dateTime - the date object to be printed
//	  Returns:			sout
//
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	ostream& operator<<(ostream& sout, const DateTime& dateTime)
	{
		dateTime.print(sout);
		return sout;
	}
	//-----------------------------------------------------------------------------
//    Class:			istream
//	  Method:			istream& operator >>
//	  Description:		input istream operator that calls input function
//	  Input:			sin
//    Calls:            dateTime.input(sin)							
//    Parameters:		istream& sin - input istream function, DateTime& dateTime 
//							- The dateTime object to be filled
//	  Returns:			sin
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	istream& operator>>(istream& sin, DateTime& dateTime)
	{
		dateTime.input(sin);
		return sin;
	}
}