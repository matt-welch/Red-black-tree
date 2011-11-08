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
RBNode* RBTree::RBDelete(int data){
	return NULL;
}

void RBTree::DeleteFixup(RBNode *x){
	RBNode *w;
	while(x != _root && x->GetColor() == BLACK){	//1
		if(x == x->_parent->_lchild){				//2
			w = x->_parent->_rchild;				//3
			if(w->GetColor() == RED){				//4
				w->SetColor(BLACK);					//5 case 1
				x->_parent->SetColor(BLACK);		//6 case 1
				LeftRotate(x->_parent);				//7 case 1
				w = x->_parent->_rchild;}			//8 case 1
			if(w->_lchild->GetColor() == BLACK && w->_rchild->GetColor() == BLACK){	//9		if(w.left.color == BLACK && w.right.color == BLACK)
				w->SetColor(RED);					//10 case 2
				x = x->_parent;						//11 case 2
			} else if(w->_rchild->GetColor() == BLACK) { //12
				w->_lchild->SetColor(BLACK);		//13 case 3
				w->SetColor(RED);					//14 case 3
				RightRotate(w);						//15 case 3
				w = x->_parent->_rchild;			//16 case 3
			}
			w->SetColor(x->_parent->GetColor());	//17 case 4
			x->_parent->SetColor(BLACK);			//18 case 4
			w->_rchild->SetColor(BLACK);			//19 case 4
			LeftRotate(x->_parent);					//20		LEFT-ROTATE(T,x.p)	// case 4
			x = _root;								//21		x=T.root
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
			x = this->_root;						//21		x=T.root
		}
		x->SetColor(BLACK);							//23 x.color = BLACK
	}
	/* RB-DELETE-FIXUP(T, x)
 * // x points to dbl black node inside while{}
1  while x != T.root and x.color == BLACK
2 	if x == x.p.left
3 		w = x.p.right
4		if w.color == RED
5			w.color = BLACK				// case 1
6			x.p.color = RED				// case 1
7			LEFT-ROTATE(T,x.p)			// case 1
8			w = x.p.right				// case 1
9		if(w.left.color == BLACK && w.right.color == BLACK)
10			w.color = RED				// case 2
11			x = x.p						// case 2
12		else if w.right.color == BLACK
13			w.left.color = BLACK		// case 3
14			w.color = RED				// case 3
15			RIGHT-ROTATE(T, w)			// case 3
16			w = x.p.right				// case 3
17		w.color = x.p.color				// case 4
18		x.p.color = BLACK				// case 4
19		w.right.color = BLACK			// case 4
20		LEFT-ROTATE(T,x.p)				// case 4
21		x=T.root
22	else if( x == x.p.right )
3		w = x.p.left
4		if w.color == RED
5			w.color = BLACK				// case 1
6			x.p.color = RED				// case 1
7			RIGHT-ROTATE(T,x.p)			// case 1
8			w = x.p.left				// case 1
9		if(w.right.color == BLACK && w.left.color == BLACK)
10			w.color = RED				// case 2
11			x = x.p						// case 2
12		else if w.left.color == BLACK
13			w.right.color = BLACK		// case 3
14			w.color = RED				// case 3
15			LEFT-ROTATE(T, w)			// case 3
16			w = x.p.left				// case 3
17		w.color = x.p.color				// case 4
18		x.p.color = BLACK				// case 4
19		w.left.color = BLACK			// case 4
20		RIGHT-ROTATE(T,x.p)				// case 4
21		x=T.root
23 x.color = BLACK
 * */
}

// insert a new node into the tree given its data
RBTree* RBTree::RBInsert(int key){
	// create a new node
	// attach pointers
	RBNode *z = new RBNode(key);
	RBNode *x = this->_root;
	RBNode *y;
	if(x == this->_nil){
		_root = z;
		return this;
	}else {
		while( x != this->_nil ){
			y =x;
			if(key < x->GetKey() ){ x = x->_lchild;	}
			else { x = x->_rchild;}
		}
		z->_parent = y;
		if(key < y->GetKey()) { y->_lchild = z;}
		else {y->_rchild = z;}
	}
	/*//BST-Insert
	 z := new-treenode(key, nil, nil, nil)
	 x := root[T]
	 if x = nil then root[T] = z return
	   else
		while x != nil do
	     	y := x
	     	if key < x.data
	       		then x = x.left
	       		else x = x.right
	 z.parent = y
	 if key < y.data
	     then y.left := z
	     else y.right := z
	     //end BST-insert
	 */
	// run fixup
	return this;
}


// fixup the tree after insertion
void RBTree::InsertFixup(RBNode *x){
	/*RB-INSERT-FIXUP(x)
	1 while (x.p.color == RED) {
	2 	if x.p === x.p.p.left
	3 		uncle = x.p.p.right
	4		if y.color == RED		// if y-uncle is RED
	5			x.p.color = BLACK	//case 1
	6			y.color = BLACK		//case 1
	7			x.p.p.color = RED	//case 1
	8			x = x.p.p			//case 1
	9		else if x == x.p.right	// UNCLE IS BLACK
	10			x = x.p				//case 2
	11			LEFT-ROTATE(x)		//case 2
	12		x.p.color = BLACK	//case 3
	13		x.p.p.color = RED	//case 3
	14  	RIGHT-ROTATE(x.p.p)	//case 3
	15	else //x.p === x.p.p.right  (same as then clause with “right” & "left" exchanged)
	3 		y = x.p.p.left
	4		if y.color == RED
	5			x.p.color = BLACK	//case 1
	6			y.color = BLACK		//case 1
	7			x.p.p.color = RED	//case 1
	8			x = x.p.p			//case 1
	9		else if x == x.p.left
	10			x = x.p				//case 2
	11			RIGHT-ROTATE(x)	//case 2
	12		x.p.color = BLACK	//case 3
	13		x.p.p.color = RED	//case 3
	14  	LEFT-ROTATE(x.p.p)	//case 3
	16	}//end while()*/

}

// left rotation of a parent-child backbone
void RBTree::LeftRotate(RBNode *x){
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
	12 x.p = y
*/
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
}

// right rotation of a parent-child backbone
void RBTree::RightRotate(RBNode *x){
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
}

// read a complete RBTree from an input file
RBTree* RBTree::RBRead(){
// should this do the file input or just be handed a FILE pointer?
	//read root then read left and right?
	return NULL;
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

// write out the current red-black tree to the screen, where the tree is stored in a pre-order format
void RBTree::RBWrite(){
/*	if(_root == NULL)
	{cout << "nil";}
	//print root
	cout << _root->ToString();
	//recursively print left
	RBWrite(_root->_lchild);
	//recursively print right
	RBWrite(_root->_rchild);*/
}

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

Tree-Search(root, key)
 if root == nil or root.data == key then
    return root
 if key < root.data
    then return Tree-Search(root.left, key)
    else return Tree-Search(root.right, key)

Iterative-Tree-Search(root, key)
 while root != nil and root.data != key do
    if key < root.data
    	then root = root.left
    	else root = root.right
 return root

Tree-Minimum(root)
 while root != nil and root.left != nil do
       root = root.left
 return root

Tree-Maximum(root)
 while root != nil and root.right != nil do
       root = root.right
 return root

Successor(x)
 if x.right != nil then
    return Tree-Minimum(x.right)      //e.g., 15 --> 17
 y := x.parent			    // e.g., node 13
 while y != nil and x = y.right do  // find a "right" parent
     x := y
     y := y.parent
 return y

*/
