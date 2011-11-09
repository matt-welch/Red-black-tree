/* Red Black Tree
 * This source code file comprises the implementation of a RedBlack Binary tree.
 *
 * RBNode Members
 * 		parent	(ptr to parent node)
 * 		lchild	(ptr to left node)
 * 		rchild	(ptr to right node)
 * 		data	(int)
 * 		color (enum/char)
 *
 * RedBlack Tree Operations:
 * 		RB-Fixup
 * 		rotate
 * 		colorSwap
 *		RBWrite (write out the current red-black tree to the screen, where the tree is stored in a pre-order format)
 * 		RBread (read in a red-black tree from a file named RBinput.txt, where the tree is stored in a pre-order format)
 *		RBinsert (insert a new node with the data field given as a parameter of the function and perform the fix-up if necessary)
 *		RBdelete (delete the node whose data field matches the data given as a parameter of the function, and perform the fix-up if necessary)
 *				Maintain a linked list to hold deleted nodes (re-use memory)
 */

#include "RBTree.hpp"
#include "DLList.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

//RBTree default constructor
RBTree::RBTree(){
	// create nodes for root and nil
	_root = new RBNode(BLACK);
	_nil  = new RBNode(BLACK);
	_store = new DLList();
}

//RBTree destructor
RBTree::~RBTree(){
	// clear store out
	// clear out all nodes in tree
}

// delete a node from the tree given its data
RBNode* RBTree::RBDelete(int key){
	RBNode *x;
	RBNode *y;
	RBNode *z = RBSearch(this->_root, key);

	if(z == NULL){ return NULL; }// key is not found in tree

	y = z;								//1 temp pointer set to "trouble node"
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
			RBTransplant(z,z->_rchild);	//14 swap z & z->_rchild
			y->_rchild = z->_rchild;		//15 set right child of y
			y->_rchild->_parent = y;		//16 set parent pointer
			RBTransplant(z,y);			//17 swap z & y
			y->_lchild = z->_lchild;		//18 set left child pointer
			y->_lchild->_parent = y;		//19 set parent pointer
			y->SetColor(z->GetColor());		//20 copy color from z
		}
	}
	if(yOrigColor == BLACK)
		DeleteFixup(x);					//22 run fixup if y was black
	return x;
}

void RBTree::DeleteFixup(RBNode *x){
	RBNode *w;
	while(x != _root && x->GetColor() == BLACK){	//1
		if(x == x->_parent->_lchild){				//2
			w = x->_parent->_rchild;				//3
			if(w->GetColor() == RED){				//4
				w->SetColor(BLACK);					//5 case 1
				x->_parent->SetColor(BLACK);		//6 case 1
				this->LeftRotate(x->_parent);				//7 case 1
				w = x->_parent->_rchild;}			//8 case 1
			if(w->_lchild->GetColor() == BLACK && w->_rchild->GetColor() == BLACK){	//9		if(w.left.color == BLACK && w.right.color == BLACK)
				w->SetColor(RED);					//10 case 2
				x = x->_parent;						//11 case 2
			} else if(w->_rchild->GetColor() == BLACK) { //12
				w->_lchild->SetColor(BLACK);		//13 case 3
				w->SetColor(RED);					//14 case 3
				this->RightRotate(w);						//15 case 3
				w = x->_parent->_rchild;			//16 case 3
			}
			w->SetColor(x->_parent->GetColor());	//17 case 4
			x->_parent->SetColor(BLACK);			//18 case 4
			w->_rchild->SetColor(BLACK);			//19 case 4
			this->LeftRotate(x->_parent);					//20		LEFT-ROTATE(T,x.p)	// case 4
		} else if (x == x->_parent->_rchild){//	22	else if( x == x.p.right )
			w = x->_parent->_lchild;				//3		w = x.p.left
			if(w->GetColor() == RED){				//4		if w.color == RED
				w->SetColor(BLACK);					//5			w.color = BLACK	// case 1
				x->_parent->SetColor(RED);			//6			x.p.color = RED	// case 1
				this->RightRotate(x->_parent);		//7			RIGHT-ROTATE(T,x.p)	// case 1
				w = x->_parent->_lchild;			//8			w = x.p.left		// case 1
			}
			if(w->_rchild->GetColor()==BLACK && w->_lchild->GetColor() == BLACK){//	9		if(w.right.color == BLACK && w.left.color == BLACK)
				w->SetColor(RED);					//10			w.color = RED // case 2
				x = x->_parent;						//11			x = x.p		  // case 2
			} else if (w->_lchild->GetColor() == BLACK){//	12		else if w.left.color == BLACK
				w->_rchild->SetColor(BLACK);		//13			w.right.color = BLACK // case 3
				w->SetColor(RED);					//14			w.color = RED		// case 3
				this->LeftRotate(w);				//15			LEFT-ROTATE(T, w)	// case 3
				w = x->_parent->_lchild;			//16			w = x.p.left		// case 3
			}
			w->SetColor(x->_parent->GetColor());	//17		w.color = x.p.color		// case 4
			x->_parent->SetColor(BLACK);			//18		x.p.color = BLACK		// case 4
			w->_lchild->SetColor(BLACK);			//19		w.left.color = BLACK	// case 4
			this->RightRotate(x->_parent);			//20		RIGHT-ROTATE(T,x.p)		// case 4
		}
		x = this->_root;								//21		x=T.root
		x->SetColor(BLACK);							//23 x.color = BLACK
	}
}

RBNode* RBTree::DeleteFixupLeft(RBNode *x){
	RBNode *w;
	w = x->_parent->_rchild;				//3
	if(w->GetColor() == RED){				//4
		w->SetColor(BLACK);					//5 case 1
		x->_parent->SetColor(BLACK);		//6 case 1
		this->LeftRotate(x->_parent);				//7 case 1
		w = x->_parent->_rchild;}			//8 case 1
	if(w->_lchild->GetColor() == BLACK && w->_rchild->GetColor() == BLACK){	//9		if(w.left.color == BLACK && w.right.color == BLACK)
		w->SetColor(RED);					//10 case 2
		x = x->_parent;						//11 case 2
	} else if(w->_rchild->GetColor() == BLACK) { //12
		w->_lchild->SetColor(BLACK);		//13 case 3
		w->SetColor(RED);					//14 case 3
		this->RightRotate(w);						//15 case 3
		w = x->_parent->_rchild;			//16 case 3
	}
	w->SetColor(x->_parent->GetColor());	//17 case 4
	x->_parent->SetColor(BLACK);			//18 case 4
	w->_rchild->SetColor(BLACK);			//19 case 4
	this->LeftRotate(x->_parent);					//20		LEFT-ROTATE(T,x.p)	// case 4
	return x;
}
RBNode* RBTree::DeleteFixupRight(RBNode *x){
	RBNode *w;
	w = x->_parent->_lchild;				//3		w = x.p.left
	if(w->GetColor() == RED){				//4		if w.color == RED
		w->SetColor(BLACK);					//5			w.color = BLACK	// case 1
		x->_parent->SetColor(RED);			//6			x.p.color = RED	// case 1
		this->RightRotate(x->_parent);		//7			RIGHT-ROTATE(T,x.p)	// case 1
		w = x->_parent->_lchild;			//8			w = x.p.left		// case 1
	}
	if(w->_rchild->GetColor()==BLACK && w->_lchild->GetColor() == BLACK){//	9		if(w.right.color == BLACK && w.left.color == BLACK)
		w->SetColor(RED);					//10			w.color = RED // case 2
		x = x->_parent;						//11			x = x.p		  // case 2
	} else if (w->_lchild->GetColor() == BLACK){//	12		else if w.left.color == BLACK
		w->_rchild->SetColor(BLACK);		//13			w.right.color = BLACK // case 3
		w->SetColor(RED);					//14			w.color = RED		// case 3
		this->LeftRotate(w);				//15			LEFT-ROTATE(T, w)	// case 3
		w = x->_parent->_lchild;			//16			w = x.p.left		// case 3
	}
	w->SetColor(x->_parent->GetColor());	//17		w.color = x.p.color		// case 4
	x->_parent->SetColor(BLACK);			//18		x.p.color = BLACK		// case 4
	w->_lchild->SetColor(BLACK);			//19		w.left.color = BLACK	// case 4
	this->RightRotate(x->_parent);			//20		RIGHT-ROTATE(T,x.p)		// case 4
	return x;
}


RBNode* RBTree::GetRoot(){
	return this->_root;
}

// insert a new node into the tree given its data
RBTree* RBTree::RBInsert(int key){
	RBNode *z = new RBNode(key);
	RBNode *y = this->_nil;		//1
	RBNode *x = this->_root;	//2
	while(x != this->_nil){		//3
		y = x;					//4
		if(z->GetKey() < x->GetKey()){//5
			x = x->_lchild;		//6
		}else {x = x->_rchild;}	//7
	}
	z->_parent = y;				//8
	if(y == this->_nil){		//9
		this->_root = z;		//10
	}else if(z->GetKey() < y->GetKey()){ // 11
		y->_lchild = z;			//12
	}else {y->_rchild = z;}		//13
	z->_lchild = this->_nil;	//14
	z->_rchild = this->_nil;	//15
	z->SetColor(RED);			//16 - redundant since all NEW nodes are red
	InsertFixup(x);				//17
	return this;
}


// fixup the tree after insertion
void RBTree::InsertFixup(RBNode *z){
	RBNode *y;
	while(z->_parent->GetColor() == RED){			//1 while (z.p.color == RED) {
		if(z->_parent == z->_parent->_parent->_lchild){	//2 	if z.p === z.p.p.left
			y = z->_parent->_parent->_rchild;		//3 		y = z.p.p.right
			if(y->GetColor() == RED){				//4		if y.color == RED		// if y-uncle is RED
				z->_parent->SetColor(BLACK);		//5			z.p.color = BLACK	//case 1
				y->SetColor(BLACK);					//6			y.color = BLACK		//case 1
				z->_parent->_parent->SetColor(RED);	//7			z.p.p.color = RED	//case 1
				z = z->_parent->_parent;			//8			z = z.p.p			//case 1
			}else if(z == z->_parent->_rchild){		//9		else if z == z.p.right	// UNCLE IS BLACK
				z = z->_parent;						//10			z = z.p			//case 2
				this->LeftRotate(z);				//11			LEFT-ROTATE(z)	//case 2
			}
			z->_parent->SetColor(BLACK);			//12		z.p.color = BLACK	//case 3
			z->_parent->_parent->SetColor(RED);		//13		z.p.p.color = RED	//case 3
			this->RightRotate(z->_parent->_parent);	//14  	RIGHT-ROTATE(z.p.p)		//case 3
		}else {	//15 z.p === z.p.p.right  (same as then clause with “right” & "left" exchanged)
			y = z->_parent->_parent->_lchild;		//3 		y = z.p.p.left
			if(y->GetColor() == RED){				//4			if y.color == RED
				z->_parent->SetColor(BLACK);		//5				z.p.color = BLACK	//case 1
				y->SetColor(BLACK);					//6				y.color = BLACK		//case 1
				z->_parent->_parent->SetColor(RED);	//7				z.p.p.color = RED	//case 1
				z = z->_parent->_parent;			//8				z = z.p.p			//case 1
			}else if(z == z->_parent->_lchild){		//9		else if z == z.p.left
				z = z->_parent;						//10			z = z.p			//case 2
				this->RightRotate(z);				//11			RIGHT-ROTATE(z)	//case 2
			}
			z->_parent->SetColor(BLACK);			//12		z.p.color = BLACK	//case 3
			z->_parent->_parent->SetColor(RED);		//13		z.p.p.color = RED	//case 3
			this->LeftRotate(z->_parent->_parent);	//14  	LEFT-ROTATE(z.p.p)		//case 3
		}
	}												//	16	}//end while()
}

// left rotation of a parent-child backbone
void RBTree::LeftRotate(RBNode *x){
	RBNode *y;
	y = x->_rchild;
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
	x->ColorSwap(y);

	/* from _Introduction_to_Algorithms_
	LEFT-ROTATE(T,x) // T is tree, x is trouble-node
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
		12 x.p = y		*/
}

// right rotation of a parent-child backbone
void RBTree::RightRotate(RBNode *x){
	RBNode *y;
	y = x->_lchild;
	x->_lchild = y->_rchild; 			// hand beta off to x
	if(y->_rchild != _nil){				// check for leaf
		y->_rchild->_parent = x;}		// assign x as beta-parent
	y->_parent = x->_parent;			// pass parent to y
	if(x->_parent == _nil)				// check for root
		_root = y;
	else if(x == x->_parent->_rchild)	// assign y as correct child of parent
		x->_parent->_rchild = y;
	else x->_parent->_lchild = y;
	y->_rchild = x;						//assign x as y-left child
	x->_parent = y;						//assign y as x-parent

	// color swap (top stays same color, bottom stays same color
	x->ColorSwap(y);

	/* based on Left-Rotate from _Introduction_to_Algorithms_
	RIGHT-ROTATE(T,x) // T is tree, x is trouble-node
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

// read a complete RBTree from an input file
RBTree* RBTree::RBRead(){
// should this do the file input or just be handed a FILE pointer?
	//read root then read left and right?
	return NULL;
}

// iterative tree search based on BST Iterative-Tree-Search(x,k);
RBNode* RBTree::RBSearch(RBNode *traverse, int key){
	if(traverse == this->_nil){ return NULL; } // tree is empty

	while(traverse != this->_nil && key != traverse->GetKey()){
		if(key < traverse->GetKey()){
			traverse = traverse->_lchild;
		}else {traverse = traverse->_rchild;}
	}// at end of while loop, x is pointing to key
	return traverse;
}

RBNode* RBTree::RBTransplant(RBNode *u,RBNode *v){
	if(u->_parent == this->_nil) {		//1: tree is empty
		_root = v; 						//2: 	set new node to root
	} else if(u == u->_parent->_lchild){//3: u is left child
		u->_parent->_lchild = v;		//4: 	set v to lchild
	} else {u->_parent->_lchild = v;}	//5: else set v to rchild
	v->_parent = u->_parent;			//6: set parent
	return u;
}

RBNode* RBTree::RBSuccessor(RBNode *x){
	/*Successor(x)
	 if x.right != nil then
	    return Tree-Minimum(x.right)      //e.g., 15 --> 17
	 y := x.parent			    // e.g., node 13
	 while y != nil and x = y.right do  // find a "right" parent
	     x := y
	     y := y.parent
	 return y*/
	if(x->_rchild != this->_nil){ return TreeMin(x->_rchild); }
	RBNode* y = x->_parent;
	while(y != this->_nil && x == y->_rchild){
		x = y;
		y = y->_parent;
	}
	return y;
}

RBNode* RBTree::TreeMin(RBNode *x){
/*	Tree-Minimum(root)
	 while root != nil and root.left != nil do
	       root = root.left
	 return root */
	while(x != this->_nil && x->_lchild != this->_nil){
		x = x->_lchild;
	}
	return x;
}

RBNode* RBTree::TreeMax(RBNode *x){
/*Tree-Maximum(root)
 while root != nil and root.right != nil do
       root = root.right
 return root */
	while(x != this->_nil && x->_rchild != this->_nil){
		x = x->_rchild;
	}
	return x;
}

#if 1
// write out the current red-black tree to the screen, where the tree is stored in a pre-order format
string RBTree::RBWrite(RBNode *myRoot){
	stringstream accumulator;
	string strOut;

	// base case
	if(myRoot == this->_nil) {accumulator << "";} // tree is empty
	//print root
	accumulator <<  myRoot->ToString();
	//recursively print left
	accumulator <<  RBWrite(myRoot->_lchild);
	//recursively print right
	accumulator <<  RBWrite(myRoot->_rchild);

	strOut = accumulator.str();
	return strOut;
}
#endif


// pseudocode
/*
Inorder-Tree-Walk(x)
if x != nil then
     Inorder-Tree-Walk(x.left)  //left[x]
     print(x.data)		//data[x]
     Inorder-Tree-Walk(x.right)  //right[x]

Preorder-Tree-Walk(x)
if x != nil then
     print(x.data)
     Preorder-Tree-Walk(x.left)
     Preorder-Tree-Walk(x.right)
*/
