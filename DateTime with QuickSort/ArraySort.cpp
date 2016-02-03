#include "ArraySort.h"
namespace KG_DATETIME
{
//-----------------------------------------------------------------------------
//	  Function:			safeRead(istream& sin, Comparable* d, const char* re)
//	  Description:		safely reads in a DateTime (d) from sin.
//						Re-prompts and re-enters if input is invalid
//    Input:			Comparable* d from sin
//    Output:			None
//    Calls:            input()
//    Called By:		main
//    Parameters:		istream& sin  -- the input stream
//						Comparable* d -- pointer to the object input
//						const char* prompt  -- prompt, if necessary
//    Returns:          n/a 
//
//    History Log:
//                           2/9/08  PB  completed version 1.0
// ----------------------------------------------------------------------------	
	void safeRead(istream& sin, Comparable* d, const char* prompt)
	{
		const int BUFFERSIZE = 256;
		d->input(sin);
		while(!sin)
		{		// read in number--enter loop if fail
			sin.clear();		// clear fail
			sin.ignore(BUFFERSIZE, '\n');	// read past newline
			cout << prompt << endl;  // re-prompt
			d->input(sin);
		}
		sin.ignore(BUFFERSIZE, '\n');  // read past newline once input succeeds
	}
//-----------------------------------------------------------------------------
//	  Function:			void printArray(ostream & sout, Comparable **a,
//							int size)
//	  Description:		can print out an array of DateTime *
//    Input:			None
//    Output:			Comparable* d sout
//    Calls:            print()
//    Called By:		main()
//    Parameters:		ostream& sout  -- the output stream
//						Comparable** a -- array of pointers to the objects
//						int size  -- number of elements in the array
//    Returns:          n/a 
//    History Log:
//                           2/9/08  PB  completed version 1.0
// ----------------------------------------------------------------------------	
	void printArray(ostream & sout, Comparable **a, int size)
	{
		for(int i = 0; i < size; i++)
		{
			a[i]->print(sout);
			sout << endl;
		}
		sout << endl;
	}
//-----------------------------------------------------------------------------
//	  Function:			void quickSort(Comparable** array, int fromIndex, 
//							int toIndex)
//	  Description:		sorts an array of DateTime * in ascending order
//						works as the moderator function 
//    Calls:            insertionSort(array, fromIndex, toIndex)
//						partition(array, fromIndex, toIndex)
//						quickSort(array, fromIndex, mid)
//						quickSort(array, mid, toIndex)
//    Called By:		main(), quickSort()
//    Parameters:		int fromIndex -- the start of the array
//						Comparable** a -- array of pointers to the objects
//						int toIndex -- end of the array
//    Returns:          void
//    History Log:
//                           4/30/15  KG  completed version 1.0
// ----------------------------------------------------------------------------	
	void quickSort(Comparable** array, int fromIndex, int toIndex)
	{
		if(toIndex - fromIndex < FOUR)
			 insertionSort(array, fromIndex, toIndex);
		else
		{
			int mid = partition(array, fromIndex, toIndex);
			quickSort(array, fromIndex, mid);
			quickSort(array, mid, toIndex);
		}
	}
//-----------------------------------------------------------------------------
//	  Function:			int partition(Comparable** array, int fromIndex, 
//							int toIndex)
//	  Description:		sorts an array of DateTime * in ascending order
//						works as the work horse function
//    Calls:            SortFirstMiddleLast(array, fromIndex, pivot, toIndex)
//						swap();				
//    Called By:		quickSort()
//    Parameters:		int fromIndex -- the start of the array
//						Comparable** a -- array of pointers to the objects
//						int toIndex -- end of the array
//    Returns:          front - the middle of the array
//    History Log:
//                           4/30/15  KG  completed version 1.0
// ----------------------------------------------------------------------------	
	int partition(Comparable** array, int fromIndex, int toIndex)
	{
		int pivot = ((fromIndex + toIndex) / 2);
		SortFirstMiddleLast(array, fromIndex, pivot, toIndex);
		swap(array[pivot], array[toIndex - 1]);
		int front = fromIndex + 1;
		int back = toIndex - 2;
		pivot = toIndex - 1;
		while (front <= back) 
		{
			while(*array[front] < *array[pivot])
			{
				front++;
			}
			while(*array[pivot] < *array[back])
			{
				back--;
			}
			swap(array[front], array[back]);		
			front++;
			back--;
		}
		swap(array[front], array[pivot]);
		return front;                    
	}
//-----------------------------------------------------------------------------
//	  Function:			void SortFirstMiddleLast(Comparable** array, int 
//								fromIndex,int midIndex, int toIndex)						
//	  Description:		sorts the first, middle, and last objects in the array
//    Calls:            swap();				
//    Called By:		partition()						
//    Parameters:		int fromIndex -- the start of the array
//						Comparable** a -- array of pointers to the objects
//						int midIndex -- the middle of the array
//						int toIndex -- end of the array
//    Returns:          front - the middle of the array
//    History Log:
//                           4/30/15  KG  completed version 1.0
// ----------------------------------------------------------------------------	
	void SortFirstMiddleLast(Comparable** array, int fromIndex,
		int midIndex, int toIndex)
	{
		if(*array[midIndex] < *array[fromIndex])
			swap(array[midIndex], array[fromIndex]);
		if(*array[toIndex] < *array[midIndex])
			swap(array[toIndex], array[midIndex]);
		if(*array[midIndex] < *array[fromIndex])
			swap(array[midIndex], array[fromIndex]);
	}
//-----------------------------------------------------------------------------
//	  Function:			void swap(Comparable*& a, Comparable*& b)						
//	  Description:		swaps two DateTime * objects  
//    Input:			None
//    Output:			None
//    Calls:            swap();				
//    Called By:		partition()
//						sortFirstMiddleLast()					
//    Parameters:		Comparable*& a -- first pointer reference
//						Comparable*& b -- second pointer reference						
//    Returns:          None
//    History Log:
//                           4/30/15  KG  completed version 1.0
// ----------------------------------------------------------------------------	
	 void swap(Comparable*& a, Comparable*& b)
     {
		Comparable* temp = a;
        a = b;
        b = temp;
	 }
//-----------------------------------------------------------------------------
//	  Function:			void insertionSort(Comparable** array, int fromIndex,
//							 int toIndex)							
//	  Description:		sorts in ascending order arrays smaller than 4
//    Called By:		quickSort()						
//    Parameters:		int fromIndex -- the start of the array
//						Comparable** array -- array of pointers to the objects
//						int toIndex -- end of the array					
//    Returns:          None
//    History Log:
//                           4/30/15  KG  completed version 1.0
// ----------------------------------------------------------------------------	
	 void insertionSort(Comparable** array, int fromIndex, int toIndex)
	{
		Comparable* temp = array[0];
		Comparable* value = array[0];
		for(int i = fromIndex + 1; i <= toIndex; i++)  // ar[i] is element to insert
		{
			temp = array[i];
			int j = i;
			for(j = i; j > 0; j--)
			{
				value = array[j - 1];
				if(*temp < *value)
				   array[j] = array[j - 1];
				else break;
			}
			array[j] =  temp;
		} 
	}

};


