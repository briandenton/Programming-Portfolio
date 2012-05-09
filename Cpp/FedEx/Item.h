/*///////////////////////////////////////////////////////////////////////////////////////

FILENAME:	 Item.h

AUTHOR:      Brian Denton

DATE:		 09/23/2009

PROJECT:	 CSCI 362 Data Structures - Programming Assignment 3

DESCRIPTION: Header file for Item class in FedEx simulation.


///////////////////////////////////////////////////////////////////////////////////////*/

#ifndef ITEM_H
#define ITEM_H

#include "utility.h"
#include "GlobalConstants.h"
#include <iomanip>

class Item
{

public:

	// Constructor
	Item( int, string );

	//Accessor Functions
	int getArrivalTime() const;
	string getDestination() const;

	// Overload operator << as friend function
	friend ostream& operator << ( ostream&, const Item& );

private:

	int arrivalTime;
	string destination;

};// End class Item definition

#endif

//END OF PROGRAM