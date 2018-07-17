/**************************************************************************************************************************************************************
	Title:		List.cpp

	Author:		Edwin Quintuna

	Created On:	5/4/2018

	Description:	Source file.	

	Purpose:	Used to make double linked lists that will represent our queues.	 

	Usage:		List.h
			function definitions

	Build:		"make" Make file is provided.

	Modifications:  May 7, 2018
			Implemented code documentation.
			May 7, 2018
			More implemented code documentation.		    
 	 

**************************************************************************************************************************************************************/

#include "list.h"

/**
*	@brief Copy constructor that stores a process in a node.
*
*	@param [P]	, Data type stored in the list node.
*	@param [*n]	, pointer to the next node in the list
*	@param [*p]	, pointer to the previous node in the list.
*	@return none
*/
node::node(Process P, node *n, node *p)
{
	data = P; 
	next = n;
	previous = p; 

}

/**
*	@brief Copy constructor that stores a process in a node.
*
*	@param [P]	, Data type stored in the list node.
*	@param [file]	, Sets the file name within the process Data type.
*	@param [*n]	, pointer to the next node in the list
*	@param [*p]	, pointer to the previous node in the list.
*	@return none
*/
node::node(Process P, string file, node *n, node *p)
{
	data = P;
	data.setFile(file); 
	next = n;
	previous = p; 

}

/**
*	@brief Copy constructor that stores a process in a node.
*
*	@param [counter]	, Data type stored in the list node.
*	@param [*n]		, pointer to the next node in the list
*	@param [*p]		, pointer to the previous node in the list.
*	@return none
*/
node::node(int counter, node *n, node *p) 
{
	data.setID(counter);
	next = n;
	previous = p; 

}

node::~node()
{
	
}

/**
*	@brief Adds an object of type process to the head of the list
*
*	@param counter is an int that keeps track of the Process ID and its initialized at main.cpp
*	@return void
*/
void List::toHead(Process P)
{
	node *temp = new node(P);
	temp->next = head;
	head = temp;
		
}

/**
*	@brief Adds an object of type process to the tail of the list
*
*	@param counter is an int that keeps track of the Process ID and its initialized at main.cpp
*	@return void
*/
void List::toTail(Process P)
{
	node *newNode = new node(P);
	node *temp = head;
	newNode->next = NULL;
	
	if(head != NULL)
	{
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		
		temp->next = newNode;
		newNode->previous = temp;
	} else {

		newNode->previous = NULL;
		head = newNode;		
		
		}
}

/**
*	@brief Adds an object of type process to the head of the list
*
*	@param counter is an int that keeps track of the Process ID and its initialized at main.cpp
*	@return void
*/
void List::toHead(int counter)
{
	node *temp = new node(counter);
	temp->next = head;
	head = temp;
		
}

/**
*	@brief Adds an object of type process to the tail of the list
*
*	@param counter is an int that keeps track of the Process ID and its initialized at main.cpp
*	@return void
*/
void List::toTail(int counter)
{
	node *newNode = new node(counter);
	node *temp = head;
	newNode->next = NULL;
	
	if(head != NULL)
	{
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		
		temp->next = newNode;
		newNode->previous = temp;
	} else {

		newNode->previous = NULL;
		head = newNode;		
		
		}
		
}

/**
*	@brief Adds an object of type process to the tail of the list.
*
*	@param [P] 	,Data object that is stored in the node of the list.
*	@param [file]	,used for disk lists that also store a file name.
*	@return void
*/
void List::toTailF(Process P, string file)
{
	node *newNode = new node(P, file);
	node *temp = head;
	newNode->next = NULL;
	
	if(head != NULL)
	{
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		
		temp->next = newNode;
		newNode->previous = temp;
	} else {

		newNode->previous = NULL;
		head = newNode;		
		
		}
}

/**
*	@brief Checks if there is a node in the head of the list.
*
*	@param none
*	@return bool
*/
bool List::emptyHead()
{
	if(head == NULL)
		return true;
	else
		return false;
}

/**
*	@brief Checks if there is a node in the tail of the list.
*
*	@param none
*	@return bool
*/
bool List::emptyTail()
{
	if(tail == NULL)
		return true;
	else
		return false;

}

/**
*	@brief Displays the entire list starting from head and ending at the tail.
*
*	@param none
*	@return none
*/
void List::display()
{
	node *temp = new node();
	temp = head;
	while(temp != NULL)
	{
		(temp->data).display();
		temp = temp->next;
		 
	}
}

/**
*	@brief Displays the entire list starting from head and ending at the tail. Used by disk and disk queue lists to display process data and file stored.
*
*	@param none
*	@return none
*/
void List::displayF()
{
	node *temp = new node();
	temp = head;
	while(temp != NULL)
	{
		(temp->data).display();
		cout << "	- File Name: " << (temp->data).getFile() << endl << endl; 
		temp = temp->next;
		 
	}
}

/**
*	@brief Displays the list from head to tail.
*
*	@param
*	@return data, which is of type process, returns an object with all the information of the PCB
*/
Process List::getHead()
{
	node *current = new node();
	current = head;
	
	return current->data;

}

/**
*	@brief Stores the head of the list on a temp. node, moves the object next on the list to the 
*		front and makes it the list's head, then deletes the temp. node.  
*
*	@param
*	@return
*/
void List::deleteHead()
{
	node *current = new node();
	current = head;
	head = head->next;
	
	delete current;

}


