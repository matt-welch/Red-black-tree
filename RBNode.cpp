/*
 * RBNode.cpp
 *
 *  Created on: Oct 23, 2011
 *      Author: mwelch
 */

#include "RBNode.hpp"
#include <iostream>
#include <string>

#include <sstream>

#include <stdio.h>
#include <stdlib.h>

using std::string;
using std::stringstream;
using std::stringbuf;

// create an empty RBNode
RBNode::RBNode(){
	// new nodes are always RED by convention
	_key = -1;
	_color = RED;
}

// create a RBNode with the supplied int data value
RBNode::RBNode(int key){
	_key 	= key;
	_color 	= BLACK;
	_name  	= DATA;
}

// create a NIL RBNode
RBNode::RBNode(Name pNilName){
	_key 	= -1;
	_color 	= BLACK;
	_name 	= NIL;
}

// create a RBNode with the supplied int data value and Color color value
RBNode::RBNode(int key, Color pColor){
	_key = key;
	_color = pColor;
	_name  	= DATA;
}

// create a RBNode with the supplied data, parent, lchild, rchild, pColor references
RBNode::RBNode(int data, RBNode *parent, RBNode *lchild, RBNode *rchild, Color pColor){
	_key 	= data;
	_parent = parent;
	_lchild = lchild;
	_rchild = rchild;
	_color 	= pColor;
	_name  	= DATA;
};

//RBNode destructor
RBNode::~RBNode(){
	// free here??
}

//swap colors between two nodes
void RBNode::ColorSwap(RBNode *y) {
	Color tempColor = this->_color;
	this->_color = y->_color;
	y->_color = tempColor;
}

Color RBNode::GetColor(){
	return _color;
}

// accessor method for _key member variable
int RBNode::GetKey(){
	return this->_key;
}

// set method for _color
void RBNode::SetColor(Color newColor){
	if(this->_name == NIL){
		// _nil node should never change his color
		return;
	}
	if(newColor == BLACK || newColor == RED)
		{_color = newColor;}
}

string RBNode::ToString(){
	/*  stringbuf sb;
  string mystr;

  sb.sputn ("Sample string",13);
  mystr=sb.str();

  cout << mystr;*/
	stringbuf buffer;
	string tostring;
	char number[4] = "100";
	if(_color == RED)
		buffer.sputn("r, ", 3);
	else
		buffer.sputn("b, ", 3);
	sprintf(number, "%d", _key);
	buffer.sputn(number, 2);
	tostring = buffer.str();
	return tostring;
}

#if 0
//constructors that are unused
//belongs in header::
RBNode(Color pColor);
RBNode(RBNode *pCopyMyColor);
RBNode(int key, RBNode *pParent, RBNode *pLchild, RBNode *pRchild);
RBNode(RBNode *pParent, RBNode *pLchild, RBNode *pRchild);
//char* 	ToString(); // returns the node color and data value for a node (e.g. "r,10")
void	ChangeColor(RBNode *copyNode); // copy the color of a given node
void	ColorToggle(); // changes a node's color to opposite (R->B, B->R)

//ENDbelongs in header::

// create a RBNode with the supplied int data value
RBNode::RBNode(Color pColor){
	_key 	= -1;
	_color 	= pColor;
	_name  	= DATA;
}

// create a RBNode with the supplied Color value
RBNode::RBNode(RBNode *copyMyColor){
	_key 	= -1;
	_parent = NULL;
	_lchild = NULL;
	_rchild = NULL;
	_color 	= copyMyColor->_color;
	_name  	= DATA;
}

// create a RBNode with the supplied data, parent, lchild, and rchild references
RBNode::RBNode(int data, RBNode *parent, RBNode *lchild, RBNode *rchild){
	_key 	= data;
	_parent = parent;
	_lchild = lchild;
	_rchild = rchild;
	_color 	= RED;
	_name  	= DATA;
};

// create a RBNode with the supplied color, parent, lchild, and rchild references
RBNode::RBNode(RBNode *parent, RBNode *lchild, RBNode *rchild){
	_key 	= -1;
	_parent = parent;
	_lchild = lchild;
	_rchild = rchild;
	_color 	= BLACK;
	_name  	= DATA;
};

// change color to match a supplied node
void RBNode::ChangeColor(RBNode *copyMyColor) {
	_color = copyMyColor->_color;
}

// toggle the color of a node from b->r or r->b
void RBNode::ColorToggle(){
	(_color==RED) ? (_color=BLACK) : (_color=RED);
}

string RBNode::ToString(){
	/*stringstream ss;
	string s;
	char c = 'a';
	ss << c;
	ss >> s;*/
	stringstream buffer;
	string tostring;
	if(_color == RED)
		buffer << 'r';
	else
		buffer << 'b';
	buffer << ", " << _key;
	buffer >> tostring;
	return tostring;
}

// create a string representation of the node (e.g. r,10 )
char* RBNode::ToString(){
	char *colorChar;
	colorChar = (char*)malloc(sizeof(char)*6);
	char keyChar[4]= "100";
	if(_color == RED)
		colorChar[0] = 'r';
	else
		colorChar[0] = 'b';
	colorChar[1] = '\0';
	// convert int value to a char
	sprintf( keyChar, "%d", _key);

	strcat(colorChar, ", \0");
	strcat(colorChar, keyChar);
	//TODO anytime string/cout/stringstream is implemented here, seg faults occur
	return colorChar;
}

// create a string representation of the node (e.g. r,10 )
char* RBNode::ToString(){
	char colorChar;
	char * output;
	if(_color == RED)
		colorChar = 'r';
	else
		colorChar = 'b';

	output = strcat(output, (const)colorChar);
	//TODO anytime string/cout/stringstream is implemented here, seg faults occur
}
#endif
