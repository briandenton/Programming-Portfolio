/*///////////////////////////////////////////////////////////////////////////////////////

FILENAME:	 List.h

AUTHOR:      Brian Denton

DATE:		 09/23/2009

PROJECT:	 CSCI 362 Data Structures - Programming Assignment 3

DESCRIPTION: Header file for List class in FedEx simulation.


///////////////////////////////////////////////////////////////////////////////////////*/

#ifndef LIST_H
#define LIST_H

#include "utility.h"
#include "GlobalConstants.h"
#include "Event.h"
#include <list>

class List
{

public:

	//Constructor
	List();

	//Function to add new event to list
	void add( Event const& );

	//Function to return first event from list
	Event front() const;

	//Function to remove first event from list
	void pop_front();

	//Test whether list is empty
	bool empty();

	//Print all elements in list
	void print() const;

private:

	list<Event> eventList;

};

#endif

//END OF PROGRAM