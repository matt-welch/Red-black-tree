/*******************************************************************************
 * FILENAME:	RBNode.cpp
 * DESCRIPTION:	Red-Black Tree Node Member Function Definitions
 * AUTHOR: 		James Matthew Welch [JMW]
 * SCHOOL:		Arizona State University
 * CLASS:		CSE310::Data Structures and Algorithms
 * INSTRUCTOR:	Dr. Guoliang Xue
 * SECTION:		71409
 * TERM:		Fall 2011
 ******************************************************************************/

/*  RBNode has the following member variables:
 *  Public:
 *  	_parent		pointer to parent node in the RB tree
 *  	_lchild 	pointer to the left-child node in the RB tree
 *  	_rchild 	pointer to the right-child node in the RB tree
 *	Protected:
 *		_key		integer data value of the node
 *		_color		enum Color value of the node (RED or BLACK)
 *		_name		enum Name value of the node (NIL or DATA)
 */

#include "RBNode.hpp"
#include <iostream>
#include <string>

#include <sstream>

#include <stdio.h>
#include <stdlib.h>

using std::string;
using std::stringstream;

// RBNode constructor
// create an empty RBNode
RBNode::RBNode(){
	// new nodes are always RED by convention
	_key = -1;
	_color = RED;
}

// RBNode constructor
// create a RBNode with the supplied int data value
/* data bearing nodes get BLACK because they're set
 * to RED @ end of RBInsert algorithm */
RBNode::RBNode(int key){
	_key 	= key;
	_color 	= BLACK;
	_name  	= DATA;
}

// RBNode constructor
// Used only to create a NIL RBNode
RBNode::RBNode(Name pNilName){
	_key 	= -1;
	_color 	= BLACK;
	_name 	= NIL;
}

// RBNode constructor
// create a RBNode with the supplied int data value and Color color value
RBNode::RBNode(int key, Color pColor){
	_key = key;
	_color = pColor;
	_name  	= DATA;
}

// RBNode constructor
// create a RBNode with the supplied data, parent, lchild, rchild, pColor references
RBNode::RBNode(int data, RBNode *parent, RBNode *lchild, RBNode *rchild, Color pColor){
	_key 	= data;
	_parent = parent;
	_lchild = lchild;
	_rchild = rchild;
	_color 	= pColor;
	_name  	= DATA;
}

//RBNode destructor
RBNode::~RBNode(){
	// no deletes necessary, no members are pointers
}

//swap colors between two nodes
void RBNode::ColorSwap(RBNode *y) {
	Color tempColor = this->_color;
	this->_color = y->_color;
	y->_color = tempColor;
}

// accessor method for _color member variable
Color RBNode::GetColor(){
	return _color;
}

// accessor method for _key member variable
int RBNode::GetKey(){
	return this->_key;
}

// mutator method for _color member variable
void RBNode::SetColor(Color newColor){
	if(this->_name == NIL){
		// _nil node should never change his color
		return;
	}
	if(newColor == BLACK || newColor == RED)
		{_color = newColor;}
}

// mutator method for _key member variable
void RBNode::SetKey(int pKey){
	_key = pKey;
}

// create a string representation of the node (e.g. r,10 )
string RBNode::ToString(){
	stringstream buffer;
	if(_color == RED)
		buffer << 'r';
	else
		buffer << 'b';
	buffer << ", " << _key;
	return buffer.str();
}
