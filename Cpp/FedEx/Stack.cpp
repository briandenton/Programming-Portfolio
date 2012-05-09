/*///////////////////////////////////////////////////////////////////////////////////////

FILENAME:	 Stack.cpp

AUTHOR:      Brian Denton

DATE:		 09/23/2009

PROJECT:	 CSCI 362 Data Structures - Programming Assignment 3

DESCRIPTION: Implementation file for Stack class in FedEx simulation.


///////////////////////////////////////////////////////////////////////////////////////*/

#include "Stack.h"

//The constructor for the Stack class creates a stack
//and an iterable deque from the Standard Template Library.
//This redundancy is neccessary because the class contains
//a print() function that must iterate over the Items
//in the stack, and a stack is not an iterable data structure
//but a deque is. The push() and pop() functions must
//also operate on both structures to keep them equivalent.

Stack::Stack(){

	stack<Item> itemStack;
	deque<Item> itemDeque;
}


void Stack::push( Item x )
{
	itemStack.push( x );
	itemDeque.push_back( x );
}

void Stack::pop()
{
	itemStack.pop();
	itemDeque.pop_back();//remove from back of deque rather than front
}

bool Stack::empty()
{
	return itemStack.empty();
}

Item Stack::top()
{
	return itemStack.top();
}


void Stack::print() const
{
    deque<Item>::const_reverse_iterator i;                 

    for ( i = itemDeque.rbegin(); i != itemDeque.rend(); ++i )
	{
         cout << *i << endl;
    }
}

void Stack::printContentsAtTime( int queryTime ) const
{
    deque<Item>::const_reverse_iterator i;                 

    for ( i = itemDeque.rbegin(); i != itemDeque.rend(); ++i )
	{
        if( (*i).getArrivalTime() <= queryTime )
		{
			cout << *i << endl;
		}
    }
}

//END OF PROGRAM