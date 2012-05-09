/*///////////////////////////////////////////////////////////////////////////////////////

FILENAME:	 Simulator.h

AUTHOR:      Brian Denton

DATE:		 09/23/2009

PROJECT:	 CSCI 362 Data Structures - Programming Assignment 3

DESCRIPTION: Header file for Simulator class in FedEx simulation.


///////////////////////////////////////////////////////////////////////////////////////*/

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "utility.h"
#include "GlobalConstants.h"
#include "Item.h"
#include "Queue.h"
#include "Stack.h"
#include "Event.h"
#include "List.h"

class Simulator
{

public:

	//Constructor
	Simulator( int, int );

	//Function to print data structure contents
	void printSnapshot( int, Queue &, Queue &, Stack &, Stack &, List & ) const;

	//Function to print service log

private:


};


#endif

//END OF PROGRAM