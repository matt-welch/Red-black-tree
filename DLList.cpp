/*
 * DLList.cpp
 *
 *  Created on: Oct 26, 2011
 *      Author: mwelch
 */

#include "DLList.hpp"

/* Doubly Linked List to hold "deleted" values */

// Doubly Linked List to hold "deleted" values: function definitions
DLList::DLList(){
	// default constructor for doubly linked list
	_head = NULL;
	_tail = NULL;
	_size = 0;
}

// default destructor for doubly linked list
DLList::~DLList(){
	// delete node by node, but this should be done by RBTree
	while(!this->IsEmpty()){
		delete(Remove());
	}
	delete _head;
	delete _tail;
}

// checks to see if the list is empty
bool DLList::IsEmpty(){
	if(_size == 0) {
		return true;
	}
	return false;
}

// adds a new node to the end of the list
void DLList::Add(RBNode *deletedNode){
	DLNode *newNode = new DLNode(deletedNode);
	if(_size==0){
		_head = newNode;
		_tail = newNode;
	}
	else{
		DLNode *temp;
		temp = _tail;
		_tail->_next = newNode;
		_tail = newNode;
		_tail->_prev = temp;
	}
	_size++;
}

// removes the last node (tail) from the list and returns it for re-use
DLNode* DLList::Remove(){
	// check for empty list
	if(_size==0)return NULL;

	// make a node ptr to hand out
	DLNode *outNode = _tail;

	// list is not empty, check for singleton
	if(_size==1){// only one left
		_head = NULL;
		_tail = NULL;
	}else{// 2+ nodes in the list
		_tail->_prev->_next = NULL;
		_tail = outNode->_prev;
		outNode->_prev = NULL;
	}
	//decrement size for removed node
	_size--;

	// return node
	return outNode;
}
