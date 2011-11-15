/*
 * DLNode.cpp
 *
 *  Created on: Oct 26, 2011
 *      Author: mwelch
 */

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
