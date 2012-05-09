/*///////////////////////////////////////////////////////////////////////////////////////

FILENAME:	 Queue.cpp

AUTHOR:      Brian Denton

DATE:		 09/23/2009

PROJECT:	 CSCI 362 Data Structures - Programming Assignment 3

DESCRIPTION: Implementation file for Queue class in FedEx simulation.


///////////////////////////////////////////////////////////////////////////////////////*/

#include "Queue.h"

//The constructor for the Queue class creates a queue
//and an iterable deque from the Standard Template Library.
//This redundancy is neccessary because the class contains
//a print() function that must iterate over the Items
//in the queue, and a queue is not an iterable data structure
//but a deque is. The enqueue() and dequeue() functions must
//also operate on both structures to keep them equivalent.

Queue::Queue(){

	queue<Item> itemQueue;
	deque<Item> itemDeque;
}

void Queue::enqueue( Item x )
{
	itemQueue.push( x );
	itemDeque.push_back( x );
}

void Queue::dequeue()
{
	itemQueue.pop();
	itemDeque.pop_front();
}

bool Queue::empty()
{
	return itemQueue.empty();
}

Item Queue::front()
{
	return itemQueue.front();
}

void Queue::print() const
{
    deque<Item>::const_iterator i;                 

    for ( i = itemDeque.begin(); i != itemDeque.end(); ++i )
	{
         cout << *i << endl;
    }  
}

void Queue::printContentsAtTime( int queryTime ) const
{
    deque<Item>::const_iterator i;                 

    for ( i = itemDeque.begin(); i != itemDeque.end(); ++i )
	{
		if( (*i).getArrivalTime() <= queryTime )
		{
			cout << *i << endl;
		}
    }  
}

//END OF PROGRAM