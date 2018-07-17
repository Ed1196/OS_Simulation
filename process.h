/**************************************************************************************************************************************************************
	Title:		Process.h

	Author:		Edwin Quintuna

	Created On:	5/4/2018

	Description:	Header file.	

	Purpose:	Used to create instances of Process objects that will be moved around the OS simulation. As contents
			of the local variables are manipulated, these changes will determine where each instance of Process will be located
			in the OS simulation.	 

	Usage:		Process.h
			function prototypes

	Build:		"make" Make file is provided.

	Modifications:  May 4, 2018
			Implemented code documentation		    
 	 

**************************************************************************************************************************************************************/

#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED
#include <iostream>

using namespace std;

/**
*  @brief Class that contains information of a process
*/
class Process{

public:
	//Default constructor
	Process();

	//Copy constructor
	Process(int); 

	//Asignment operator for variables in class.
	void setData(int, int, int); 
	
	//Prints class variables to the console
	void display();

	//Selectors
	int getID      () {return processID;}
	int getState   () {return state;}
	int getWtTime  () {return waitTime;}
	int getQ       () {return queue;}
	int getB       () {return burstTime;}
	string getFile () {return fileUsed;}

	//Modifiers
	void setID     (int I) 		{processID = I;}	
	void setState  (int S)		{state = S;}
	void setWtTime (int W) 		{waitTime = W;}
	int  setBurst  (int B)		{burstTime = B;}
	void setQueue  (int Q) 		{queue = Q;}
	void setFile   (string F)	{fileUsed = F;}
	
	//Increases variable "burstTime" by one
	void increaseB () 		{burstTime++;}

	//Increases variable "queue" by one
	void increaseQ () 		{queue++;}

		
	
	

private:
	//Local attributes
	int state;		 
	int processID;			
	int waitTime;		
	int queue;		
	int burstTime;
	string fileUsed;
	
};





#endif
