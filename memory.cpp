/**************************************************************************************************************************************************************
	Title:		Memory.cpp

	Author:		Edwin Quintuna

	Created On:	5/4/2018

	Description:	Source file.	

	Purpose:	Used to build a memory block made out of a specified number of frames. Number of frames are determined by
			user input of ramMem and pageSize. If our memory size is 10 and we want page size of 2, we will have 5 frames.
			This frames are modifies if we delete, create or ask for a memory operation of a process. 

	Usage:		Memory.cpp
			function definitions

	Build:		"make" Make file is provided.

	Modifications:  May 4, 2018
			Implemented proper code documentation.
			May 5, 2018
			More implementation of proper code documentation.		    
 	 

**************************************************************************************************************************************************************/

#include "memory.h"

/**  
*	@brief Default constructor for Memory that sets default values to local variables of Process class.
*
*	@param 
*	@return nothing
*/
Memory::Memory()
{

    setTable(0,0);
    isFull = 0;

}

/**
*	@brief Copy constructor for Memory that sets up a memory block with frames specified by 
*	user by entering memory size and page size, we get frame numbers by dividing the two.
*
*	@para[mem] , represents the memory size of main memory.
*	@para[page], represents page size.
*	@return nothing
*/
Memory::Memory(unsigned int mem, unsigned int page)
{

    setTable(mem,page);
    isFull = 0;

}

/**
*	@brief function that sets values for memorySize, pageSize and dynamically creates an array of Frame objects
*	using memoriSize/pageSize as its size.The Frame objects will make out our memory table.
*
*	@param[mem] 	, represents the memory size of main memory.
*	@param[page]    , represents the page size of each page.
*	@return nothing
*/
void Memory::setTable(unsigned int mem, unsigned int page)
{
    memorySize = mem;
    pageSize = page;
    frameNum = mem/page;
    RAM = new Frames[frameNum];

}


/**
*	@brief function that fills up a frame "i" in the memory table created by setTable() with default values.
*
*	@param[i] 	, represents the index of the frame in the memory table that will be filled.
*	@return nothing
*/
void Memory::fillFrame(int i)
{
    RAM[i].processID = -1;
    RAM[i].full = 1;
    RAM[i].pageNum = -1;
    RAM[i].timeStamp = -1;
    RAM[i].index = i;
}

/**
*	@brief function that uses fillFrame() to set default values for all the frames in the memory table created by setTable() 
*	and sets the index from 0 to frameNum.
*
*	@param[i] 	, represents the index of the frame in the memory table.
*	@return nothing
*/
void Memory::emptyOut()
{
    for(unsigned int i=0; i < frameNum; i++)
    {
        fillFrame(i);
    }

}


/**
*	@brief function that clears out a RAM[i] frame info and sets them back to default ones to represent that those pages have been flushed.
*
*	@param[&RAM] 	, is a refeerence to one of the elements, RAM[i], of the array RAM[frameNum].
*	@return nothing
*/
void Memory::deleteFrame(Frames &RAM)
{

    RAM.processID = 0;
    RAM.full = 1;
    RAM.pageNum = -1;
    RAM.timeStamp = -1;

}

/**
*	@brief function that clears out a RAM[i] frame variables, by checking the process ID in that frame, and sets them back to default ones to represent *	that those pages have been flushed.
*
*	@param[ID] 	, using a process ID we find frames in the table that has that ID and deletes them.
*	@return nothing
*/
void Memory::deleteFrameIn(int ID)
{

    for(unsigned int i = 0; i < frameNum; i++) {
        if(RAM[i].processID == ID)
        {
            deleteFrame(RAM[i]);
            isFull--;
        }
    }
}


/**
*	@brief function that clears out a RAM[i] frame variables, by checking the process ID in that frame, and sets them back to default ones to represent *	that those pages have been flushed.
*
*	@param[ID] 	, using a process ID extracted from process in CPU, we find the frames belonging to that process in the memory table.
*	@param[Page]	, the page we want to find that has the ID in parameter ID
*	@param[&index]	, refference to an int that will record the index of the page we found so that it's timeStamp can be increased.
*	@return nothing
*/
bool Memory::findPage(int ID, int Page, int &index)
{
    for(unsigned int i = 0; i < frameNum; i++) {

        if(RAM[i].processID == ID && RAM[i].pageNum == Page) {
            index = i;
            return true;
        } else {
            continue;
        }

    }
    LRU();
    return false;
}

/**
*	@brief function that sets local variables using parameters, will replace default process data with data from a process that has been created. 
*
*	@para[P]     , represents a process that has been created and has its own unique data.
*	@para[time]  , represents the time as pages are added to memory table.
*	@para[i]     , represents the index in the table of the frame that we want.
*	@return nothing
*/
void Memory::setValues(Process P, int time, int i)
{
    RAM[i].processID = P.getID();
    RAM[i].full = 0;
    RAM[i].pageNum = 0;
    RAM[i].timeStamp = time;

}

/**
*	@brief overloaded function that sets local variables using parameters, will replace default 
*               process data with data from a process that has been created. 
*
*	@para[index]     , represents index of a frame in the memory table.
*	@para[time]  , represents the time as pages are added to memory table.
*	@para[i]     , represents the index in the table of the frame that we want.
*	@return nothing
*/
void Memory::setValues(int index, int time, int i, int newPage)
{
    RAM[i].processID = index;
    RAM[i].full = 0;
    RAM[i].pageNum = newPage;
    RAM[i].timeStamp = time;

}

/**
*	@brief overloaded function that inserts a page into a memory table . 
*
*	@para[index]     , if process ID is know, insert using it rather then the Process as a whole
*	@para[time]      , Each time a page is added to the memory table, the time stamp is updated.
*	@para[newPage]   , Will set the page on page table.
*	@return nothing
*/
void Memory::insert(int index, int time, int newPage)
{

    if(isFull == frameNum) {
        cout << "Memory is Full" << endl;
	cout << "Pages will start to be replaced!" << endl;
        LRU();
        insert(index, time, newPage);
    } else {

        for(unsigned int i = 0; i < frameNum; i++) {
            if(RAM[i].full == 1)
            {
                setValues(index, time, i, newPage);
                isFull++;
                i = frameNum;
            }
        }
    }

}

/**
*	@brief function that changes the timeStamp of a frame. 
*
*	@para[index]     , Helps us find the memory frame in the memory table.
*	@para[time]      , Each time a page is added to the memory table, the time stamp is updated.
*	@return nothing
*/
void Memory::increaseT(int index, int time)
{
    RAM[index].timeStamp = time;
}

/**
*	@brief function that inserts a process page to a memory frame in the memory table. 
*
*	@para[P]     , Process who's page will be stored into memory table.
*	@para[time]  , Each time a page is added to the memory table, the time stamp is updated.
*	@return nothing
*/
void Memory::insert(Process P, int time)
{

    if(isFull == frameNum) {
        cout << "Memory is Full" << endl;
	cout << "Pages will start to be replaced!" << endl;
        LRU();
        insert(P, time);
    } else {

        for(unsigned int i = 0; i < frameNum; i++) {
            if(RAM[i].full == 1)
            {
                setValues(P, time, i);
                isFull++;
                i = frameNum;
            }
        }
    }
}

/**
*	@brief function that finds the smalles time stamp of a process in a frame of the memory table. 
*
*	@para     , none
*	@return nothing
*/
int Memory::LRU()
{
    int index;
    Frames small = RAM[0];
    for(unsigned int i =1; i < frameNum; i++) {
        if(RAM[i].timeStamp < small.timeStamp)
            small = RAM[i];

    }
    index = small.index;
    isFull--;
    deleteFrame(RAM[index]);
}


/**
*	@brief function that displays memory table and all the pages that have been added. 
*
*	@para     , none
*	@return nothing
*/
void Memory::displayMem()
{

    for(unsigned int i=0; i < frameNum; i++)
    {

        cout << "Frame: " << RAM[i].index << " || " << "P: " << RAM[i].pageNum << " || "
             << "ID: "<< RAM[i].processID << " || " << "Time:" << RAM[i].timeStamp << " || " << "Flag: " << RAM[i].full << endl;
    }
}
