/**************************************************************************************************************************************************************
	Title:		Memory.h

	Author:		Edwin Quintuna

	Created On:	5/4/2018

	Description:	Header file.	

	Purpose:	Used to build a memory block made out of a specified number of frames by the user. This frames
			are modifies if we delete, create or ask for a memory operation of a process. 

	Usage:		Memory.h
			function prototypes

	Build:		"make" Make file is provided.

	Modifications:  May 4, 2018
			Implemented proper code documentation.
			May 5, 2018
			More implementation of proper code documentation.		    
 	 

**************************************************************************************************************************************************************/

#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED
#include <iostream>
#include "process.h"

using namespace std;

/**
*  @brief Struct that contains information that each individual frame in memory will have. 
*/
struct Frames 
{
	//Local attributes
	int index;
	bool full;
	int processID;
	int pageNum;
	int timeStamp;	

};

class Memory{
/**
*  @brief Class that builds an empty memory block with the number of frames specified by the user.
*/
public:
	//Default constructor
	Memory(); 

	//Copy constructor
	Memory			(unsigned int, unsigned int);  

	//Modifiers
	void setTable		(unsigned int, unsigned int); 
	void setValues		(Process P, int time, int i);
	void setValues		(int index, int time, int i, int newPage);
	void insert		(Process P, int);
	void insert		(int index, int time,int newPage);
	void increaseT		(int index, int time);
	
	//Sets up an empty RAM will frames with default values.
	void emptyOut		();

	//Displays main memory to console.
	void displayMem		();

	//Sets up an empty RAM frame with default values.
	void fillFrame		(int i); 

	//Delete frame by frame object.
	void deleteFrame	(Frames &); 

	//Delete frame by index number
	void deleteFrameIn	(int);	

	//Returns true if we find a page of a process in memory.
	bool findPage	(int , int, int &);

	//Finds the processes with the lowest timeStamp.
	int LRU();


private:
	//Local attributes
	unsigned int memorySize;
	unsigned int pageSize;
	unsigned int frameNum;

	int storedProcess;
	int storedPage;
	unsigned int isFull;
	Frames *RAM;

	
	
};



#endif
