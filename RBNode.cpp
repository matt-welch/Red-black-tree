/*
 * RBNode.cpp
 *
 *  Created on: Oct 23, 2011
 *      Author: mwelch
 */

#include "RBNode.hpp"
#include <iostream>
#include <string>
using std::cout;
using std::string;

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

// create a RBNode with the supplied int data value and Color color value
RBNode::RBNode(int data, Color pColor){
	_key = data;
	_parent = NULL;
	_lchild = NULL;
	_rchild = NULL;
	_color = pColor;
}

// create a RBNode with the supplied int data value
RBNode::RBNode(Color pColor){
	_key 	= -1;
	_parent = NULL;
	_lchild = NULL;
	_rchild = NULL;
	_color 	= pColor;
}

// create a RBNode with the supplied Color value
RBNode::RBNode(RBNode *copyMyColor){
	_key 	= -1;
	_parent = NULL;
	_lchild = NULL;
	_rchild = NULL;
	_color 	= copyMyColor->_color;
}

// create a RBNode with the supplied data, parent, lchild, and rchild references
RBNode::RBNode(int data, RBNode *parent, RBNode *lchild, RBNode *rchild){
	_key 	= data;
	_parent = parent;
	_lchild = lchild;
	_rchild = rchild;
	_color 	= RED;
};

// create a RBNode with the supplied data, parent, lchild, rchild, pColor references
RBNode::RBNode(int data, RBNode *parent, RBNode *lchild, RBNode *rchild, Color pColor){
	_key 	= data;
	_parent = parent;
	_lchild = lchild;
	_rchild = rchild;
	_color 	= pColor;
};

// create a RBNode with the supplied color, parent, lchild, and rchild references
RBNode::RBNode(RBNode *parent, RBNode *lchild, RBNode *rchild){
	_key 	= -1;
	_parent = parent;
	_lchild = lchild;
	_rchild = rchild;
	_color 	= BLACK;
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
void RBNode::ToString(){
	//TODO _key should be converted to from an int to a string
	char colorChar;
//	string strOut;
	if(_color == RED)
		colorChar = 'r';
	else
		colorChar = 'b';
//	strOut = colorChar + ", ";
//	return strOut;
	//TODO anytime string/cout/stringstream is implemented here, seg faults occur
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
