/**************************************************************************************************************************************************************
	Title:		List.h

	Author:		Edwin Quintuna

	Created On:	5/4/2018

	Description:	Header file.	

	Purpose:	Used to make double linked lists that will represent our queues.	 

	Usage:		List.h
			function prototypes

	Build:		"make" Make file is provided.

	Modifications:  May 7, 2018
			Implemented code documentation.
			May 7, 2018
			More implemented code documentation.		    
 	 

**************************************************************************************************************************************************************/

#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <iostream>
#include "process.h"

using namespace std;
//Creates a node with all the data of a process 
struct node
{
	//Data stored in a list is of type process.
	Process data;		
	
	//Pointer to next item in list.
	node *next;		

	//Pointer to previous item in list.
	node *previous;			

	//Default constructor 
	node() : next(NULL), previous(NULL) {}	

	//Copy constructor
	node(int counter ,node *n = NULL, node *p = NULL);

	//Copy constructor
	node(Process ,node *n = NULL, node *p = NULL);

	//Copy constructor
	node(Process ,string ,node *n = NULL, node *p = NULL);


	~node();	

};

class List
{
	public:
	 
	List() : head(NULL), tail(NULL){}
	
	//Inserting to head of list using an int variable.
	void toHead(int);

	//Inserting to tail of list using an int variable.	
	void toTail(int);	
	
	//Inserting to head of list, passing a process as a variable.
	void toHead(Process P);	

	//Inserting to tail of list, passing a process as a variable.
	void toTail(Process P);	

	//Inserting to tail of list.
	void toTailF(Process P, string file);

	//Display list from head to tail.		
	void display   ();

	//Display list from head to tail, process and file stored in disk is displayed.		
	void displayF  ();

	//Returns the process data type from the head of the list.
	Process getHead();

	//Deletes head of the lists.
	void deleteHead();

	//Checks if head is empty.
	bool emptyHead ();

	//Checks if tail is empty.
	bool emptyTail ();

	//Returns ID of the process in the head of the list.
	int getID		(){return (head->data).getID();}

	//Returns current queue of the process in the head of the list.
	int getQueue		(){return (head->data).getQ();}

	//Returns current queue of the process in the head of the list. 
	string getFileUsed	(){return (head->data).getFile();}	

	//Resets the time burst of a process to 0.	
	void resetBurst		(){(head->data).setBurst(0);}

	//Increases the time burst of a process by 1.
	void increaseBurst	(){(head->data).increaseB();}

	//Returns current time burst of a process.
	int  getBurst		(){return (head->data).getB();}

	//Changes the queue of a process to another queue.
	void incQueue		(){(head->data).increaseQ();}

	//Sets the queue of a process in a node manually.
	void setQueue		(int Q){(head->data).setQueue(Q);};

	//Sets the file name of a file in a node manually. 
	void setFileName	(string filename){(head->data).setFile(filename);}; 

	private:
	
	//Pointers to head and tail of the list.
	node *head;
	node *tail;
};


#endif
