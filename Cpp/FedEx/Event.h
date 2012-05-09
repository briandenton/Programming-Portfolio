/*///////////////////////////////////////////////////////////////////////////////////////

FILENAME:	 Event.h

AUTHOR:      Brian Denton

DATE:		 09/23/2009

PROJECT:	 CSCI 362 Data Structures - Programming Assignment 3

DESCRIPTION: Header file for Event class in FedEx simulation.


///////////////////////////////////////////////////////////////////////////////////////*/

#ifndef EVENT_H
#define EVENT_H

#include <iomanip>
#include "utility.h"
#include "GlobalConstants.h"

class Event
{

public:

	//Constructors
	Event( string, string, int  );
	Event( int );//If an event is of type "End of Service" then destination is "N/A" and
				 //therefore event type and destination are known, and only timestamp needs
				 //to be provided

	//Accessor Functions
	int getTimestamp() const;
	string getDestination() const;
	string getEventType() const;

	//Overload operator << as friend function
	friend ostream& operator << ( ostream&, const Event& );

	//Overload operator < as member function
	bool operator < ( const Event& ) const;

private:

	int timestamp;
	string eventType, destination;

};

#endif

//END OF PROGRAM