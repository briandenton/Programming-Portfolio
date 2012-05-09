/*///////////////////////////////////////////////////////////////////////////////////////

FILENAME:	 Simulator.cpp

AUTHOR:      Brian Denton

DATE:		 09/23/2009

PROJECT:	 CSCI 362 Data Structures - Programming Assignment 3

DESCRIPTION: Implementation file for Simulator class in FedEx simulation.


///////////////////////////////////////////////////////////////////////////////////////*/

#include "Simulator.h"

Simulator::Simulator( int snapshotTime, int serverLogRequest )
{
	
	//Seed random number generator
	//srand((unsigned)time(0));

	int numberOfPackagesProcessed = 0, timeInSystem = 0,
		minimumTimeInSystem = SIMULATION_DURATION, maximumTimeInSystem = 0,
		sumTimeInSystem = 0, serviceTime = 1;
	double meanTimeInSystem = 0;

	bool snapshotPrinted = false;
	ofstream serverLog;


	//Create package queue
	Queue packageQueue;

	//Create one stack for Chicago-bound packages and one for Memphis-bound
	Stack packageStackChicago;
	Stack packageStackMemphis;

	//Create queue for planes
	Queue planeQueue;

	//Create event list and populate with initial events
	List eventList = List();
	eventList.add( Event( "Package arrives", "Memphis", 5 ) );
	eventList.add( Event( 8 ) );//End of Service event
	eventList.add( Event( "Plane arrives", "Chicago", 80 ) );
	eventList.add( Event( "Plane arrives", "Memphis", 100 ) );

	//Add initial events to appropriate queues
	packageQueue.enqueue( Item( 5, "Memphis" ) );
	planeQueue.enqueue( Item( 80, "Chicago" ) );
	planeQueue.enqueue( Item( 100, "Memphis" ) );

	// Populate event list with remaining events
	for( int t = 1; t <= SIMULATION_DURATION; t++ )
	{

		//Arrival of package events
		//A new package arrives every 10 units of time starting at t = 5,
		//but an initial package at t = 5 is already in the event list so
		//start adding new packages after t = 5
		if( ( t - 5 ) % PACKAGE_INTERVAL == 0  && t > 5 )
		{
			if( (float)rand()/RAND_MAX < CHICAGO_PROB )
			{
				eventList.add( Event( "Package arrives", "Chicago", t ) );
				packageQueue.enqueue( Item( t, "Chicago" ) );
			}

			else
			{
				eventList.add( Event( "Package arrives", "Memphis", t ) );
				packageQueue.enqueue( Item( t, "Memphis" ) );
			}
		}

		//Arrival of plane events
		if( ( t - 80 ) % PLANE_CHICAGO_INTERVAL == 0 && t > 80 )
		{
			eventList.add( Event( "Plane arrives", "Chicago", t ) );
			planeQueue.enqueue( Item( t, "Chicago" ) );
		}

		if( ( t - 100 ) % PLANE_MEMPHIS_INTERVAL == 0 && t > 100 )
		{
			eventList.add( Event( "Plane arrives", "Memphis", t ) );
			planeQueue.enqueue( Item( t, "Memphis" ) );
		}

	}

	

	if( serverLogRequest == 1 )
	{
		serverLog.open ( "FedEx Simulation Server Log.txt" );
	}

	// BEGIN TRAVERSING EVENT LIST
	while( !eventList.empty() && serviceTime <= SIMULATION_DURATION )
	{
		//Set the current serviceTime to the time of the next event event
		serviceTime = eventList.front().getTimestamp();
		
		//Print snapshot if requested
		if( serviceTime >= snapshotTime && snapshotTime > 0 
			&& snapshotPrinted == false )
		{

			printSnapshot( serviceTime, packageQueue, planeQueue, 
							 packageStackChicago, packageStackMemphis, eventList );
			
			snapshotPrinted = true;
		}

		//Traverse list removing events until End of Sercice event is found
		if( eventList.front().getEventType().compare( "End of Service" ) != 0 )
		{
			eventList.pop_front();
		}

		//When an End of Service event is found:
		// 1) process a plane if one is in the plane queue at that time,
		// 2)  else process a package if one is in the package queue at that time
		// 3)  else maintain the forklift
		else
		{

			if( serverLogRequest == 1 )
			{
				serverLog << endl << "serviceTime = " << serviceTime << endl; 
			}

			//***********************************//
			//            CONDITION 1			 //
			// **********************************//

			//Check if there are any planes in the queue, and if so,
			//did the next one in the queue arrive before the End of Service event?
			if( !planeQueue.empty() && planeQueue.front().getArrivalTime() <= serviceTime )
			{
				//If it did arrive before the End of Service event, determine its
				//destination and load packages from it's stack
				if( planeQueue.front().getDestination().compare( "Chicago" ) == 0 )
				{
					if( serverLogRequest == 1 )
					{
						serverLog << "Loading plane to Chicago (arrived t = " 
								  << planeQueue.front().getArrivalTime() << ")" << endl;
					}
			
					int numberOfPackagesLoaded = 0;
					while( !packageStackChicago.empty() && 
						   numberOfPackagesLoaded < PLANE_MAX_CAPACITY )
					{
						timeInSystem = serviceTime + PLANE_LOAD_TIME
							           - packageStackChicago.top().getArrivalTime();

						if( serverLogRequest == 1 )
						{
							serverLog << "Arrival time: " 
							 << packageStackChicago.top().getArrivalTime() << ", "
							 << "Service time: " << serviceTime << ", " 
							 << "Time in system : " << timeInSystem << endl;
						}

						numberOfPackagesProcessed++;//Count how many total packages
						minimumTimeInSystem = min( minimumTimeInSystem, timeInSystem );
						maximumTimeInSystem = max( maximumTimeInSystem, timeInSystem );
						sumTimeInSystem = sumTimeInSystem + timeInSystem;
						
						packageStackChicago.pop();
						numberOfPackagesLoaded++;//Count how many packages on this plane
					}

				}//END load Chicago plane

				else if( planeQueue.front().getDestination().compare( "Memphis" ) == 0 )
				{
					if( serverLogRequest == 1 )
					{
						serverLog << "Loading plane to Memphis (arrived t = " 
					     << planeQueue.front().getArrivalTime() << ")" << endl;
					}

					int numberOfPackagesLoaded = 0;
					while( !packageStackMemphis.empty() && 
						   numberOfPackagesLoaded < PLANE_MAX_CAPACITY )
					{
						timeInSystem = serviceTime + PLANE_LOAD_TIME 
							           - packageStackMemphis.top().getArrivalTime();

						if( serverLogRequest == 1 )
						{
							serverLog << "Arrival time: " 
							 << packageStackMemphis.top().getArrivalTime() << ", "
							 << "Service time: " << serviceTime << ", " 
							 << "Time in system : " << timeInSystem << endl;
						}

						numberOfPackagesProcessed++;//Count how many total packages
						minimumTimeInSystem = min( minimumTimeInSystem, timeInSystem );
						maximumTimeInSystem = max( maximumTimeInSystem, timeInSystem );
						sumTimeInSystem = sumTimeInSystem + timeInSystem;

						packageStackMemphis.pop();
						numberOfPackagesLoaded++;//Count how many packages on this plane
					}

				}//END load Memphis plane

				//Remove the loaded plane from the plane queue
				planeQueue.dequeue();

				//Add an End of Service event for time when plane loading is complete
				eventList.add( Event( serviceTime + PLANE_LOAD_TIME ) );

			}//END plane queue non-empty

			//END CONDITON 1


			//***********************************//
			//            CONDITION 2			 //
			// **********************************//

			//If no planes in queue, check if there are packages in the queue,
			//and if so, did the next package in the queue arrive before the
			//End of Service event?
			else if( !packageQueue.empty() && 
				      packageQueue.front().getArrivalTime() <= serviceTime )
			{				
				
				//If it did arrive before the End of Service event, determine its
				//destination and add to appropriate to stack
				if( packageQueue.front().getDestination().compare( "Chicago" ) == 0 )
				{
					if( serverLogRequest == 1 )
					{
						serverLog << "Processing package for Chicago (arrived t = " 
						 << packageQueue.front().getArrivalTime() << ")" << endl;
					}

					packageStackChicago.push( packageQueue.front() );

				}//END process Chicago package

				else if( packageQueue.front().getDestination().compare( "Memphis" ) == 0 )
				{
					if( serverLogRequest == 1 )
					{
						serverLog << "Processing package for Memphis (arrived t = " 
						 << packageQueue.front().getArrivalTime() << ")" << endl;
					}
					
					packageStackMemphis.push( packageQueue.front() );
				}//END process Memphis package

				//Remove the transferred package from the queue
				packageQueue.dequeue();

				//Add an End of Service event for time when package processing is complete
				eventList.add( Event( serviceTime + PACKAGE_PROCESS_TIME ) );

			}//END package queue non-empty
			
			//END CONDITION 2



			//***********************************//
			//            CONDITION 3			 //
			// **********************************//
			
			//If no planes in queue, and no packages in queue then maintain forklift
			else
			{
				if( serverLogRequest == 1 )
				{
					serverLog << "Maintain forklift at t = " << serviceTime << endl;
				}

				//Add an End of Service event for time when forlift maintenance is complete
				eventList.add( Event( serviceTime + FORKLIFT_MAINT_TIME ) );
			}
			//END CONDITION 3

			// Remove current End of Service event from Event list	
			eventList.pop_front();

		}//END event is End of Service event


		if( !eventList.empty() )
		{
			serviceTime = eventList.front().getTimestamp();
		}

	}//END simulation while() loop

	if( serverLogRequest == 1 )
	{
		serverLog.close();
	}

	//If a snapshot was requested but has not yet been printed
	//(e.g. if the request is for a time after the last event
	//in the event list) then print snapshot now
	if( snapshotTime > 0 && snapshotPrinted == false )
	{
			printSnapshot( serviceTime, packageQueue, planeQueue, 
							 packageStackChicago, packageStackMemphis, eventList );
			
			snapshotPrinted = true;
	}

	if( numberOfPackagesProcessed > 0 )
	{
		meanTimeInSystem = (double)sumTimeInSystem/numberOfPackagesProcessed;
	}

	else
	{
		minimumTimeInSystem = -1;
		maximumTimeInSystem = -1;
		meanTimeInSystem = -1;
	}

	cout <<endl << endl
		 << "*********************************" << endl
		 << "*                               *" << endl
		 << "*      Simulation Results       *" << endl
		 << "*                               *" << endl
		 << "*********************************" << endl
		 
		 << endl << "Number of packages processed: " << numberOfPackagesProcessed << endl;

	if( numberOfPackagesProcessed > 0 )
	{
		cout << "Minimum time a package spent in the system: " << minimumTimeInSystem << endl
			 << "Maximum time a package spent in the system: " << maximumTimeInSystem << endl
			 << "Average time a package spent in the system: " << meanTimeInSystem << endl;
	}

	else
	{
		cout << "Minimum time a package spent in the system: N/A" << endl
			 << "Maximum time a package spent in the system: N/A" << endl
			 << "Average time a package spent in the system: N/A" << endl;
	}


}

void Simulator::printSnapshot( int serviceTime, Queue &packageQueue, Queue &planeQueue,
							   Stack &packageStackChicago, Stack &packageStackMemphis,
							   List &eventList ) const
{		
	cout << endl << endl
		 << "*********************************" << endl
		 << "*                               *" << endl
		 << "*  Snapshot of Data Structures  *" << endl
		 << "*                               *" << endl
		 << "*********************************" << endl;
	
	cout << endl << "Contents of Package Queue at t = " << serviceTime << endl;
	packageQueue.printContentsAtTime( serviceTime );

	cout << endl << endl << "Contents of Plane Queue at t = " << serviceTime << endl;
	planeQueue.printContentsAtTime( serviceTime );

	cout << endl << endl << "Contents of Package Stack for Chicago at t = " << serviceTime << endl;
	packageStackChicago.printContentsAtTime( serviceTime );

	cout << endl << endl << "Contents of Package Stack for Memphis at t = " << serviceTime << endl;
	packageStackMemphis.printContentsAtTime( serviceTime );

	cout << endl << endl << "Contents of Event List at t = " << serviceTime << endl;
	eventList.print();

}

//END OF PROGRAM