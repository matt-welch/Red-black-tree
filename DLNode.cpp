/*
 * DLNode.cpp
 *
 *  Created on: Oct 26, 2011
 *      Author: mwelch
 */

#include "DLNode.hpp"

/*// Doubly Linked List node declaration
class DLNode {
public:
	DLNode();
	~DLNode();
	DLNode(RBNode const &);
	RBNode *_data;
protected:
	DLNode *_next;
	DLNode *_prev;
};*/

// Doubly Linked List node definitions

// default constructor for Doubly Linked List Node
DLNode::DLNode(){
	_next = NULL;
	_prev = NULL;
	_data = NULL;
}

//default destructor for doubly linked list node
DLNode::~DLNode(){}

// overloaded constructor for DLList node, takes a RBNode reference as input
DLNode::DLNode(RBNode *junkNode){
	_next = NULL;
	_prev = NULL;
	_data = junkNode;
}
