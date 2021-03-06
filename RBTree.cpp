/*******************************************************************************
 * FILENAME:	RBTree.cpp
 * DESCRIPTION:	Red-Black Tree Member Function Definitions
 * AUTHOR: 		James Matthew Welch [JMW]
 * SCHOOL:		Arizona State University
 * CLASS:		CSE310::Data Structures and Algorithms
 * INSTRUCTOR:	Dr. Guoliang Xue
 * SECTION:		71409
 * TERM:		Fall 2011
 ******************************************************************************/

/* This source code file comprises the implementation of a Red Black Binary tree.
 *
 * RBNode Members
 * 		parent	(ptr to parent node)
 * 		lchild	(ptr to left node)
 * 		rchild	(ptr to right node)
 * 		data	(integer key of the node)
 * 		color 	(enum describing the color of the node (RED/BLACK))
 * 		name	(enum describing the type fo node (DATA/NIL))
 *
 * RedBlack Tree Operations:
 *		RBWrite:	write out the current red-black tree to the screen in a
 *					pre-order format
 * 		RBread:		read in a red-black tree from a file named RBinput.txt,
 * 					where the tree is stored in a pre-order format
 *		RBinsert: 	insert a new node with the data field given as a parameter
 *					of the function and perform the fix-up if necessary
 *		RBdelete:	delete the node whose data field matches the data given as
 *					a parameter of the function, and perform the fix-up if necessary)
 *
 * RedBlack Tree Support Functions:
 * 		RB-Insert-Fixup
 * 		RB_Delete-Fixup
 * 		Left-Rotate
 * 		Right-Rotate
 * 		RBSearch
 *		RBTransplant
 *		RBSuccessor
 *		TreeMax
 *		TreeMin
 * 		Garbage collection in a Doubly-Linked List
 */

#include "RBTree.hpp"
#include "DLList.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;

//RBTree default constructor
RBTree::RBTree(){
	// create nodes for root and nil
	_nil  = NewRBNode(NIL);
	_nil->_lchild = _nil;
	_nil->_rchild = _nil;
	_nil->_parent = _nil;
	_root = _nil;
	_size = 0;
	_store = new DLList();
	_valid = true;
}

//RBTree destructor
RBTree::~RBTree(){
	// clear store out
	DLNode *temp;
	while(!_store->IsEmpty()){
		// delete garbage nodes form the store
		temp = _store->Remove();
		delete(temp->_data);
		delete(temp);
	}
	delete(_store);

	// clear out all nodes in tree
	RBFreeTree(_root);
	delete(_nil);
}

// RBTree destructor helper, recursively deletes each data-bearing node in the tree
void RBTree::RBFreeTree(RBNode *myRoot){
	// recursively traverse the tree, deleting nodes on the way down
	if(myRoot != _nil) {
		RBNode *Left = myRoot->_lchild;
		RBNode *Right = myRoot->_rchild;

		delete(myRoot);
		RBFreeTree(Left);
		RBFreeTree(Right);
	}
}

// Insert helper function for building from a pre-order list of keys/colors
int RBTree::RBInsertFromList(int list[], Color colors[], const int numNodes){
	_size = 0;
	_root = new RBNode(list[_size], _nil, _nil, _nil, BLACK);
	_size++;
	while(_size < numNodes){
		BSTInsert(list[_size], colors[_size]);
		_size++;
	}
	_valid = (!0);
	return _size;
}

// RBNode instantiation helper function
RBNode* RBTree::NewRBNode(Name pNilName){
	RBNode* z = new RBNode(pNilName);
	return z;
}

// RBNode instantiation helper function
RBNode* RBTree::NewRBNode(int key){
	RBNode* z = new RBNode(key);
	z->_lchild = _nil;
	z->_rchild = _nil;
	z->_parent = _nil;
	return z;
}

// RBNode instantiation helper function
RBNode* RBTree::NewRBNode(int pKey, Color pColor){
	RBNode* z = new RBNode(pKey, pColor);
	z->_lchild = _nil;
	z->_rchild = _nil;
	z->_parent = _nil;
	return z;
}

// Binary Search Tree insertion for building the tree
// based on pseudocode from _Introduction_to_Algorithms_
void RBTree::BSTInsert(int key, Color color){
	RBNode* z = NewRBNode(key, color);
	RBNode* y = this->_nil;				// 1 y = NIL
	RBNode* x = this->_root;			// 2 x = T.root
	while(x != this->_nil){				// 3 while x != NIL
		y = x;							// 4	y = x
		if(z->GetKey() < x->GetKey()){	// 5	if z.key < x.key
			x = x->_lchild;				// 6		x = x.left
		}else{x = x->_rchild;}			// 7	else x = x.right
	}
	z->_parent = y;						// 8 z.p = y
	if(y == this->_nil)	{				// 9 if y == NIL
		this->_root = z;				//10	T.root == z	// tree was empty
	}else if(z->GetKey() < y->GetKey()){//11 elseif z.key < y.key
		y->_lchild = z;}				//12 	y.left = z
	else{y->_rchild = z;}				//13 else y.right = z
	z->_lchild = this->_nil;			// set lchild as nil
	z->_rchild = this->_nil;			// set rchild as nil
}

// helper function that calls RBDelete
int RBTree::Delete(int key){
	RBNode *delNode = RBDelete(key);
	if(delNode){
		int delKey = delNode->GetKey();
		this->RecycleNode(delNode);
		return delKey;
	}
	return -1;
}

// RecycleNode saves deleted nodes to the Doubly-Linked List "garbage collector"
void RBTree::RecycleNode(RBNode *x){
	_store->Add(x);
}

// delete a node from the tree given its data
// based on pseudocode from _Introduction_to_Algorithms_
RBNode* RBTree::RBDelete(int key){
	RBNode *z = RBSearch(this->_root, key);
	RBNode *x;

	if(z == NULL || z == _nil){
		// key is not found in tree
		return NULL;
	}

	RBNode *y = z;						//1 temp pointer set to "trouble node"
	Color yOrigColor = y->GetColor();	//2 preserve y orig color
	if(z->_lchild == _nil){				//3 if lchild is nil
		x = z->_rchild;					//4 set x to z's rchild
		RBTransplant(z,z->_rchild);}	//5 swap z & z->rchild
	else if(z->_rchild == _nil){		//6 if rchild of z is nil
		x = z->_lchild;					//7 x is lchild of z
		RBTransplant(z,z->_lchild);}	//8 swap z & z->_lchild
	else {								//	z MUST have 2 children
		y = TreeMin(z->_rchild);		//9 set y to z.successor();
		yOrigColor = y->GetColor();		//10 preserve y orig color
		x = y->_rchild;					//11 set x to right child
		if(y->_parent == z)				//12 successor is also child
			x->_parent = y;				//13 set parent of x to y
		else{							//	successor must not be z's child
			RBTransplant(y,y->_rchild);	//14 swap z & z->_rchild
			y->_rchild = z->_rchild;	//15 set right child of y
			y->_rchild->_parent = y;	//16 set parent pointer
		}
		RBTransplant(z,y);				//17 swap z & y
		y->_lchild = z->_lchild;		//18 set left child pointer
		y->_lchild->_parent = y;		//19 set parent pointer
		y->SetColor(z->GetColor());		//20 copy color from z
	}
	if(yOrigColor == BLACK)
		x = DeleteFixupSmall(x);		//22 run fixup if y was black
	return z;
}

// Delete Fixup after deleting a node from the tree
// based on outer loop of RBDeleteFixup function from _Introduction_to_Algorithms_
RBNode* RBTree::DeleteFixupSmall(RBNode *x){
	while(x != _root && x->GetColor() == BLACK){//1
		if(x == x->_parent->_lchild){			//2 if x is left child of it's parent
			x = DeleteFixupLeft(x);
		}else {									//else x is a right child of it's parent
			x = DeleteFixupRight(x);
		}
	}
	x->SetColor(BLACK);							//23 x.color = BLACK
	return x;
}

// Delete fixup if the "trouble-node" is the left child of its parent
// based on "left child" inner loop of RBDeleteFixup from _Introduction_to_Algorithms_
RBNode* RBTree::DeleteFixupLeft(RBNode *x){
	RBNode *w;
	w = x->_parent->_rchild;				//3
	if(w->GetColor() == RED){				//4
		w->SetColor(BLACK);					//5 case 1
		x->_parent->SetColor(RED);			//6 case 1
		LeftRotate(x->_parent);				//7 case 1
		w = x->_parent->_rchild;}			//8 case 1
	if(w->_lchild->GetColor() == BLACK &&		//9		if(w.left.color == BLACK && w.right.color == BLACK)
			w->_rchild->GetColor() == BLACK){
		w->SetColor(RED);					//10 case 2
		x = x->_parent;						//11 case 2
	} else {
		if(w->_rchild->GetColor() == BLACK) { //12
			w->_lchild->SetColor(BLACK);	//13 case 3
			w->SetColor(RED);				//14 case 3
			RightRotate(w);					//15 case 3
			w = x->_parent->_rchild;			//16 case 3
		}
		w->SetColor(x->_parent->GetColor());//17 case 4
		x->_parent->SetColor(BLACK);		//18 case 4
		w->_rchild->SetColor(BLACK);		//19 case 4
		LeftRotate(x->_parent);				//20 LEFT-ROTATE(T,x.p)	// case 4
		x = _root;							//21		x=T.root
	}
	return x;
}

// Delete fixup if the "trouble-node" is the right child of its parent
// based on "right child" inner loop of RBDeleteFixup from _Introduction_to_Algorithms_
RBNode* RBTree::DeleteFixupRight(RBNode *x){
	RBNode *w;
	w = x->_parent->_lchild;				//3		w = x.p.left
	if(w->GetColor() == RED){				//4		if w.color == RED
		w->SetColor(BLACK);					//5			w.color = BLACK	// case 1
		x->_parent->SetColor(RED);			//6			x.p.color = RED	// case 1
		RightRotate(x->_parent);			//7			RIGHT-ROTATE(T,x.p)	// case 1
		w = x->_parent->_lchild;			//8			w = x.p.left		// case 1
	}
	if(w->_rchild->GetColor()==BLACK &&		//	9		if(w.right.color == BLACK && w.left.color == BLACK)
			w->_lchild->GetColor() == BLACK)
	{
		w->SetColor(RED);					//10			w.color = RED // case 2
		x = x->_parent;						//11			x = x.p		  // case 2
	} else {
		if (w->_lchild->GetColor() == BLACK){//	12		else if w.left.color == BLACK
			w->_rchild->SetColor(BLACK);	//13			w.right.color = BLACK // case 3
			w->SetColor(RED);				//14			w.color = RED		// case 3
			LeftRotate(w);					//15			LEFT-ROTATE(T, w)	// case 3
			w = x->_parent->_lchild;		//16			w = x.p.left		// case 3
		}
		w->SetColor(x->_parent->GetColor());//17		w.color = x.p.color		// case 4
		x->_parent->SetColor(BLACK);		//18		x.p.color = BLACK		// case 4
		w->_lchild->SetColor(BLACK);		//19		w.left.color = BLACK	// case 4
		RightRotate(x->_parent);			//20		RIGHT-ROTATE(T,x.p)		// case 4
		x = _root;							//21		x=T.root
	}
	return x;
}

// insert a new node into the tree given its data
// pseudocode from _Introduction_to_Algorithms_
RBTree* RBTree::RBInsert(int key){

	if(_root != _nil && this->RBSearch(_root, key) != _nil){
		return NULL;
	}
	RBNode *z;
	if(this->_store->IsEmpty()){
		z = NewRBNode(key);
	}else {
		z = this->_store->Remove()->_data;
		z->SetKey(key);
		z->SetColor(BLACK);
	}

	RBNode *y = this->_nil;		//1 		y = T.nil
	RBNode *x = this->_root;	//2 		x = T.root
	while(x != this->_nil){		//3 		while x != T.nil
		y = x;					//4				y = x
		if(z->GetKey() < x->GetKey()){//5		if z.key < x.key
			x = x->_lchild;		//6 				x = x.left
		}else {x = x->_rchild;}	//7				else x = x.right
	}
	z->_parent = y;				//8			z.p = y
	if(y == this->_nil){		//9 		if y == T.nil
		this->_root = z;		//10			T.root = z;
	}else if(z->GetKey() < y->GetKey()){//11else if z.key < y.key
		y->_lchild = z;			//12			y.left = z
	}else {y->_rchild = z;}		//13		else y.right = z
	z->_lchild = this->_nil;	//14		z.left = T.nil
	z->_rchild = this->_nil;	//15		z.right = T.nil
	z->SetColor(RED);			//16 		z.color = RED
	this->InsertFixup(z);		//17		RBInsertFixup(T,z)
	return this;
}

// fixup the tree after insertion
// pseudocode from _Introduction_to_Algorithms_
void RBTree::InsertFixup(RBNode *z){
	RBNode *y;
	while(z->_parent != _nil && z->_parent->GetColor() == RED){			//1 while (z.p.color == RED) {
		if(z->_parent == z->_parent->_parent->_lchild){	//2 	if z.p === z.p.p.left
			y = z->_parent->_parent->_rchild;		//3 		y = z.p.p.right
			if(y->GetColor() == RED){				//4		if y.color == RED		// if y-uncle is RED
				z->_parent->SetColor(BLACK);		//5			z.p.color = BLACK	//case 1
				y->SetColor(BLACK);					//6			y.color = BLACK		//case 1
				z->_parent->_parent->SetColor(RED);	//7			z.p.p.color = RED	//case 1
				z = z->_parent->_parent;			//8			z = z.p.p			//case 1
			}else{									// UNCLE IS BLACK
				if(z == z->_parent->_rchild){		//9		else if z == z.p.right
					z = z->_parent;					//10			z = z.p			//case 2
					this->LeftRotate(z);			//11			LEFT-ROTATE(z)	//case 2
				}
				z->_parent->SetColor(BLACK);		//12		z.p.color = BLACK	//case 3
				z->_parent->_parent->SetColor(RED);	//13		z.p.p.color = RED	//case 3
				this->RightRotate(z->_parent->_parent);	//14  	RIGHT-ROTATE(z.p.p)		//case 3
			}
		}else {	//15 z.p === z.p.p.right  (same as then clause with “right” & "left" exchanged)
			y = z->_parent->_parent->_lchild;		//3 		y = z.p.p.left
			if(y->GetColor() == RED){				//4			if y.color == RED
				z->_parent->SetColor(BLACK);		//5				z.p.color = BLACK	//case 1
				y->SetColor(BLACK);					//6				y.color = BLACK		//case 1
				z->_parent->_parent->SetColor(RED);	//7				z.p.p.color = RED	//case 1
				z = z->_parent->_parent;			//8				z = z.p.p			//case 1
			}else {									// UNCLE IS BLACK
				if(z == z->_parent->_lchild){		//9		else if z == z.p.left
					z = z->_parent;					//10			z = z.p			//case 2
					this->RightRotate(z);			//11			RIGHT-ROTATE(z)	//case 2
				}
				z->_parent->SetColor(BLACK);		//12		z.p.color = BLACK	//case 3
				z->_parent->_parent->SetColor(RED);	//13		z.p.p.color = RED	//case 3
				this->LeftRotate(z->_parent->_parent);	//14  	LEFT-ROTATE(z.p.p)		//case 3
			}
		}
	}
	this->_root->SetColor(BLACK);					//	16	}//end while()} T.root.color = BLACK
}

// left rotation of a parent-child backbone
// based on pseudocode for RBLeftRotate from _Introduction_to_Algorithms_
void RBTree::LeftRotate(RBNode *x){
/*LeftRotate(x) from _Introduction_to_Algorithms_ */
	RBNode *y = x->_rchild;
	x->_rchild = y->_lchild; 			// hand beta off to x
	if(y->_lchild != _nil){				// check for leaf
		y->_lchild->_parent = x;}		// assign x as beta-parent
	y->_parent = x->_parent;			// pass parent to y

	if(x->_parent == _nil)				// check for root
		_root = y;
	else if(x == x->_parent->_lchild)	// assign y as correct child of parent
		x->_parent->_lchild = y;
	else x->_parent->_rchild = y;

	y->_lchild = x;						//assign x as y-left child
	x->_parent = y;						//assign y as x-parent

	// color swap (top stays same color, bottom stays same color
	//x->ColorSwap(y);
	 /* LEFT-ROTATE(T,x) // T is tree, x is trouble-node
		1 y = x.right		//set y
		2 x.right=y.left	//turn y's left subtree into x's right subtree
		3 if y.left != T:nil
		4     y.left.p=x
		5 y.p=x.p			// link x's parent to y
		6 if x.p == T.nil
		7     T.root = y
		8 elseif x == x.p.left
		9     x.p.left = y
		10 else x.p.right = y
		11 y.left = x		// put x on y's left
		12 x.p = y */
}

// right (clockwise) rotation of a parent-child backbone
// based on pseudocode for RBRightRotate from _Introduction_to_Algorithms_
void RBTree::RightRotate(RBNode *x){
/* based on Left-Rotate from _Introduction_to_Algorithms_ */
	RBNode *y = x->_lchild;						//1 y = x.left
	x->_lchild = y->_rchild; 			//2 x.left = y.right 	//hand beta off to x
	if(y->_rchild != _nil){				//3 if y.right != T.nil // check for leaf
		y->_rchild->_parent = x;}		//4 	y.right.p = x 	// assign x as beta-parent
	y->_parent = x->_parent;			//5 y.p = x.p			// pass parent to y

	if(x->_parent == _nil)				//6 if x.p = T.nil		// check for root
		_root = y;						//7 	T.root = y
	else if(x == x->_parent->_rchild)	//8 elseif x == x.p.right // assign y as correct child of parent
		x->_parent->_rchild = y;		//9		x.p.right = y
	else x->_parent->_lchild = y;		//10 else x.p.left = y

	y->_rchild = x;						//11 y.right = x			//assign x as y-left child
	x->_parent = y;						//12 x.p = y				//assign y as x-parent

	// color swap (top stays same color, bottom stays same color
	//x->ColorSwap(y);

	/*RIGHT-ROTATE(T,x) // T is tree, x is trouble-node
	1 y = x.left		//set y
	2 x.left=y.right	//turn y's right subtree into x's left subtree
	3 if y.right != T.nil
	4     y.right.p=x
	5 y.p=x.p			// link x's parent to y
	6 if x.p == T.nil
	7     T.root = y
	8 else if x == x.p.right
	9     x.p.right = y
	10 else x.p.left = y
	11 y.right = x		// put x on y's right
	12 x.p = y
 */
}

// iterative tree search
// based on BST Iterative-Tree-Search(x,k) from _Introduction_to_Algorithms_
RBNode* RBTree::RBSearch(RBNode *traverse, int key){
	if(traverse == this->_nil){ return NULL; } // tree is empty

	while(traverse != this->_nil && key != traverse->GetKey()){
		if(key < traverse->GetKey()){
			traverse = traverse->_lchild;
		}else {traverse = traverse->_rchild;}
	}// at end of while loop, traverse is pointing to key
	return traverse;
}

// find the successor (next in sequence) of a given node
// pseudocode from _Introduction_to_Algorithms_
RBNode* RBTree::RBSuccessor(RBNode *x){
	if(x->_rchild != this->_nil){ return TreeMin(x->_rchild); }
	RBNode* y = x->_parent;
	while(y != this->_nil && x == y->_rchild){
		x = y;
		y = y->_parent;
	}
	return y;
	/*Successor(x)
	if x.right != nil then
	    return Tree-Minimum(x.right)      //e.g., 15 --> 17
	y := x.parent			    // e.g., node 13
	while y != nil and x = y.right do  // find a "right" parent
	     x := y
	     y := y.parent
	return y	*/
}

// based on BST-Transplant, but assign v.p unconditionally
// pseudocode from _Introduction_to_Algorithms_
RBNode* RBTree::RBTransplant(RBNode *u,RBNode *v){
	if(u->_parent == this->_nil) {		//1: tree is empty
		_root = v; 						//2: 	set new node to root
	} else if(u == u->_parent->_lchild){//3: u is left child
		u->_parent->_lchild = v;		//4: 	set v to lchild
	} else {
		u->_parent->_rchild = v;		//5: else set v to rchild
	}
	v->_parent = u->_parent;			//6: set parent
	return v;
}

// TreeMin returns the minimum key of a subtree
// pseudocode from _Introduction_to_Algorithms_
RBNode* RBTree::TreeMin(RBNode *x){
	while(x != this->_nil && x->_lchild != this->_nil){
		x = x->_lchild;
	}
	return x;
	/*Tree-Minimum(root)
		while root != nil and root.left != nil do
			root = root.left
		return root */
}

// TreeMax returns the maximum key from a subtree
// pseudocode from _Introduction_to_Algorithms_
RBNode* RBTree::TreeMax(RBNode *x){
	while(x != this->_nil && x->_rchild != this->_nil){
		x = x->_rchild;
	}
	return x;
	/*Tree-Maximum(root)
	 while root != nil and root.right != nil do
	       root = root.right
	 return root */
}

// write out the current red-black tree to the screen, in a pre-order format
// helper function calls RBTree::Write
void RBTree::RBWrite(){
	cout << endl;
	this->Write(_root);
	cout << endl;
}

// write out the current red-black tree to the screen in a pre-order format
void RBTree::Write(RBNode *myRoot){
	// base case: tree is empty
	if(myRoot == this->_nil) {
		return;
	}

	//print semicolon only after root
	if(myRoot != this->_root){
		cout << ";" << endl;
	}

	// print myRoot
	cout << myRoot->ToString();
	//recursively print left
	Write(myRoot->_lchild);
	//recursively print right
	Write(myRoot->_rchild);
}
