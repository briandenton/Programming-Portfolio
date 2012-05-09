/*///////////////////////////////////////////////////////////////////////////////////////

FILENAME:	 Stack.h

AUTHOR:      Brian Denton

DATE:		 09/23/2009

PROJECT:	 CSCI 362 Data Structures - Programming Assignment 3

DESCRIPTION: Header file for Stack class in FedEx simulation.


///////////////////////////////////////////////////////////////////////////////////////*/

#ifndef STACK_H
#define STACK_H

#include "utility.h"
#include "GlobalConstants.h"
#include "Item.h"
#include <stack>
#include <deque>

class Stack
{
public:

	//Constructor
	Stack();

	//Add element to top of Stack
	void push( Item ); 

	//Remove element from top of Stack
	void pop();

	//Test whether stack is empty
	bool empty();

	//Return next element on the stack
	Item top();

	//Print all elements from front to back
	void print() const;

	//Print all elements that exist in stack at a given time
	void printContentsAtTime( int ) const;

private:

	stack<Item> itemStack;
	deque<Item> itemDeque;

};

#endif

//END OF PROGRAM

