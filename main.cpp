/**************************************************************************************************************************************************************
	Title:		main.cpp

	Author:		Edwin Quintuna

	Section: 	34000 03[5379]

	Created On:	5/4/2018

	Description:	Simulates an operating system with multilevel feedback queue 
			scheduling and demand paging.

	Purpose:	Program will demonstrate the different stages of the ready queue,
			main memory, disks and their respective I/O queue's as the user sends inputs
			to the program. FCFS and RR scheduling algorithms are used to implement the 
			ready queue, FCFS scheduling algorithm is used for I/O queues
		 	and demand paging is implemented in main memory. 

	Usage:		main.cpp
			Enter inputs to alter the state of queues and main memory.
			Input "A" to create a new process.
			Input "Q" increases the time Quantum of a process, will determine queue. 
			Input "t" will terminate a process and remove it from main memory.
			Input "d number file_name," where "number is a disk number and file_name the name of a fil, will
				send a process to do I/O on a disk.
			Input "D number," where "number" is a disk number, will indicate that I/O is finish on specified disk.
			Input "m address," where "address" is a logical/virtual address, will request an operation from address,
				if address not present, allocate it to memory.
			Input "S r" display ready queue.
			Input "S i" display disks and respective I/O queues.
			Input "S m" displays main memory.

	Build:		 "make" Make file is provided.

	Modifications:  May 4, 2018
			Implemented code documentation	
			May 11, 2018
			Encapsulated most of the variables in main.cpp by moving them to simulation.cpp	    
 	 

**************************************************************************************************************************************************************/ 

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "list.h"
#include "simulation.h" 
#include "process.h"

using namespace std;

int main()
{

    Simulation mySim;

    //Sets memory size.
    mySim.setRamMem();

    //Sets page size.
    mySim.setPageSize();

    //Checks if page size is bigger than memory size.
    mySim.correctSize();

    //Checks if page size divides memory with no remainder.
    mySim.correctNum();

    //Dynamically creates disk as demanded by user
    vector<List> disks;

    //Dynamically creates disk waiting queue's as demanded by user
    vector<List> IOqueue;

    //Sets disk numbers.
    mySim.setDiskNum();

    //Resizes disk vector to accomodate the size entered by the user.
    disks.resize   (mySim.getDiskNum());

    //Resizes disk waiting queue vector to accomodate the size entered by the user.
    IOqueue.resize (mySim.getDiskNum());

	
    //Creates memory table
    Memory myMemory(mySim.getRamMem(),mySim.getPageSize());

    //Sets default values to table frames
    myMemory.emptyOut();


    //Will create new processes
    vector<Process> newProcess;    

    //Lists for multilevel queues
    List RR_Q0;
    List RR_Q1;
    List FCFS_Q2;

    //CPU list, will only hold one value
    List CPU;

    cout << endl << endl; 

    //Command menu
    mySim.menu(mySim.getDiskNum());

    //Simulation starts
    while(true)
    {
        cout << endl;
        cout << "next_command> ";

        //Get's input from the user for each iteration of the while loop.
        mySim.setInput();

        cout << endl << endl;


        if(mySim.getInput() == "clear")
        {
            cout << string(100, '\n');
        }



        if(mySim.getInput() == "menu")
        {
            cout << endl << endl;
            mySim.menu(mySim.getDiskNum());
        }



	//New process is created.
        if(mySim.getInput() == "A")	
        {
	    //Checks to see if there's a process in CPU, if true move new process to QO
            if(CPU.emptyHead() == true) 
            {
		//Creates new process in vector.
		newProcess.push_back(mySim.getCounter());

		//Move newly created process to CPU.
		CPU.toHead(newProcess[0]);

		//allocates a frame in memory, with page 0 of the new process.
		myMemory.insert(newProcess[0],mySim.getTime());

		//delete node from START list as it's not longer needed.
                newProcess.clear();			

                //Avoid reusing PID counter only increases and will never repeat
		mySim.incCounter();

		//Updates timeStamp	
		mySim.incTime();
		
              //Checks to see if there's a process in CPU, if false proceed to check it's priority queue.
            } else if(CPU.emptyHead() == false)
            {

		//If process is CPU came from Q0 leave it.
                if(CPU.getQueue() == 0)
                {
		    //Creates new process in vector.
                    newProcess.push_back(mySim.getCounter());

		    //Add the new process to the back of Q0 list
                    RR_Q0.toTail(newProcess[0]);
		
		    //allocates a frame in memory, with page 0 of the new process.
                    myMemory.insert(newProcess[0], mySim.getTime());

		    //clear process from vector as it's not longer needed.	
                    newProcess.clear();	
		
  		    //Avoid reusing PID counter by only increases and will never repeat
		    mySim.incCounter();	

		    //Updates timeStamp
		    mySim.incTime();
		
		  //If process is CPU came from Q1, new process get's preempted by new process with Q0.
                } else if (CPU.getQueue() == 1)
                {
		    //Create a new process
                    newProcess.push_back(mySim.getCounter());

		    //Move the process from CPU to Q1
                    RR_Q1.toHead(CPU.getHead());

		    //allocates a frame in memory, with page 0.
                    myMemory.insert(newProcess[0], mySim.getTime());

		    //Delete process from CPU.
                    CPU.deleteHead();

		    //Adds the newly created process to the CPU.
                    CPU.toHead(newProcess[0]);

		    //Cleares the vector where the process was created as we not longer needed and we dont want vector to grow in size if unnecessary.
                    newProcess.clear();

		    //Avoid reusing PID counter only increases and will never repeat
		    mySim.incCounter();	

		    //Updates timeStamp
		    mySim.incTime();		
				
		   //If process is CPU came from Q2, new process get's preempted by new process with Q0.   
                } else if(CPU.getQueue() > 1) {

		    //Creates a new process in vector.
                    newProcess.push_back(mySim.getCounter());

		    //Moves the process from CPU to Q2
                    FCFS_Q2.toHead(CPU.getHead());

		    //allocates a fram in memory, with page 0.
                    myMemory.insert(newProcess[0], mySim.getTime());

		    //Remove process from CPU.
                    CPU.deleteHead();

		    //Adds the newly created process to the CPU.
                    CPU.toHead(newProcess[0]);

		    //Cleares the vector where the process was created as we not longer needed and we dont want vector to grow in size if unnecessary.
                    newProcess.clear();

		    //Avoid reusing PID counter only increases and will never repeat
                    mySim.incCounter();	

		    //Updates timeStamp
		    mySim.incTime();		
                }

            }



        }


	//If preemptive, it keeps it's time quantum, if it did half of it's cpu burst, once it gets back the CPU it will continue it's CPU burst.
	//if process wants to use disk and will reset time quantum
        if(mySim.getInput() == "Q")	//process in CPU time quantum updated +1.
        {


            cout << endl << endl;
	    //Avoids segementation dump do to trying to increase time quantum on an empty CPU with no process.
            if(CPU.emptyHead() == true) {	
		cout << endl;

		//There is no process to increase time quantum for.
                cout << "CPU is idle." << endl;

		//diplays an empty CPU. 
                CPU.display();				

            } else {

		//Check the time quantum of the process using the CPU.
                if(CPU.getQueue() == 0) 	
                {

		    cout << "Time burst exceeded." << endl;
		    cout << "Move process one level down." << endl;
		    cout << "Reset burst." << endl << endl;  

		    //Increase the time quantum that the process has spent on the CPU.                 
		    CPU.incQueue();

		    //Display the CPU.
		    CPU.display();

		    //If Quantum time is 0, add it to the level 0 RR.
                    RR_Q1.toTail(CPU.getHead());

		    //Remove process from CPU.	
                    CPU.deleteHead();

		    //Checks to see if Q0 is empty
                    if(RR_Q0.emptyHead() == false)
                    {
			//Moves a process at the front of Q0 to CPU.
                        CPU.toHead(RR_Q0.getHead());

			//Removes the process that was moved from Q0 to CPU.
                        RR_Q0.deleteHead();
		
		    //Checks to see if Q1 is empty
                    } else if(RR_Q1.emptyHead() == false)
                    {
			//Moves a process at the front of Q1 to CPU.
                        CPU.toHead(RR_Q1.getHead());

			//Removes the process that was moved from Q1 to CPU.
                        RR_Q1.deleteHead();

		    //Checks to see if Q2 is empty
                    } else if (FCFS_Q2.emptyHead() == false) {

			//Moves a process at the front of Q2 to CPU.
                        CPU.toHead(FCFS_Q2.getHead());

			
			CPU.incQueue();

			//Removes the process that was moved from Q1 to CPU.
                        FCFS_Q2.deleteHead();

                    } else {

			cout << endl;
                        cout << "Waiting Queue's are empty!" << endl;

                    }

		//Check the time quantum of the process using the CPU.
                } else if(CPU.getQueue() == 1) {

		    //Check the time quantum of the process using the CPU.
                    if(CPU.getBurst() < 1)
                    {
			//Increase the time spent in the CPU of the process using it.
                        CPU.increaseBurst();

			cout<< "1 burst remaining." << endl << endl;

			//Display the CPU.
			CPU.display();
		
                    } else {

			 cout << "Time burst exceeded." << endl;
			 cout << "Move process one level down." << endl;
			 cout << "Reset burst." << endl << endl;
                        
			//Sets the new queue that the process will be moved to.
                        CPU.incQueue();

			//Ressets the time burst once a process has been moved to a different queue.
			CPU.resetBurst();

			//Display the CPU.
			CPU.display();

			//Moved the process from CPU to Q2
                        FCFS_Q2.toTail(CPU.getHead());

			//Process from CPU has been moved, so delete it from CPU.
                        CPU.deleteHead();

			//CPU has no process running at this point, add one from ready queue's to CPU.
			//Check if there are processes waitng at Q0 as these have the highest priority.
                        if(RR_Q0.emptyHead() == false)
                        {
			    //Move the process at the top of the list to the CPU. 
                            CPU.toHead(RR_Q0.getHead());

			    //Remove process that was just moved from Q0 to CPU, from Q0.
                            RR_Q0.deleteHead();

			//If Q0 is empty, check if there are processes in Q1.
                        } else if(RR_Q1.emptyHead() == false)
                        {
			    //Move the process at the top of the list to the CPU.
                            CPU.toHead(RR_Q1.getHead());

			    //Remove process that was just moved from Q1 to CPU, from Q1.
                            RR_Q1.deleteHead();

			//If Q0 and Q1 are empty, check if there are processes in Q1.
                        } else if (FCFS_Q2.emptyHead() == false) {

			    //Move the process at the top of the list to the CPU.
                            CPU.toHead(FCFS_Q2.getHead());

			    //Remove process that was just moved from Q2 to CPU, from Q2.
                            FCFS_Q2.deleteHead();

                        } else {

                            cout << "Waiting Queue's are empty!" << endl;

                        }
                    }

		//If a Q2 process has the CPU and there are no higher priority processes,
		// it stays in CPU as long as there are no new higher priority processes.
                } else  if(CPU.getQueue() > 1) {

		    //Increase time quantum of process in CPU.
                    CPU.increaseBurst();

		    //Display CPU.
                    CPU.display();
                    cout << "Will run as long as there is no higher level process!" << endl;
                }


            }
        }


	//Removes process and it's respective pages from memory.
        if(mySim.getInput() == "t")
        {
            cout << endl << endl;

	    //Avoids segementation dump do to trying to increase time quantum on an emty CPU with no process.
            if(CPU.emptyHead() == true) {	
		cout<< endl;
                cout << "CPU is idle!!!" << endl;

		//Display CPU.
                CPU.display();

            } else {

		//Will store the ID of the process who is using the CPU.
                int index = CPU.getID();

		//Remove the pages from memory table of the process using the CPU.
                myMemory.deleteFrameIn(index);

		//Remove the process from the CPU.
                CPU.deleteHead();

		//Chooses a new process to use the CPU as the one using it before has been terminates.
		//Check to see if there are processes in Q0.
                if(RR_Q0.emptyHead() == false)
                {
                    CPU.toHead(RR_Q0.getHead());
                    RR_Q0.deleteHead();

		//Check to see if there are processes in Q1.
                } else if (RR_Q1.emptyHead() == false)
                {
                    CPU.toHead(RR_Q1.getHead());
                    RR_Q1.deleteHead();

		//Check to see if there are processes in Q2.
                } else if(FCFS_Q2.emptyHead() == false) {

                    CPU.toHead(FCFS_Q2.getHead());
                    FCFS_Q2.deleteHead();
                } else {
                    cout << "All Queues are empty." << endl;
                }
            }
        }


	//Sends process in CPU to do IO.
        if(mySim.getElement(0) == "d" && mySim.getElement(1) != "NULL" && mySim.getElement(2) != "NULL")
        {
            cout << endl << endl;

            string fileName;
            int Num;
	    //Converts string to int to obtain disk number.
            Num = atoi(mySim.getElement(1).c_str());

	    //Stores filename specified by user in fileName.
            fileName = mySim.getElement(2);

	    //Error check to see if user input an invalid disk number.
            if(Num > (mySim.getDiskNum()-1) || Num <0)
            {

                cout << "Invalid disk number!" << endl;

	    //Checks to see if there is a process doing IO on disk.
            } else if(disks[Num].emptyHead() == true) {

	        
                if(CPU.emptyHead() == true) {	
                    cout << endl;
                    cout << "CPU is idle." << endl;
                    CPU.display();
                    cout << endl;

                } else {
                    CPU.resetBurst();

		    //Moves process from CPU to Disk
                    disks[Num].toHead(CPU.getHead()); 

		    //Sets the filename to the one entered by user
                    disks[Num].setFileName(fileName); 

		    //Cleares up CPU to allow other process in
                    CPU.deleteHead();		  

		    //Process using CPU has moved to disk leaving CPU iddle, a process needs to be added to the CPU from ready queues.
		    //Check Q0 to see if there are processes waiting.
                    if(RR_Q0.emptyHead() == false)
                    {
                        CPU.toHead(RR_Q0.getHead());
                        RR_Q0.deleteHead();

		    //Check Q1 to see if there are processes waiting.
                    } else if (RR_Q1.emptyHead() == false)
                    {
                        CPU.toHead(RR_Q1.getHead());
                        RR_Q1.deleteHead();

		    //Check Q2 to see if there are processes waiting.
                    } else if(FCFS_Q2.emptyHead() == false) {

                        CPU.toHead(FCFS_Q2.getHead());
                        FCFS_Q2.deleteHead();
                    } else {
                        cout << "All Queues are empty." << endl;
                    }
                }
            } else {

		
                if(CPU.emptyHead() == true) {	
                    cout << "CPU is idle." << endl;
                    CPU.display();

                } else {
		    //Reset time quantum as process is about to do IO.
                    CPU.resetBurst();

		    //Move process from CPU to IO queue as Disk is taken by another process.
                    IOqueue[Num].toTailF(CPU.getHead(), fileName);

		    //Remove process from CPU.
                    CPU.deleteHead();

		    //Process using CPU has moved to disk leaving CPU iddle, a process needs to be added to the CPU from ready queues.
		    //Check Q0 to see if there are processes waiting.
                    if(RR_Q0.emptyHead() == false)
                    {
                        CPU.toHead(RR_Q0.getHead());
                        RR_Q0.deleteHead();

		    //Check Q1 to see if there are processes waiting.
                    } else if (RR_Q1.emptyHead() == false)
                    {
                        CPU.toHead(RR_Q1.getHead());
                        RR_Q1.deleteHead();

		    //Check Q2 to see if there are processes waiting.
                    } else if(FCFS_Q2.emptyHead() == false) {

                        CPU.toHead(FCFS_Q2.getHead());
                        FCFS_Q2.deleteHead();
                    } else {
                        cout << "All Queues are empty." << endl;
                    }
                }

            }

	    //Clears the string fileName.
            fileName.clear();
            Num = -1;

        }


	//Signals that process is finish doing IO in specified Disk.
        if(mySim.getElement(0) == "D")
        {
            int Num;
            Num = atoi(mySim.getElement(1).c_str());
            cout << "Disk Number: " << Num << endl;

	    //Error Check: checks for invalid disk number.
            if(Num > (mySim.getDiskNum()-1) || Num <0)
            {
                cout << "Invalid disk number!" << endl;

	    //Checks if there's a process doing IO in Disk.
            } else if(disks[Num].emptyHead() == true) {

                cout << "Disk is Empty!" << endl;

            } else {

		//We check the Quantum time of the process using the Disk.
                if(disks[Num].getQueue() == 0) 	
                {
		    //Checks to see if there is a process in currently using the CPU.
                    if(CPU.emptyHead()==false) {

			//If priorities are the same, add it to Q)
                        if(CPU.getQueue() <= disks[Num].getQueue())
                        {
                            RR_Q0.toTail(disks[Num].getHead());	
                        }

			//checks to see if the priority of CPU is lower then the one in disk
                        if(CPU.getQueue() > disks[Num].getQueue())
                        {
			    //checks to see if process in CPU is of priority Q0
                            if(CPU.getQueue() == 0)
                            {

                                RR_Q0.toHead((CPU.getHead()));
                                CPU.deleteHead();
                                CPU.toHead(disks[Num].getHead());
                            }

			    //checks to see if process in CPU is of priority Q1
                            if(CPU.getQueue() == 1)
                            {
                                RR_Q1.toHead((CPU.getHead()));
                                CPU.deleteHead();
                                CPU.toHead(disks[Num].getHead());

			    //checks to see if process in CPU is of priority Q2
                            } else {
                                FCFS_Q2.toHead((CPU.getHead()));
                                CPU.deleteHead();
                                CPU.toHead(disks[Num].getHead());
                            }
                        }




		    //If there is no process in CPU
                    } else if(CPU.emptyHead()==true)				
                    {
			//Add the process that just finished I/O to the OS
                        CPU.toHead(disks[Num].getHead());			
                    } else {
                        cout << endl;
                        cout << "The following process is using cpu." << endl;

			//If CPU is not empty, show the process that is using CPU
                        CPU.display();
                    }

		    //Delete the process that just finished I/O from disk
                    disks[Num].deleteHead();

		    //check if there is process waiting for I/O queue				
                    if(IOqueue[Num].emptyHead() == true)	
                    {
		    //No process in queue waiting to use Disk
                        cout << endl;
                        cout << "Disk Queue: " << Num <<" empty!" << endl; 
		    //There is a process in waiting queue
                    } else {						

			//get the process from the top of the IOqueue list
                        disks[Num].toHead(IOqueue[Num].getHead());

 			//Once stored in disk, remove it from IOqueue list
                        IOqueue[Num].deleteHead();			

                    }

		//We check the Quantum time of the process using the Disk.
                } else if (disks[Num].getQueue() == 1)
                {
		    //Checks to see if CPU is empty
                    if(CPU.emptyHead()==false) {
			//Process from disk is being added back to ready queue.
			//Checks to see if process in DISK has a lower priority then the one using the CPU.
                        if(CPU.getQueue() <= disks[Num].getQueue())
                        {
                            RR_Q1.toTail(disks[Num].getHead());
                        }
			//Checks to see if process in CPU has a lower priority then the one using the DISK.
                        if(CPU.getQueue() > disks[Num].getQueue())
                        {
			    //Decide what queue the process from CPU is going to be moved to.
			    //Checks if CPU queue is Q0, if so move to the head of that queue.
                            if(CPU.getQueue() == 0)
                            {

                                RR_Q0.toHead((CPU.getHead()));
                                CPU.deleteHead();
                                CPU.toHead(disks[Num].getHead());
                            }
			    //Checks if CPU queue is Q1, if so move to the head of that queue.
                            if(CPU.getQueue() == 1)
                            {
                                RR_Q1.toHead((CPU.getHead()));
                                CPU.deleteHead();
                                CPU.toHead(disks[Num].getHead());

			    //Checks if CPU queue is Q2, if so move to the head of that queue.
                            } else {
                                FCFS_Q2.toHead((CPU.getHead()));
                                CPU.deleteHead();
                                CPU.toHead(disks[Num].getHead());
                            }

                        }

		    //Checks to see if the CPU is empty
                    } else if(CPU.emptyHead()==true)
                    {
                        CPU.toHead(disks[Num].getHead());

		    //Display what process is using the CPU.
                    } else {
                        cout << "The following process is using cpu." << endl;
                        CPU.display();
                    }
                    disks[Num].deleteHead();
                    if(IOqueue[Num].emptyHead() == true)
                    {
                        cout << endl;
                        cout << "I/O Queue is empty!" << endl;
                    } else {
                        disks[Num].toHead(IOqueue[Num].getHead());
                        IOqueue[Num].deleteHead();
                    }

                }

                else {

                    if(CPU.emptyHead()==false) {
                        if(CPU.getQueue() <= disks[Num].getQueue())
                        {
                            FCFS_Q2.toTail(disks[Num].getHead());	//If Quantum time is 0, add it to the level 0 RR
                        }

                        if(CPU.getQueue() > disks[Num].getQueue())
                        {
                            if(CPU.getQueue() == 0)
                            {

                                RR_Q0.toHead((CPU.getHead()));
                                CPU.deleteHead();
                                CPU.toHead(disks[Num].getHead());
                            }
                            if(CPU.getQueue() == 1)
                            {
                                RR_Q1.toHead((CPU.getHead()));
                                CPU.deleteHead();
                                CPU.toHead(disks[Num].getHead());

                            } else {
                                FCFS_Q2.toHead((CPU.getHead()));
                                CPU.deleteHead();
                                CPU.toHead(disks[Num].getHead());
                            }

                        }


                    } else if(CPU.emptyHead()==true)
                    {
                        CPU.toHead(disks[Num].getHead());
                    } else {
                        cout << "The following process is using cpu." << endl;
                        CPU.display();
                    }


                    disks[Num].deleteHead();
                    if(IOqueue[Num].emptyHead() == true)
                    {
                        cout << "I/O Queue is empty!" << endl;
                    } else {
                        disks[Num].toHead(IOqueue[Num].getHead());
                        IOqueue[Num].deleteHead();
                    }
                }
            }

            Num = -1;

        }

	//Check to see if logical address is present in memory.
        if(mySim.getElement(0) == "m" && mySim.getElement(1) != "NULL" )
        {
            cout << endl << endl;
            int logicalMem;
 
	    //Convert the logical address that is currently a screen to an int.
            logicalMem = atoi(mySim.getElement(1).c_str());

            cout << "Logical#: " << logicalMem << endl;

	    //Create page number by dividing logical memory by page size.
            int newPage = logicalMem/mySim.getPageSize();
            cout << "Page#: " << newPage << endl;

	    //Error check
            if(logicalMem < 0) {
                cout << "Invalid logical Memory Address!" << endl;

	    //Error check, CPU is empty
            } else if(CPU.emptyHead() == true) {

                cout << "CPU is idle" << endl;

	    //CPU is not empty.
            } else {

                int index = CPU.getID();
                int tmp;
		
		//Look to see if page is already in memory table.
                if(myMemory.findPage(index, newPage, tmp)) {
                    myMemory.increaseT(tmp, mySim.getTime());
                    mySim.incTime();
                    cout << "Hit" << endl;

		//If page is not in memory table, add it.
                } else {

                    cout << "Miss" << endl;
                    myMemory.insert(index, mySim.getTime(), newPage);
                    mySim.incTime();

                }
            }
        }


	//If command is "S r", display the process in CPU and ready queue's.
        if(mySim.getElement(0) == "S" && mySim.getElement(1) == "r")
        {

            cout << endl << endl;
            cout << "-----------------------------" << endl;
            cout << "-----------------------------" << endl;
	    cout << endl;
            cout << "CPU: " << endl;
            CPU.display();
            cout << endl;
            cout << "-----------------------------" << endl;
            cout << endl;
            cout << "RR_Q0: " << endl;
            RR_Q0.display();
            cout << endl;
            cout << "-----------------------------" << endl;
            cout << endl;
            cout << "RR_Q1: " << endl;
            RR_Q1.display();
            cout << endl;
            cout << "-----------------------------" << endl;
            cout << endl;
            cout << "FCFS_Q2: " << endl;
            FCFS_Q2.display();
            cout << "-----------------------------" << endl;
            cout << "-----------------------------" << endl;
            cout << endl << endl;

        }

	//If command is "S i", displays the process doing IO in Disks and Disk queue's.
        if(mySim.getElement(0) == "S" && mySim.getElement(1) == "i")
        {
            cout << endl << endl;
            for(int i = 0 ; i < mySim.getDiskNum(); i++) {
                if(disks[i].emptyHead() == true) {
                    cout << endl;
                    cout << "Disk " << i << ":" << " Empty!" << endl;
                    cout << endl;
                } else {
                    cout << "-----------------------------" << endl;
                    cout << "-----------------------------" << endl;
                    cout << "DISK: " << i << endl << endl;
                    disks[i].displayF();
                    cout << endl;
                    cout << "-----------------------------" << endl;
                    cout << endl;
                    cout << "Queue for Disk: " << i << endl << endl;
                    IOqueue[i].displayF();
                    cout << "-----------------------------" << endl;
                    cout << "-----------------------------" << endl;
                    cout << endl << endl << endl << endl;
                }
                cout << endl;
            }

        }


	//If command is "S m", displays the process pages in memory.
        if(mySim.getElement(0) == "S" && mySim.getElement(1) == "m")
        {
            myMemory.displayMem();
        }

        mySim.clearInput();
        for(int i = 0 ; i < 100; i ++) {
            mySim.setElms(i, "NULL");
        }
	
        cout << endl << endl;
    }



    return 0;
}














