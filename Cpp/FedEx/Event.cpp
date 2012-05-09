/*///////////////////////////////////////////////////////////////////////////////////////

FILENAME:	 Event.cpp

AUTHOR:      Brian Denton

DATE:		 09/23/2009

PROJECT:	 CSCI 362 Data Structures - Programming Assignment 3

DESCRIPTION: Implementation file for Event class in FedEx simulation.


///////////////////////////////////////////////////////////////////////////////////////*/

#include "Event.h"

Event::Event(  string event_type, string destination_code, int time )
{
	eventType = event_type;
	destination = destination_code;
	timestamp = time;
}

Event::Event( int time )
{
	eventType = "End of Service";
	destination = "";
	timestamp = time;
}

int Event::getTimestamp() const
{
	return timestamp;
}

string Event::getDestination() const
{
	return destination;
}

string Event::getEventType() const
{
	return eventType;
}

ostream& operator << ( ostream& out, const Event& x )
{
    out << "Event Type: "  << setw(20) << left  << x.getEventType() 
		<< "Destination: " << setw(15) << left  << x.getDestination() 
		<< "Timestamp: " << setw(4)  << right << x.getTimestamp();
    return out;
}

bool Event::operator < ( const Event& x ) const
{
	if( getTimestamp() < x.getTimestamp() )
	{
		return true;
	}

	else
	{
		return false;
	}
}

//END OF PROGRAM