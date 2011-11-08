/*
 * RBNode.cpp
 *
 *  Created on: Oct 23, 2011
 *      Author: mwelch
 */

#include "RBNode.hpp"

// create an empty RBNode
RBNode::RBNode(){
	// new nodes are always RED by convention
	_key = -1;
	_parent = NULL;
	_lchild = NULL;
	_rchild = NULL;
	_color = RED;
}

// create a RBNode with the supplied int data value
RBNode::RBNode(int data){
	_key = data;
	_parent = NULL;
	_lchild = NULL;
	_rchild = NULL;
	_color = RED;
}

// create a RBNode with the supplied Color value
RBNode::RBNode(RBNode *copyMyColor){
	_key = -1;
	_parent = NULL;
	_lchild = NULL;
	_rchild = NULL;
	_color = copyMyColor->_color;
}

// create a RBNode with the supplied data, parent, lchild, and rchild references
RBNode::RBNode(int data, RBNode *parent, RBNode *lchild, RBNode *rchild){
	_key = data;
	_parent = parent;
	_lchild = lchild;
	_rchild = rchild;
	_color = RED;
};

//RBNode destructor
RBNode::~RBNode(){
	// free here??
}

// accessor method for _key member variable
int RBNode::GetKey(){
	return this->_key;
}

// create a string representation of the node (e.g. r,10 )
string RBNode::ToString(){
	//TODO _key should be converted to from an int to a string
	stringstream s;
	if(_color == RED)
		s << "r,";
	else
		s << "b,";
	s << _key;
	string strOut = s.str();
	return (strOut);
}

// set method for _color
void RBNode::SetColor(Color newColor){
	_color = newColor;
}

// change color to match a supplied node
void RBNode::ChangeColor(RBNode *copyMyColor) {
	_color = copyMyColor->_color;
}

//swap colors between two nodes
void RBNode::ColorSwap(RBNode *y) {
	Color tempColor = this->_color;
	this->_color = y->_color;
	y->_color = tempColor;
}

// toggle the color of a node from b->r or r->b
void RBNode::ColorToggle(){
	(_color==RED) ? (_color=BLACK) : (_color=RED);
}

Color RBNode::GetColor(){
	return _color;
}
