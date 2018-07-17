/**************************************************************************************************************************************************************
	Title:		Process.cpp

	Author:		Edwin Quintuna

	Created On:	5/4/2018

	Description:	Source file.	

	Purpose:	Used to create instances of Process objects that will be moved around the OS simulation. As contents
			of the local variables are manipulated, these changes will determine where each instance of Process will be located
			in the OS simulation.	 

	Usage:		Process.cpp
			function definitions

	Build:		"make" Make file is provided.

	Modifications:  May 4, 2018
			Implemented code documentation		    
 	 

**************************************************************************************************************************************************************/
#include "process.h"

/**
*	@brief Default constructor for Process that sets default values to local variables of Process class.
*
*	@param
*	@return nothing
*/
Process::Process()
{
	setData(-1,0,0);
}

/**
*	@brief Copy constructor for Process
*
*	@para[counter] , represents the process ID of the process being created.
*	@return nothing
*/
Process::Process(int counter)
{
	setData(counter,0, 0);
}

/**
*	@brief function that sets values for processID, queue and burstTime all at the same time.
*
*	@param[counter] , represents the process ID of the process being created.
*	@param[Q]       , represents the queue that the process is in.
*	@param[B]       , represents the current burst time the process is on.
*	@return nothing
*/
void Process::setData(int counter, int Q, int B)
{
	
	processID = counter;	
	queue = Q;
	burstTime = B;

}

/**
*	@brief function that displays local varaibles of Process class to console. 
*
*	@param nothing
*	@return nothing
*/
void Process::display()
{
	cout << "- Process ID: "   << processID << endl;
	cout << endl;
	cout << "	- Queue: " << "Q" << queue  << endl;
	cout << endl;
	cout << "	- Burst Time: " <<  burstTime  << endl;
	cout << endl;

}



