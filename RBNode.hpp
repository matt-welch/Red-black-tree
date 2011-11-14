/*
 * RBNode.h
 *
 *  Created on: Oct 23, 2011
 *      Author: mwelch
 */

#ifndef __RBNODE_H__
#define __RBNODE_H__

typedef enum {RED, BLACK} Color;
typedef enum {NIL, DATA} Name;
#include <string>
#include <cstring>
#include <sstream>
using std::stringstream;
using std::string;

// RedBlack Node declaration
class RBNode {
public:
	RBNode();
	RBNode(int pKey);//1
	RBNode(Name pNilName);// only used when creating NIL nodes
	RBNode(int pKey, Color pColor);//2
	RBNode(int pKey, RBNode *pParent, RBNode *pLchild, RBNode *pRchild, Color pColor);//3
	~RBNode();
	RBNode 	*_parent; // ptr to parent RBNode
	RBNode 	*_lchild; // ptr to left child RBNode
	RBNode 	*_rchild; // ptr to right child RBNode
	void	ColorSwap(RBNode *y); //2 swap colors with incoming node
	Color 	GetColor();// accessor method for _color;
	int 	GetKey();// accessor method for _key;
	void 	SetColor(Color pColor); // mutator method for _color
	void	SetKey(int pKey); // mutator method for _key, only should be used when recycling nodes
	string 	ToString(); // returns the node color and data value for a node (e.g. "r,10")
protected:
	int	 	_key;	 // integer data field
	Color	_color;	 // enum color field (RED/BLACK)
	Name	_name;	// enum name field to distinguish _nil (from other nodes with key=-1)
};
// inclusion guard for __RBNODE_H__
#endif
