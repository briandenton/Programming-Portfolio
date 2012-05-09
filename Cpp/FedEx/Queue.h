/*///////////////////////////////////////////////////////////////////////////////////////

FILENAME:	 Queue.h

AUTHOR:      Brian Denton

DATE:		 09/23/2009

PROJECT:	 CSCI 362 Data Structures - Programming Assignment 3

DESCRIPTION: Header file for Queue class in FedEx simulation.


///////////////////////////////////////////////////////////////////////////////////////*/

#ifndef QUEUE_H
#define QUEUE_H

#include "utility.h"
#include "GlobalConstants.h"
#include "Item.h"
#include <queue>
#include <deque>

class Queue
{

public:

	//Constructor
	Queue();

	//Add element to back of queue
	void enqueue( Item ); 

	//Remove element from front of queue
	void dequeue();

	//Test whether queue is empty
	bool empty();

	//Return next element in queue
	Item front();

	//Print all elements from front to back
	void print() const;

	//Print all elements that exist in queue at a given time
	void printContentsAtTime( int ) const;

private:

	queue<Item> itemQueue;
	deque<Item> itemDeque;

};

#endif

//END OF PROGRAM