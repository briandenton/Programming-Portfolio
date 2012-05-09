/*///////////////////////////////////////////////////////////////////////////////////////

FILENAME:	 Item.cpp

AUTHOR:      Brian Denton

DATE:		 09/23/2009

PROJECT:	 CSCI 362 Data Structures - Programming Assignment 3

DESCRIPTION: Implementation file for Item class in FedEx simulation.


///////////////////////////////////////////////////////////////////////////////////////*/

#include "Item.h"

Item::Item( int time, string city )
{
	arrivalTime = time;
	destination = city;
}

int Item::getArrivalTime() const
{
	return arrivalTime;
}

string Item::getDestination() const
{
	return destination;
}


//Overload operator << as friend function of Item class
ostream& operator << ( ostream& out, const Item& x )
{
    out << "Destination: "  << setw(15) << left  << x.getDestination() 
		<< "Arrival Time: " << setw(4)  << right << x.getArrivalTime();
    return out;
}


//END OF PROGRAM