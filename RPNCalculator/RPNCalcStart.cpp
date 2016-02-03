//-----------------------------------------------------------------------------
//    File:			RPNCalcStart.cpp
//
//    Class:		CRPNCalc
//
//	  Functions:	CRPNCalc(bool on)
//					run()
//					print(ostream& ostr)
//					parse()
//					void add() 
//					void bin_prep(double& d1, double& d2)  
//					void clear()  
//					void clearAll()  
//					void divide()  
//					void exp()  
//					void getReg(int reg)  
//					void loadProgram()  
//					void mod()  
//					void multiply()  
//					void neg()  
//					void parse()  
//					void recordProgram()  
//					void rotateUp()  
//					void rotateDown()  
//					void runProgram()  
//					void saveToFile()  
//					void setReg(int reg)  
//					void subtract()  
//					void unary_prep(double& d) 
//					ostream &operator<<(ostream &ostr, const CRPNCalc &calc)
//    				istream &operator>>(istream &istr, CRPNCalc &calc)
//-----------------------------------------------------------------------------
#include "RPNCalc.h"

namespace CPM_CALC
{
//-----------------------------------------------------------------------------
//    Class:		CRPNCalc
//
//    File:			RPNCalc.cpp
//
//    Description:	Definitions for CRPNCalc methods and related functions.
//
//    Programmers:	Kyle Graham, Sufiah Ahmad, Joe Waldher, Shawn Baines, and 
//						John Pickard-Gilyeat.
//   
//    Date:			6/12/2015
// 
//    Version:		1.0
//  
//    Environment:	Intel Xeon PC 
//                  Software:   MS Windows 7 for execution; 
//                  Compiles under Microsoft Visual C++.Net 2010
// 
//	  class CRPNCalc:
//
//		Properties:
//				double m_registers[10] -- Registers to store numbers.
//				stack<string> m_stack -- The stack to which numbers are added.
//				vector<list<string>> m_programs(NUMPROGRAMS) -- The place to
//										store instructions for a user defined
//										program.
//				istringstream m_inStrStream -- A stream for the input.
//
//	  History Log:       
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			CRPNCalc::CRPNCalc(bool on)
//	  Description:		constructor for the CRPNCalc class
//    Parameters:		bool on -- turns the calculator on
//    Called by:		main()
//	  Calls:			clear()
//						empty()
//						run()
//	  Throws:			n/a
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//						6/07/15	  completed version 1.0
//-----------------------------------------------------------------------------
	CRPNCalc::CRPNCalc(bool on): m_on(on), m_error(false), m_helpOn(true),
		m_programRunning(false)
	{
		for(int i = 0; i < NUMREGS; i++)
			m_registers[i] = 0.0;
		if(!(m_stack.empty()))
			m_stack.clear();
		if(!(m_program.empty()))
			m_program.clear();
		if(m_on)
			run();
	}

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::run()
//	  Description:		starts the calculator running
//    Parameters:		void
//    Called by:		CRPNCalc()
//	  Calls:			input()
//						print()
//						system()
//	  Throws:			n/a
//	  Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//                      6/07/15  JW  completed version 1.0
//-----------------------------------------------------------------------------
	void CRPNCalc::run()
	{
		do
		{
			system("cls");
			print(cout);
			input(cin);
		}while(m_on);
	}

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::print(ostream& ostr)
//	  Description:		prints out the help menu is m_helpOn is true, otherwise
//						prints out a few carriage returns. Follows this a long 
//						line and the first element that is in the stack
//    Parameters:		ostream& ostr -- the ostream to print to
//    Called by:		operator<<
//						run()
//	  Calls:			empty()
//						front()
//						operator<<()
//	  Throws:			n/a
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			prints out the helpMenu[] if it is on otherwise a few
//						carriage returns. Then prints out a line and the first
//						number in the stack.
//    History Log:
//						6/07/15	JP  completed version 1.0
//-----------------------------------------------------------------------------
	void CRPNCalc::print(ostream& ostr)
	{
		double d = 0.0;
		ostr << "[RPN Programmable Calculator] by C+-" << endl;
		if(m_helpOn)
			cout << helpMenu;
		else
			cout << endl << endl << endl;
		cout << line;
		if(!m_stack.empty())
		{
			d = m_stack.front();
			ostr << d;
		}
		ostr << endl << endl;
		if(m_error)
		{
			ostr << "<<error>>" << endl;
			m_error = false;
		}
	} 

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::parse()
//	  Description:		parses the next command from m_instrStream
//    Parameters:		void
//    Called by:		input()
//						runProgram()
//	  Calls:			add()
//						atof()
//						basic_string()
//						begin()
//						c_str()
//						clearAll()
//						clearEntry()
//						divide()
//						end()
//						exp()
//						getReg()
//						isdigit()
//						length()
//						loadProgram()
//						log10()
//						mod()
//						multiply()
//						neg()
//						operator*()
//						operator++()
//						operator--()
//						operator+=()
//						operator==()
//						operator!=()
//						operator>>()
//						push_front()
//						rotateDown()
//						rotateUp()
//						runProgram()
//						saveToFile()
//						setReg()
//						subtract()
//						transform()
//	  Throws:			m_error
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//                           6/7/15  JW  completed version 1.0
//-----------------------------------------------------------------------------
	void CRPNCalc::parse()
	{
		string token;
		while(m_instrStream >> token)
		{
			string::iterator sit(token.begin());
			transform(token.begin(), token.end(), token.begin(), toupper);
			if(isdigit(*token.c_str()))
				m_stack.push_front(atof(token.c_str()));
			else if(*sit == '+' || *sit == '-' || *sit == '*' || *sit == '/' || *sit == '%' || *sit == '^')
			{
				while(sit != token.end())
				{
					if(*sit == '+')
					{
						this->add();
						sit++;
					}
					else if( *sit == '-')
					{
						sit++;
						if(sit != token.end())
						{
							if(isdigit(*sit))
							{
							sit--;
							m_stack.push_front(atof(token.c_str()));
							sit += token.length();
							}
							else
							{
								sit--;
								m_error = true;
								sit += token.length();
							}
						}
						else
							this->subtract();
					}
					else if(*sit == '*')
					{
						this->multiply();
						sit++;
					}
					else if(*sit == '/')
					{
						this->divide();
						sit++;
					}
					else if(*sit == '%')
					{
						this->mod();
						sit++;
					}
					else if(*sit == '^')
					{
						this->exp();
						sit++;
					}
					else
						sit++;
				}
			}
			else if(token == "CE")
				this->clearEntry();
			else if(token == "C")
				this->clearAll();
			else if(token == "D")
				this->rotateDown();
			else if(token == "F")
				this->saveToFile();
			else if(token == "G0")
				this->getReg(0);
			else if(token == "G1")
				this->getReg(1);
			else if(token == "G2")
				this->getReg(2);
			else if(token == "G3")
				this->getReg(3);
			else if(token == "G4")
				this->getReg(4);
			else if(token == "G5")
				this->getReg(5);
			else if(token == "G6")
				this->getReg(6);
			else if(token == "G7")
				this->getReg(7);
			else if(token == "G8")
				this->getReg(8);
			else if(token == "G9")
				this->getReg(9);
			else if(token == "H")
				m_helpOn = m_helpOn ? false : true;
			else if(token == "L")
				this->loadProgram();
			else if(token == "M")
				this->neg();
			else if(token == "P")
				m_programRunning = m_programRunning ? false : true;
			else if(token == "R")
				this->runProgram();
			else if(token == "S0")
				this->setReg(0);
			else if(token == "S1")
				this->setReg(1);
			else if(token == "S2")
				this->setReg(2);
			else if(token == "S3")
				this->setReg(3);
			else if(token == "S4")
				this->setReg(4);
			else if(token == "S5")
				this->setReg(5);
			else if(token == "S6")
				this->setReg(6);
			else if(token == "S7")
				this->setReg(7);
			else if(token == "S8")
				this->setReg(8);
			else if(token == "S9")
				this->setReg(9);
			else if(token == "U")
				this->rotateUp();
			else if(token == "X")
			{
				m_on = false;
				return;
			}
			else
				m_error = true;
		}
	}

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::add()
//	  Description:		if possible, pops top 2 elements from the stack, adds 
//							 them and pushes the result onto the stack
//    Parameters:		void
//    Called by:		parse()
//	  Calls:			binary_prep()
//						push_front()
//	  Throws:			n/a
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//                      6/10/15	SA  completed version 1.0
//-----------------------------------------------------------------------------
	void CRPNCalc::add()
	{
		double data1 = 0;
		double data2 = 0;

		binary_prep(data1, data2);
		if(!m_error)
		{
			data1 += data2;
			m_stack.push_front(data1);
		}
	} 

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::binary_prep(double& d1, double& d2)
//	  Description:		sets the args to the popped values from the stack, if 
//							possible set error state otherwise
//    Parameters:		double& d1, double& d2
//    Called by:		add()
//						divide()
//						exp()
//						mod()
//						multiply()
//						subtract()
//	  Calls:			front()
//						empty()
//						push_front()
//	  Throws:			m_error
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//						6/10/15	SA completed version 1.0
//-----------------------------------------------------------------------------
	void CRPNCalc::binary_prep(double& d1, double& d2)
	{
		if(!m_stack.empty())
		{
			d1 = m_stack.front();
			m_stack.pop_front();
			if(!m_stack.empty())
			{
				d2 = m_stack.front();
				m_stack.pop_front();
			}
			else
			{
				m_error = true;
				m_stack.push_front(d1);
			}
		}
		else
			m_error = true;
	} 

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::clearEntry()
//	  Description:		removes the top element from the stack
//    Parameters:		void
//    Called by:		parse()
//	  Calls:			empty()
//						pop_front()
//	  Throws:			n/a
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//						6/10/15 SA completed version 1.0
//-----------------------------------------------------------------------------
	void CRPNCalc::clearEntry()
	{
		if(!m_stack.empty())
			m_stack.pop_front();
	}

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::clearAll()
//	  Description:		empties the stack
//    Parameters:		void
//    Called by:		parse()
//	  Calls:			pop_front()
//						empty()
//	  Throws:			n/a
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//						6/10/15	 completed version 1.0
//-----------------------------------------------------------------------------
	void CRPNCalc::clearAll()
	{
		while(!m_stack.empty())	
			m_stack.pop_front();
	} 

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::clearEntry()
//	  Description:		if possible, pops top 2 elements from the stack, 
//							divides them and pushes the result onto the stack
//    Parameters:		void
//    Called by:		parse()
//	  Calls:			binary_prep()
//						push_front()
//	  Throws:			n/a
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//						6/10/15	SA completed version 1.0
//-----------------------------------------------------------------------------
   void CRPNCalc::divide()
   {
	   	double data1 = 0;
		double data2 = 0;
		binary_prep(data1, data2);

		if(!m_error)
		{
			data2 /= data1;
			m_stack.push_front(data2);
		}
   } 

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::exp()
//	  Description:		if possible, pops top 2 elements from the stack, raises
//							one element to the other power and pushes the
//							result onto the stack
//    Parameters:		void
//    Called by:		parse()
//	  Calls:			binary_prep()
//						pow()
//						push_front()
//	  Throws:			n/a
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//						6/10/15	SA completed version 1.0
//-----------------------------------------------------------------------------

   void CRPNCalc::exp()
   {
	   	double data1 = 0;
		double data2 = 0;
		binary_prep(data1, data2);

		if(!m_error)
		{
			data1 = pow(data2, data1);
			m_stack.push_front(data1);
		}
	}  

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::getReg(int reg)
//	  Description:		pushes the given register's value onto the stack
//    Parameters:		int reg
//    Called by:		parse()
//	  Calls:			push_front()
//	  Throws:			n/a
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//						6/7/15	JP  completed version 1.0
//-----------------------------------------------------------------------------
	void CRPNCalc::getReg(int reg)
	{
		double temp = m_registers[reg];
		m_stack.push_front(temp);
	}

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::exp()
//	  Description:		retrieves the filename from the user and loads it into
//							m_program
//    Parameters:		void
//    Called by:		parse()
//	  Calls:			basic_ifstream()
//						basic_string()
//						close()
//						getline()
//						is_open()
//						open()
//						operator!=()
//						operator<<()
//						pop_front()
//						push_back()
//						empty()
//	  Throws:			n/a
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//                      6/7/15	SB completed version 1.0
//-----------------------------------------------------------------------------
	void CRPNCalc::loadProgram()
	{
		ifstream load;
		string input = " ";
		string filename = "";

		cout << "Please enter the name of the program you wish to load." << endl;
		getline(cin, filename);
		load.open(filename);
		if(load.is_open())
		{
			while(!m_program.empty())
			{
				m_program.pop_front();
			}
			do
			{
				getline(load, input);
				m_program.push_back(input);
			}
			while(input != "\0");
		}
		else
		{
			m_error = true;
		}

		load.close();
	}

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::mod()
//	  Description:		if possible, pops top 2 elements from the stack, mods 
//							them and pushes the result onto the stack
//    Parameters:		void
//    Called by:		parse()
//	  Calls:			binary_prep()
//						fmod()
//						push_front()
//	  Throws:			n/a
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//						6/10/15	SA completed version 1.0
//-----------------------------------------------------------------------------
   void CRPNCalc::mod()
   {
		double data1 = 0;
		double data2 = 0;
		binary_prep(data1, data2);

		if(!m_error)
		{
			data1 = fmod(data2, data1);
			m_stack.push_front(data1);
		}
   } 

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::multiply()
//	  Description:		if possible, pops top 2 elements from the stack, 
//							multiplies them and pushes the result onto the 
//							stack
//    Parameters:		void
//    Called by:		parse()
//	  Calls:			binary_prep()
//						push_front()
//	  Throws:			n/a
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//						6/10/15	SA completed version 1.0
//-----------------------------------------------------------------------------
   void CRPNCalc::multiply()
   {
		double data1 = 0;
		double data2 = 0;
		binary_prep(data1, data2);

		if(!m_error)
		{
			data1 *= data2;
			m_stack.push_front(data1);
		}
   } 

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::neg()
//	  Description:		resets the top element of the stack to it's negative
//    Parameters:		void
//    Called by:		parse()
//	  Calls:			unary_prep()
//						push_front()
//	  Throws:			n/a
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//						6/7/15	JP  completed version 1.0
//-----------------------------------------------------------------------------
	void CRPNCalc::neg()
	{
		double temp;
		unary_prep(temp);
		temp *= -1;
		m_stack.push_front(temp);
	} 

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::unary_prep(double& d)
//	  Description:		sets the arg to the popped value from the stack, if 
//							possible sets error state otherwise
//    Parameters:		double& d
//    Called by:		neg()
//	  Calls:			empty()
//						front()
//						pop_front()
//	  Throws:			m_error
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//                           6/7/15  JP  completed version 1.0
//-----------------------------------------------------------------------------
	void CRPNCalc::unary_prep(double& d)
	{
		if(m_stack.empty())
			m_error = true;
		else
		{
			d = m_stack.front();
			m_stack.pop_front();
		}
	}

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::multiply()
//	  Description:		takes command-line input and loads it into m_program 
//    Parameters:		void
//    Called by:		
//	  Calls:			empty()
//						pop_back()	
//	  Throws:			n/a
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//						6/10/15	SB completed version 1.0
//-----------------------------------------------------------------------------
	void CRPNCalc::recordProgram()
	{
		if(m_programRunning == false)
		{
			while(!m_program.empty())
			{
				m_program.pop_back();
			}
			m_programRunning = true;
		}
		else if (m_programRunning == true)
		{
			m_programRunning = false;
		}
	} 

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::rotateDown()
//	  Description:		removes the bottom of the stack and adds it to the top
//    Parameters:		bool on
//    Called by:		parse()
//	  Calls:			empty()
//						front()
//						push_back()
//						pop_front()
//	  Throws:			n/a
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//                           6/7/15  JP  completed version 1.0
//-----------------------------------------------------------------------------
	void CRPNCalc::rotateDown()
	{
		if(!(m_stack.empty()))
		{
			double temp = m_stack.front();
			m_stack.push_back(temp);
			m_stack.pop_front();
		}
	} 

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::rotateUp()
//	  Description:		removes the top of the stack and adds it to the bottom
//    Parameters:		void
//    Called by:		parse()
//	  Calls:			empty()
//						back()
//						push_front()
//						pop_back()
//	  Throws:			n/a
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//                           6/7/15  JP  completed version 1.0
//-----------------------------------------------------------------------------
	void CRPNCalc::rotateUp()
	{
		if(!(m_stack.empty()))
		{
			double temp = m_stack.back();
			m_stack.push_front(temp);
			m_stack.pop_back();
		}
	} 

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::multiply()
//	  Description:		runs the program in m_program  
//    Parameters:		void
//    Called by:		parse()
//	  Calls:			list_iterator()
//						begin()
//						end()
//						operator!=()
//						operator*()
//						operator++()
//						operator>>()
//						parse()
//	  Throws:			n/a
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//                           6/7/15    completed version 1.0
//-----------------------------------------------------------------------------
	void CRPNCalc::runProgram()
	{
		if(!m_program.empty())
		{
			for(list<string>::iterator lit = m_program.begin() ; lit != m_program.end() ; ++(lit))
			{
				istringstream temp(*lit);
				m_instrStream.swap(temp);
				parse();
			}
		}
		else
		{
			m_error = true;
		}
	} 

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::saveToFile()
//	  Description:		asks the user for a filename and saves m_program to that file
//    Parameters:		void
//    Called by:		parse()
//	  Calls:			list_iterator()
//						basic_ofstream()
//						basic_string()
//						begin()
//						end()
//						open()
//						operator!=()
//						operator*()
//						operator++()
//						operator<<()
//						operator>>()
//	  Throws:			n/a
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//						6/7/15	SB  completed version 1.0
//-----------------------------------------------------------------------------
	void CRPNCalc::saveToFile()
	{
		ofstream record;
		string filename;
		cout << "Please enter in the name of the program you wish to create." << endl;
		cin >> filename;

		record.open(filename, ofstream::app);
		for(list<string>::iterator lit = m_program.begin() ; lit != m_program.end() ; ++(lit))
		{
			record << *lit << endl;
		}
	}  

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::setReg(int reg)
//	  Description:		gets the value from the top of the stack
//							and places it into the given register
//    Parameters:		int reg
//    Called by:		parse()
//	  Calls:			empty()
//						front()
//	  Throws:			n/a
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//                           6/7/15  JP  completed version 1.0
//-----------------------------------------------------------------------------
	void CRPNCalc::setReg(int reg)
	{
		if(!(m_stack.empty()))
		{
			double temp = m_stack.front();
			m_registers[reg] = temp;
		}
		else
		{
			m_error = true;
		}	
	} 

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::subtract()
//	  Description:		if possible, pops top 2 elements from the stack, 
//							subtracts them and pushes the result onto the stack
//    Parameters:		void
//    Called by:		parse()
//	  Calls:			binary_prep()
//						push_front()
//	  Throws:			n/a
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//						6/7/15	JP  completed version 1.0
//-----------------------------------------------------------------------------
   void CRPNCalc::subtract()
   {
	    double tempA, tempB;
		binary_prep(tempA, tempB);
		if(m_error == false)
		{
			double temp = tempB - tempA;
			m_stack.push_front(temp);
		}
   } 

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			void CRPNCalc::input(istream &istr)
//	  Description:		inputs a line from the given stream
//    Parameters:		istream &istr
//    Called by:		operator>>()
//						run()
//	  Calls:			basic_istringstream()
//						getline()
//						parse()
//						push_back()
//						str()
//						swap()
//	  Throws:			n/a
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//						6/7/15	JW  completed version 1.0
//-----------------------------------------------------------------------------
   void CRPNCalc::input(istream &istr)
   {
	   getline(istr, m_buffer);
	   istringstream temp(m_buffer);
	   m_instrStream.swap(temp);
	   if(m_programRunning)
		   m_program.push_back(m_instrStream.str());
	   this->parse();
   }

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			ostream &operator <<(ostream &ostr, CRPNCalc &calc)
//	  Description:		ostream's << defined for CRPNCalc
//    Parameters:		ostream &ostr, CRPNCalc &calc
//    Called by:		
//	  Calls:			print()
//	  Throws:			n/a
//    Returns:          n/a
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//						6/7/15	PB  completed version 1.0
//-----------------------------------------------------------------------------
	ostream &operator<<(ostream &ostr, CRPNCalc &calc)
	{
		calc.print(ostr);
		return ostr;
	} 

//-----------------------------------------------------------------------------
//    Class:			CRPNCalc
//	  Method:			istream &operator >>(istream &istr, CRPNCalc &calc)
//	  Description:		istream's >> defined for CRPNCalc
//    Parameters:		istream &istr, CRPNCalc &calc
//    Called by:		
//	  Calls:			input()
//	  Throws:			n/a
//    Returns:          istr -- the istream
//	  Input:			n/a
//	  Output:			n/a
//    History Log:
//						6/7/15	PB  completed version 1.0
//-----------------------------------------------------------------------------
	istream &operator>>(istream &istr, CRPNCalc &calc)
	{
		calc.input(istr);
		return istr;
	} 
} // end namespace PB_CALC