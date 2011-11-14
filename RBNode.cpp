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

void RBNode::SetKey(int pKey){
	_key = pKey;
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
