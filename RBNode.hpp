/*
 * RBNode.h
 *
 *  Created on: Oct 23, 2011
 *      Author: mwelch
 */

#ifndef __RBNODE_H__
#define __RBNODE_H__

typedef enum {RED, BLACK} Color;
#include <string>
#include <cstring>
#include <sstream>
using std::stringstream;
using std::string;

// RedBlack Node declaration
class RBNode {
public:
	RBNode();
	RBNode(int key);
	RBNode(int key, Color pColor);
	RBNode(Color pColor);
	RBNode(RBNode *copyMyColor);
	RBNode(int key, RBNode *parent, RBNode *lchild, RBNode *rchild);
	RBNode(int key, RBNode *parent, RBNode *lchild, RBNode *rchild, Color pColor);
	RBNode(RBNode *parent, RBNode *lchild, RBNode *rchild);
	~RBNode();
	RBNode 	*_parent; // ptr to parent RBNode
	RBNode 	*_lchild; // ptr to left child RBNode
	RBNode 	*_rchild; // ptr to right child RBNode
	void	ChangeColor(RBNode *copyNode); // copy the color of a given node
	void	ColorSwap(RBNode *y); // swap colors with incoming node
	void	ColorToggle(); // changes a node's color to opposite (R->B, B->R)
	Color 	GetColor();// accessor method for _color;
	int 	GetKey();// accessor method for _key;
	void 	SetColor(Color newColor); // set method for _color
	void 	ToString(); // returns the node color and data value for a node (e.g. "r,10")
protected:
	int	 	_key;	 // integer data field
	Color	_color;	 // enum color field (RED/BLACK)
};
// inclusion guard for __RBNODE_H__
#endif
