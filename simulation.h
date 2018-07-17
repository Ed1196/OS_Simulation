/**************************************************************************************************************************************************************
	Title:		Simulation.h

	Author:		Edwin Quintuna

	Created On:	5/4/2018

	Description:	Header file.	

	Purpose:	Used to encapsulaten functions and variables from main.	 

	Usage:		Simulation.h
			function prototypes

	Build:		"make" Make file is provided.

	Modifications:  May 14, 2018
			Implemented code documentation.
			May 14, 2018
			More implemented code documentation.		    
 	 

**************************************************************************************************************************************************************/

#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/**
*  @brief Class that contains information of a process
*/
class Simulation{

public:
	//Default constructor
	Simulation();

	//Selectors
	int getRamMem        () {return ramMem;}
	int getPageSize      () {return pageSize;}
	int getDiskNum       () {return diskNum;}
	int getCounter       () {return counter;}
	int getTime          () {return time;}
	string getElement    (int i) {return elems[i];}
	string getInput      () {return input;}

	//Modifiers.
	void setInput();
	void setRamMem();
	void setPageSize();
	void setDiskNum();
	void setElms(int i, string n){elems[i] = n; }
	int incCounter	     () {counter++;}
	int incTime	     () {time++;}	
	
	//Increases variable "burstTime" by one.
	void setValues 	();	

	//Error checker.
	void correctSize();
   	void correctNum();

	//Displays menu.
	void menu(int);

	//Clears screen.
	void clearInput	     () {input.clear();}

private:
	//Local attributes
	unsigned int ramMem;		 
	unsigned int pageSize;
	int diskNum;			
	string input;		
	string elems[100];		
	int counter;
	int time;
	int timeInCpu;
	
};

#endif
