//-----------------------------------------------------------------------------
//	File: Date.cpp
//
//	class: Date
//	methods:
//		Date::Date(short day, short month, short year)
//		bool Date::operator==(const Comparable &other)const
//		bool Date::operator<(const Comparable &other)const
//		void Date::setCurrentDate(void)
//		void Date::setDayOfWeek(void)
//		void Date::setDayOfYear(void)
//		short Date::countLeaps(short year)const
//		void Date::setDayOfMonth(short dayOfMonth)
//		void Date::setMonth(short month)
//		void Date::setYear(short year)
//-----------------------------------------------------------------------------
#include "Date.h"

namespace KG_DATETIME
{
//-----------------------------------------------------------------------------
//    Class:			Date
//	  Method:			Date::Date(short day, short month, short year) 
//							-- constructor
//	  Description:		creates a new Date object
//    Calls:            setCurrentDate()
//						daysInMonth(month, year)
//						setDayOfYear()
//						setDayOfWeek()
//						setYear()
//						setMonth()
//    Called By:		ostream& operator<<(ostream& sout, const CComplex &c)
//    Parameters:		short day		-- day to set
//						short month		-- month to set
//						short year		-- month to set
//    History Log:
//                           2/9/08  PB  completed version 1.0
// ----------------------------------------------------------------------------
	Date::Date(short day, short month, short year)
	{
       setCurrentDate();
	   if(month >= 0 && month <= MONTHSINYEAR)
	   {
			setMonth(static_cast<Months>(month));
	   }
	   if(year >= LOWYEAR)
	   {
			setYear(year);
	   }
	   if(day > 0 && day <= daysInMonth(month, year))
	   {
			setDayOfMonth(day);
			setDayOfYear();
			setDayOfWeek();
	   }
    }
//-----------------------------------------------------------------------------
//    Class:			Date
//	  Method:			bool Date::operator==(const Comparable& other)const
//	  Description:		true if the two objects are exactly the same
//    Parameters:		const Comparable &other  -- the other Date to compare
//	  Exceptions:		throws bad_cast if other is not a Date
//    Returns:          true if the two objects are exactly the same
//    History Log:
//                           2/9/08  PB  completed version 1.0
//-----------------------------------------------------------------------------
	bool Date::operator==(const Comparable &other)const
	{
		try
		{
			const Date &otherDate = dynamic_cast<const Date&>(other);
			if(m_year == otherDate.m_year && m_dayOfYear ==
				otherDate.m_dayOfYear)
				return true;
			return false;   
		}
		catch(bad_cast e)
		{
			return false;
		}
    }
//-----------------------------------------------------------------------------
//    Class:			Date
//	  Method:			bool Date::operator<(const Comparable& other)const
//	  Description:		true if the first object is smaller than the other 
//    Parameters:		const Comparable &other  -- the other Date to compare
//	  Throws:			bad_cast exception from main() if other is not a date
//    Called by:		partition(), SortFirstMiddleLast()
//    Returns:          true if the first object is smaller
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	bool Date::operator<(const Comparable &other)const
	{
			const Date &otherDate = dynamic_cast<const Date&>(other);
			if(m_year < otherDate.m_year || (m_year == otherDate.m_year &&
				m_dayOfYear < otherDate.m_dayOfYear))
				return true;
			else
			return false;
	}
//-----------------------------------------------------------------------------
//    Class:			Date
//	  Method:			void Date::setCurrentDate()
//	  Description:		sets the date from the system clock
//    Parameters:		n/a
//    Called by:		constructors, mutators
//	  Calls:			setDayOfYear(), setDayOfWeek()
//    Returns:          n/a
//    History Log:
//                           2/9/08  PB  completed version 1.0
// ----------------------------------------------------------------------------
	void Date::setCurrentDate(void)
	{
		time_t rawtime;
		tm *currentTimePtr;
		time(&rawtime);
		currentTimePtr = localtime(&rawtime);
		m_year = currentTimePtr->tm_year + 1900;
		m_month = static_cast<Months>(currentTimePtr->tm_mon + 1);
		m_dayOfMonth = currentTimePtr->tm_mday;
		setDayOfYear();
        setDayOfWeek();
	}
//-----------------------------------------------------------------------------
//    Class:			Date
//	  Method:			void Date::setDayOfWeek(void)
//	  Description:		sets the proper day of the week
//    Parameters:	    n/a
//    Called by:		input()
//    Returns:          n/a
//    History Log:
//                           4/28/15  KG  completed version 1.0
// ----------------------------------------------------------------------------
	void Date::setDayOfWeek(void)
    {
		int year = m_year;
		int month = static_cast<int>(m_month);
		static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
		year -= month < THREE;
		m_dayOfWeek = static_cast<Week>((( year + year / FOUR - year
			/ ONEHUNDRED + year / FOURHUNDRED + t[m_month-ONE] + m_dayOfMonth)
			% SEVEN) + ONE);
    }
//-----------------------------------------------------------------------------
//    Class:			Date
//	  Method:			void Date::setDayOfYear(void)
//	  Description:		sets the proper day of the year
//    Parameters:		n/a
//    Called by:		input(), constructors, SetCurrentDate()
//    Returns:          n/a
//    History Log:
//                           4/28/15  KG  completed version 1.0
// ----------------------------------------------------------------------------
	void Date::setDayOfYear(void)
    {
        int day = 0;
		int daysinmonth = 0;
		int month = m_month;
		for(int i = 1; i < month; i++)
		{
			daysinmonth = daysInMonth(i, m_year);
			day += daysinmonth;
		}
		day += m_dayOfMonth;
		m_dayOfYear = day;
    }
//-----------------------------------------------------------------------------
//    Class:			Date
//	  Method:			short Date::countLeaps(short year)const
//	  Description:		returns the number of leap years from 1760 to year
//    Calls:            isLeapYear(short)
//    Parameters:		short year - year to count leaps untill
//    Returns:          the number of leap years from 1760 to year 
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	short Date::countLeaps(short year)const
    { 
          short leaps = 0;
          for(short i = LOWYEAR; i < year; i++)
              if(isLeapYear(i))
                 leaps++; 
          return leaps;
    }

//-----------------------------------------------------------------------------
//    Class:			Date
//	  Method:			void Date::setDayOfMonth(short dayOfMonth)
//	  Description:		mutator for m_dayOfMonth
//	  Called by:		constructor
//    Calls:            daysInMonth(short, short)
//						setDayOfYear()
//						setDayOfWeek()
//    Parameters:		dayOfMonth --  day of month to set
//    Returns:			n/a
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	void Date::setDayOfMonth(short dayOfMonth)
    {
        if(dayOfMonth > ZERO && dayOfMonth <= daysInMonth(m_month, m_year))
        {
            m_dayOfMonth = dayOfMonth;
            setDayOfYear();  
            setDayOfWeek();
        }
    }
  
//-----------------------------------------------------------------------------
//    Class:			Date
//	  Method:			void Date::setMonth(short dmonth)
//	  Description:		mutator for m_month
//    Calls:            daysInMonth(short, short)
//						setDayOfYear()
//						setDayOfWeek()
//    Called By:		n/a
//    Parameters:		month --  month to set
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	void Date::setMonth(Months month)
    {
			m_month = month;
    }
 
//-----------------------------------------------------------------------------
//    Class:			Date
//	  Method:			void Date::setYear(short year)
//	  Description:		mutator for m_year
//    Calls:            isLeapYear(short)
//						setDayOfYear()
//						setDayOfWeek()
//    Parameters:		year --  year to set
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	void Date::setYear(short year)
    {	
		if(year > LOWYEAR)
			m_year = year;
	}
//-----------------------------------------------------------------------------
//    Class:			Date
//	  Method:			void Date::input(istream& sin)
//	  Description:		input function for Date objects
//	  Input:			sin
//    Calls:      		setDayOfYear()
//						setDayOfWeek()
//    Parameters:		sin -- input istream function
//
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	void Date::input(istream& sin)
	{
		string inputString;
		short day = 0;
		short year = 0;
		short month = 0;
		
		char c = ' ';
			
		if(sin >> day) // check for all bad input
		{
			if(day > 0)
			{
				setDayOfMonth(day);
				
			}
			c = ' ';
			sin.get(c);
			if(c == '\n')
			{
				sin.putback(c);
				return;
			}
			else if(c == '/')
			{
				if(sin >> month)
				{
					if(month > 0 && month <= MONTHSINYEAR)
					{
						m_month = static_cast<Months>(month);
						short days = daysInMonth(month, m_year);
						if (day > days)
						{
							setCurrentDate();
							setMonth(static_cast<Months>(month));
						}

					}
					sin.get(c);
					if(c == '\n')
					{
						sin.putback(c);
						return;
					}
					if(c == '/')
					{
						if(sin >> year)
						{
							if(year > LOWYEAR)
							{
								setYear(year);
								setYear(year);
								
							}
						}
					}
					else
						sin.setstate(std::ios::failbit);
				}
			}
			else
				sin.setstate(std::ios::failbit);
		
		}
	//setDayOfYear();  
	setDayOfWeek();	
	}
	
//-----------------------------------------------------------------------------
//    Class:			Date
//	  Method:			void Date::print(ostream& sout) const
//	  Description:		input function for Date objects
//	  Output:			sout
//    Calls:            weekdayName(m_dayOfWeek)
//						monthName(m_month)
//    Parameters:		sout -- output ostream function
//
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	void Date::print(ostream& sout)const
	{
		sout << weekdayName(m_dayOfWeek) << ", " << monthName(m_month) <<
			" " << m_dayOfMonth << ", " << m_year << endl;
		
	}
//-----------------------------------------------------------------------------
//    Class:			Date
//	  Method:			bool Date::isLeapYear(short year)
//	  Description:		checks if a input year is a leap year
//	  Called by:		daysInMonth()
//    Parameters:		short year
//    Returns:			True or false
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	 bool Date::isLeapYear(short year)
	{
		if(year % FOUR == 0)
			{
				if(year % ONEHUNDRED == 0 && year % FOURHUNDRED == 0)
				{
					return true;
				}	
				else if (year % ONEHUNDRED == 0)
					return false;
				else
					return true;
			}		
			else
				return false;
	}
//-----------------------------------------------------------------------------
//    Class:			Date
//	  Method:			const string Date::monthName(int monthNum)
//	  Description:		returns a string with the month name given a number					
//    Parameters:		int monthNum
//	  Returns:			month names in string format January - December
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	const string Date::monthName(int monthNum)
	{
		switch(monthNum)
		{
			case 0:	return "No Month";
					break;
			case 1:	return "January";
					break;
			case 2:	return "Febuary";
					break;
			case 3:	return "March";
					break;
			case 4:	return "April";
					break;
			case 5:	return "May";
					break;
			case 6:	return "June";
					break;
			case 7:	return "July";
					break;
			case 8:	return "August";
					break;
			case 9:	return "September";
					break;
			case 10: return "October";
					break;
			case 11: return "November";
					break;
			case 12: return "December";
					break;
			case 13: return "Overflow Day";
					break;
		}
		return ""; // to get rid of the not all control paths return a 
					//value error
	}
//-----------------------------------------------------------------------------
//    Class:			Date
//	  Method:			const string Date::weekdayName(int weekdayName)
//	  Description:		returns a string with the day name given a number				
//    Parameters:		int weekdayNum
//	  Returns:			day names in string format Sunday-Saturday
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	 const string Date::weekdayName(int weekdayNum)
	{	switch(weekdayNum)
		{
			case 0:	return "No Day";
					break;
			case 1:	return "Sunday";
					break;
			case 2:	return "Monday";
					break;
			case 3:	return "Tuesday";
					break;
			case 4:	return "Wednesday";
					break;
			case 5:	return "Thursday";
					break;
			case 6:	return "Friday";
					break;
			case 7:	return "Saturday";
					break;
			case 8:	return "Overflow Day";
		}
		return "";  // to get rid of the not all control paths return a 
					//value error
	}
//-----------------------------------------------------------------------------
//    Class:			ostream
//	  Method:			ostream& operator <<
//	  Description:		output ostream operator that calls print function
//	  Output:			sout
//    Calls:            date.print()
//	  Called by:		printarray()
//    Parameters:		ostream& sout - output ostream function 
//						const Date& date - the date object to be printed
//	  Returns:			sout
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	ostream& operator<<(ostream& sout, const Date& date)
	{
		date.print(sout);
		return sout;
	}
//-----------------------------------------------------------------------------
//    Class:			istream
//	  Method:			istream& operator >>
//	  Description:		input istream operator that calls input function
//	  Input:			sin
//    Calls:        	date.input(sin)
//	  Called by:		saferead()
//    Parameters:		istream& sin - input istream function, Date& date - 
//							The date object to be filled
//	  Returns:			sin
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	istream& operator>>(istream& sin, Date& date)
	{
		date.input(sin);
		return sin;
	}
//-----------------------------------------------------------------------------
//    Class:			Date
//	  Method:			Date Date::tomorrow()const
//	  Description:		increments the day forward by 1, checks if it goes
//							past the month or year
//	  Calls:			daysInMonth()
//						Date()
//	  Called by:		Main()
//	  Returns:			Date(day, month, year)
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	Date Date::tomorrow()const
	{
		short day = m_dayOfMonth + 1;
		short month = static_cast<short>(m_month);
		short year = m_year;	
		short days = daysInMonth(month, year);
		if(day > days)
		{
			day = 1;
			month++;
		}
		if(month > MONTHSINYEAR)
		{
			month = 1;
			year++;
		}
		return Date(day, month, year);
	}
//-----------------------------------------------------------------------------
//    Class:			Date
//	  Method:			Date Date::yesterday()const
//	  Description:		decrements the day back by 1, checks if it goes
//							past the month or year
//	  Calls:			daysInMonth()
//						Date()
//	  Called by:		Main()				
//	  Returns:			Date(day, month, year)
//
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	Date Date::yesterday()const
	{
		short day = m_dayOfMonth - 1;
		short month = static_cast<short>(m_month);
		short year = m_year;
		short days = daysInMonth(month, year);
		if(day == 0)
		{
			day = days;
			month--;
		}
		if(month == 0)
		{
			month = MONTHSINYEAR;
			year--;
		}
		return Date(day, month, year);
	}
//-----------------------------------------------------------------------------
//    Class:			Date
//	  method:			short Date::daysInMonth(short month, short year)
//	  description:		takes in a month and year and returns the number of 
//							days in the month given the year
//    Calls:            isLeapYear(year)					
//    Parameters:		short month, short year 						
//	  Returns:			an short of the number of days in the month
//    History Log:
//                           4/28/15  KG  completed version 1.0
//-----------------------------------------------------------------------------
	 short Date::daysInMonth(short month, short year)
	{
		switch(month)
		{
			case 1:	return 31;
					break;
			case 2:	if(isLeapYear(year))
						return 29;
					else
						return 28;
					break;
			case 3:	return 31;
					break;
			case 4:	return 30;
					break;
			case 5:	return 31;
					break;
			case 6:	return 30;
					break;
			case 7:	return 31;
					break;
			case 8:	return 31;
					break;
			case 9:	return 30;
					break;
			case 10:	return 31;
					break;
			case 11:	return 30;
					break;
			case 12:	return 31;
					break;
		}
	  // to get rid of the not all control paths return a 
					//value error
		return 31;
	}	
	}