/*******************************************************************************
 * FILENAME:	DLNode.cpp
 * DESCRIPTION:	Doubly-Linked List Node Member Function Definitions
 * AUTHOR: 		James Matthew Welch [JMW]
 * SCHOOL:		Arizona State University
 * CLASS:		CSE310::Data Structures and Algorithms
 * INSTRUCTOR:	Dr. Guoliang Xue
 * SECTION:		71409
 * TERM:		Fall 2011
 ******************************************************************************/

#include "DLNode.hpp"

// Doubly Linked List node definitions

// default constructor for Doubly Linked List Node
DLNode::DLNode(){
	_next = NULL;
	_prev = NULL;
	_data = NULL;
}

//default destructor for doubly linked list node
DLNode::~DLNode(){
	// no deletes necessary, all members are non-pointer
}

// overloaded constructor for DLList node, takes a RBNode reference as input
DLNode::DLNode(RBNode *recycleNode){
	_next = NULL;
	_prev = NULL;
	_data = recycleNode;
}
