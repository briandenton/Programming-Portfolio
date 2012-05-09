/*///////////////////////////////////////////////////////////////////////////////////////

FILENAME:	 List.cpp

AUTHOR:      Brian Denton

DATE:		 09/23/2009

PROJECT:	 CSCI 362 Data Structures - Programming Assignment 3

DESCRIPTION: Implementation file for List class in FedEx simulation.


///////////////////////////////////////////////////////////////////////////////////////*/

#include "List.h"

List::List()
{
	list<Event> eventList;
}

void List::add( Event const& e )
{
	eventList.push_front( e );
	eventList.sort();
}


Event List::front() const
{
	return eventList.front();
}

void List::pop_front()
{
	eventList.pop_front();
}

bool List::empty()
{
	return eventList.empty();
}

void List::print() const
{
    list<Event>::const_iterator i;                 

    for ( i = eventList.begin(); i != eventList.end(); ++i )
	{
         cout << *i << endl;
    }

}

//END OF PROGRAM