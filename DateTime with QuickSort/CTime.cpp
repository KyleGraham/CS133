//-----------------------------------------------------------------------------
//	File: CTime.cpp
//	class: CTime
//	methods:
//		void CTime::setCurrentTime()
//		virtual bool equals(const Comparable &other)const
//		virtual lessthan(const Comparable &other)const
//		virtual void input(istream& sin)
//		virtual void print(ostream& sout)const
//		virtual ~CTime() 
//		void setCurrentTime(void)
//		void setHour(short hour)
//		void setMinute(short minute)
//		void setSecond(short second)
//		void print(ostream& sout)const
//	Outside Of Class
//		ostream& operator<<(ostream& sout, const CTime& time);
//		istream& operator>>(istream& sin, CTime& time);
//-----------------------------------------------------------------------------
#include "CTime.h"
namespace KG_DATETIME
{
//-----------------------------------------------------------------------------
//    Class:			CTime
//	  Method:			CTime::CTime(int hour, int minute, int second)
//	  Description:		constructor for CTime objects
//    Calls:            setHour(), setMinute(), setSecond()
//    Called By:		main() 
//    Parameters:		int hour, int minute, int second
//    Returns:          n/a 
//    History Log:
//                           4/28/15  KG  completed version 1.0
// ----------------------------------------------------------------------------
	CTime::CTime(int hour, int minute, int second)
	{
		setCurrentTime();
		if(hour >= 0 && hour < MAXHOUR)
			setHour(hour);
		if(minute >= 0 && minute < MAXMINSEC)
			setMinute(minute);
		if(second >= 0 && minute < MAXMINSEC)
			setSecond(second);
	}
//-----------------------------------------------------------------------------
//    Class:			CTime
//	  Method:			CTime::CTime(void)
//	  Description:		default constructor for CTime objects  
//    Calls:            setCurrentTime()
//    Called By:		main()
//    Parameters:		void
//    Returns:          n/a 
//    History Log:
//                           4/28/15  KG  completed version 1.0
// ----------------------------------------------------------------------------
	CTime::CTime(void)
	{
		setCurrentTime();
	}
//-----------------------------------------------------------------------------
//    Class:			CTime
//	  Method:			void CTime::setCurrentTime()
//	  Description:		sets the time from the system clock
//    Called By:		constructor, mutators
//    Parameters:		none
//    Returns:          n/a 
//    History Log:
//                      2/9/08  PB  completed version 1.0
// ----------------------------------------------------------------------------
	void CTime::setCurrentTime()
	{
		time_t rawtime;
		tm *currentTimePtr;
		time(&rawtime);
		currentTimePtr = localtime(&rawtime);

		m_hour = currentTimePtr->tm_hour;
		m_minute = currentTimePtr->tm_min;
		m_second = currentTimePtr->tm_sec;
	}
//-----------------------------------------------------------------------------
//    Class:			CTime
//	  Method:			bool CTime::operator<(const Comparable &other)const
//	  Description:		The less than operator for CTime objects
//    Called By:		constructor, mutators
//    Parameters:		const Comparable &other
//	  Throws:			bad_cast exception from main() if other is not a time
//    Called by:		partition(), SortFirstMiddleLast() 
//    Returns:          true or false
//    History Log:
//                      4/29/15  KG  completed version 1.0
// ----------------------------------------------------------------------------
	bool CTime::operator<(const Comparable &other)const
		{
		
			const CTime &otherTime = dynamic_cast<const CTime&>(other);
			if(m_hour < otherTime.m_hour || m_hour == otherTime.m_hour &&
				m_minute < otherTime.m_minute || m_hour == otherTime.m_hour && 
				m_minute == otherTime.m_minute && m_second < otherTime.m_second)
				return true;
			else
			return false;   
		
		}
//-----------------------------------------------------------------------------
//    Class:			CTime
//	  Method:			bool CTime::operator==(const Comparable &other)const
//	  Description:		The equals to operator for CTime objects   
//    Called By:		constructor, mutators
//    Parameters:		const Comparable &other
//    Returns:          true or false
//    History Log:
//                      4/29/15  KG  completed version 1.0
// ----------------------------------------------------------------------------
	bool CTime::operator==(const Comparable &other)const
	{
			try
		{
			const CTime &otherTime = dynamic_cast<const CTime&>(other);
			if(m_hour == otherTime.m_hour && m_minute ==
				otherTime.m_minute && m_second == otherTime.m_second)
				return true;
			return false;   
		}
		catch(bad_cast e)
		{
			return false;
		}
	}
//-----------------------------------------------------------------------------
//    Class:			CTime
//	  Method:			void CTime::input(istream& sin)
//	  Description:		input method for CTime objects
//	  Input:			sin
//    Called By:		constructor from DateTime/CTime, mutators, saferead
//    Parameters:		istream& sin - input istream
//    Returns:          n/a
//    History Log:
//                      4/29/15  KG  completed version 1.0
// ----------------------------------------------------------------------------
	void CTime::input(istream& sin)
	{
		int hour = 0;
		int minute = 0;
		int second = 0;
		m_hour = hour;
		m_second = second;
		m_minute = minute;
		char c = ' ';
		sin.get(c);
		if(c == '\n') //checks for no input if datetime
		{
			sin.putback(c);
			return;
		}
		sin.putback(c); //puts back character if normal input
		if(sin >> hour)
		{
			if(hour > MINTIME && hour <= MAXHOUR)
				m_hour = hour;
			sin.get(c);
			if(c == '\n')
			{
				sin.putback(c);
				return;
			}
			if(c == ':')
			{
				if(sin >> minute)
				{
					if(minute > MINTIME && minute < MAXMINSEC)
					{
						m_minute = minute;
					}
					sin.get(c);
					if(c == '\n')
					{
						sin.putback(c);
						return;
					}
					if(c == ':')
					{
						if(sin >> second)
						{
							if(second > MINTIME && second < MAXMINSEC)
							{
								m_second = second;
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
	}
//-----------------------------------------------------------------------------
//    Class:			CTime
//	  Method:			void CTime::print(istream& sout) const
//	  Description:		print method for CTime objects
//	  Output:			sout
//    Called By:		constructor, mutators, operator<<
//    Parameters:		ostream& sout - output ostream
//    History Log:
//                      4/29/15  KG  completed version 1.0
// ----------------------------------------------------------------------------
	void CTime::print(ostream& sout) const
	{
			sout << setw(2) << setfill('0') << m_hour << ":" << setw(2) << 
				setfill('0') <<  m_minute << ":"  << setw(2) << setfill('0') 
				<< m_second << endl;
	}
//-----------------------------------------------------------------------------
//   
//	  Method:			ostream& operator <<(ostream& sout, const CTime& time
//	  Description:		output operator for CTime objects
//	  Output:			sout
//	  Calls:			time.print()
//    Called By:		main()
//    Parameters:		ostream& sout, const CTime& time
//    Returns:          sout - output ostream
//    History Log:
//                      4/29/15  KG  completed version 1.0
// ----------------------------------------------------------------------------
	ostream& operator<<(ostream& sout, const CTime& time)
	{
		time.print(sout);
		return sout;
	}
//-----------------------------------------------------------------------------
//   
//	  Method:			istream& operator >>(ostream& sout, const CTime& time)
//	  Description:		input operator for CTime objects  
//    Input:			sin
//    Calls:            time.input()
//    Called By:		saferead()
//    Parameters:		istream& sin, CTime& time
//    Returns:          sin - input istream
//    History Log:
//                      4/29/15  KG  completed version 1.0
// ----------------------------------------------------------------------------
	istream& operator>>(istream& sin, CTime& time)
	{
		time.input(sin);
		return sin;
	}
//-----------------------------------------------------------------------------
//    Class:			CTime
//	  Method:			void CTime::setHour(short hour)
//	  Description:		mutator for m_hour  
//    Called By:		CTime(hour, minute, second) 
//    Parameters:		short hour
//    Returns:          n/a
//    History Log:
//                      4/29/15  KG  completed version 1.0
// ----------------------------------------------------------------------------
	void CTime::setHour(short hour)
	{
		if(hour > MINTIME && hour < MAXHOUR)
			m_hour = hour;
	}
//-----------------------------------------------------------------------------
//    Class:			CTime
//	  Method:			void CTime::setMinute(short minute)
//	  Description:		mutator for m_minute
//    Called By:		CTime(hour, minute, second)
//    Parameters:		short minute
//    Returns:          n/a
//    History Log:
//                      4/29/15  KG  completed version 1.0
// ----------------------------------------------------------------------------
	void CTime::setMinute(short minute)
	{
		if(minute > MINTIME && minute < MAXMINSEC)
			m_minute = minute;
	}
//-----------------------------------------------------------------------------
//    Class:			CTime
//	  Method:			void CTime::setSecond(short second)
//	  Description:		mutator for m_second  
//    Called By:		CTime(hour, minute, second)
//    Parameters:		short second
//    Returns:          n/a
//    History Log:
//                      4/29/15  KG  completed version 1.0
// ----------------------------------------------------------------------------
	void CTime::setSecond(short second)
	{
		if(second > MINTIME && second < MAXMINSEC)
			m_second = second;
	}
	
}