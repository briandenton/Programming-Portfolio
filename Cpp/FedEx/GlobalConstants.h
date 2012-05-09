/*///////////////////////////////////////////////////////////////////////////////////////

FILENAME:	 GlobalConstants.h

AUTHOR:      Brian Denton

DATE:		 09/23/2009

PROJECT:	 CSCI 362 Data Structures - Programming Assignment 3

DESCRIPTION: Header file defining global constants for FedEx simulation.


///////////////////////////////////////////////////////////////////////////////////////*/

#ifndef GLOBAL_CONSTANTS_H
#define GLOBAL_CONSTANTS_H

const int PACKAGE_INTERVAL = 10;
const int PACKAGE_PROCESS_TIME = 8;

const int FORKLIFT_MAINT_TIME = 6;

const int PLANE_CHICAGO_INTERVAL = 150;
const int PLANE_MEMPHIS_INTERVAL = 180;
const int PLANE_MAX_CAPACITY = 25;
const int PLANE_LOAD_TIME = 25;

const float CHICAGO_PROB = 0.5;

const int SIMULATION_DURATION = 10000;

#endif