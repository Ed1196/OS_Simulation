/**************************************************************************************************************************************************************
	Title:		Simulation.cpp

	Author:		Edwin Quintuna

	Created On:	5/4/2018

	Description:	Source file.	

	Purpose:	Used to encapsulaten functions and variables from main.	 

	Usage:		Simulation.cpp
			function definitions.

	Build:		"make" Make file is provided.

	Modifications:  May 14, 2018
			Implemented code documentation.
			May 14, 2018
			More implemented code documentation.		    
 	 

**************************************************************************************************************************************************************/

#include "simulation.h"

/**  
*	@brief Default constructor for Simulation that sets default values to local variables of Process class.
*
*	@param 
*	@return nothing
*/
Simulation::Simulation()
{
	ramMem = 0;		 
	pageSize = 0;
	diskNum = 0;			
	input = " ";				
	counter = 1;
	time = 1;
	timeInCpu = 0;
}

/**  
*	@brief Function that gets user's input for the size of the memory and checks if it's a valid input.
*
*	@param 
*	@return nothing
*/
void Simulation::setRamMem()
{
	 cout << "RAM memory: " << endl;
	 cin >> ramMem;

   	 while(!cin.good()) {

        cout << endl;

        cout << "Invalid input." << endl;
        cin.clear();
        cin.ignore(100, '\n');

        cout << endl;
        cout << "RAM memory: " << endl;
        cin >> ramMem;
    }
}

/**  
*	@brief Function that gets user's input for the size of the page size and checks if it's a valid input.
*
*	@param 
*	@return nothing
*/
void Simulation::setPageSize()
{
	 cout << endl;

   	 cout << "Page size: " << endl;
	 cin >> pageSize;

   	 while(!cin.good()) {
        cout << endl;

        cout << "Invalid input." << endl;
        cin.clear();
        cin.ignore(100, '\n');

        cout << endl;
        cout << "Page size: " << endl;
        cin >> pageSize;
    }
}

/**  
*	@brief Function that gets user's input for number of the disks and checks if it's a valid input.
*
*	@param 
*	@return nothing
*/
void Simulation::setDiskNum()
{

	 cout << endl;

   	 cout << "Disk numbers: " << endl;
	 cin >> diskNum;

   	 while(!cin.good()) {

        cin.clear();
        cin.ignore(100, '\n');

        cout << "Disk number: " << endl;
        cin >> diskNum;
    }
}

/**  
*	@brief Function that gets user's input as a string that will be parse through and split into different sections.
*	@param 
*	@return nothing
*/
void Simulation::setInput()
{

    getline(cin , input);
    string tmp;
    istringstream iss(input);

    int i = 0;

    for(int i = 0 ; i < 100; i++) {
        getline(iss, tmp, ' ');
        elems[i] = tmp;
        tmp = "NULL";

    }

    tmp.clear();
    iss.clear();


}

/**  
*	@brief Function that checks the correctness of the memory table. If the pageSize is bigger than ramMem, then a warning is given.
*
*	@param 
*	@return nothing
*/
void Simulation::correctSize()
{
	if(pageSize > ramMem) {
	cout << endl;
        cout << "Page size is bigger than memory!" << endl;
    }
}

/**  
*	@brief Function that checks the correctness of the memory table. If the pageSize doesn't divide ramMem completly, then a warning is given.
*
*	@param 
*	@return nothing
*/
void Simulation::correctNum()
{
	if((ramMem % pageSize) != 0) {
	cout << endl;
        cout << "WARNING!!!!!!" << endl;
         cout << "Page size divided by memory size has a left over!!!!!" << endl;
	cout << "Frames: " << ramMem/pageSize << " " << endl;
	cout << "Left over bytes: " << ramMem % pageSize << endl;
	cout << endl;
    }
}

void Simulation::menu(int diskNum)
{

    cout << "*COMMANDS*" << endl;
    cout << " 1. Create Process          [A] "               << endl
         << " 2. Increase Time Quantum   [Q] "               << endl
         << " 3. Delete CPU process      [t] "               << endl
         << " 4. Read file from disk#    [d num file] "      << endl
         << " 5. Disk# I/O has finish    [D num] "           << endl
         << " 6. CPU request log Addr.   [m address] "       << endl
         << " 7. Show CPU and Queues     [S r] "             << endl
         << " 8. Show hard disk          [S i] "             << endl
         << " 9. Display Memory          [S m] "             << endl
         << "10. Display Menu            [menu] "      	 << endl
         << "11. Clear Screen            [clear] "      	 << endl << endl;
    cout << "*DISKS*" << endl;
    for(int i = 0; i < diskNum ; i++) {
        cout << "Disk[" << i << "]" << "   ";
    }
    cout << endl;
}
