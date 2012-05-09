/*///////////////////////////////////////////////////////////////////////////////////////

FILENAME:	 FedEx.cpp

AUTHOR:      Brian Denton

DATE:		 09/23/2009

PROJECT:	 CSCI 362 Data Structures - Programming Assignment 3

DESCRIPTION: Implementation file for driver program in FedEx simulation.


///////////////////////////////////////////////////////////////////////////////////////*/

#include "FedEx.h"

int main()
{

	int snapshotRequest = -1, snapshotTime = -1,
		serverLogRequest = -1;

	cout << "This program runs a simulation of a FedEx air terminal." << endl;

	//Get info from user about snapshot
	while( snapshotRequest != 0 && snapshotRequest != 1 )
	{
		cout << endl << "Do you want a snapshot of the data structure contents "
			 << "during the simulation? (0 = no, 1 = yes): ";

		cin >> snapshotRequest;

		if( snapshotRequest == 1 )
		{
			cout << endl
				 << "NOTE: Snapshot will be provided at the " 
  		         << "time of the next event after requested time, or " << endl
				 << "      at the time of the last event if the requested "
				 << "time is after the last event." << endl;
			
			while( snapshotTime < 1 )
			{
				cout << endl << "Enter time for snapshot: ";
				cin >> snapshotTime;

				if( snapshotTime < 1 )
				{
					cout << endl << endl
						 << "The snapshot time must be greater than or equal to 1."
						 << endl << endl;
				}

			}

		}

	}

	//Get info from user about server log
	while( serverLogRequest != 0 && serverLogRequest != 1 )
	{
		cout << endl << endl 
			 << "Do you want a log of server activity (0 = no, 1 = yes): ";

		cin >> serverLogRequest;

		if( serverLogRequest == 1 )
		{
			cout << endl << "The server log will be printed to "
				 << "'FedEx Simulation Server Log.txt'.";
		}

	}

	Simulator FedEx( snapshotTime, serverLogRequest );

	cout << endl << endl;

	return 0;

}


//END OF PROGRAM