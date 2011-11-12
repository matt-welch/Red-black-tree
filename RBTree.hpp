/* Red Black Tree
 * This source code file comprises the implementation of a RedBlack Binary tree.
 *
 * RedBlack Tree Operations:
 * 		RB-Fixup
 * 		rotate
 * 		colorSwap
 *		RBWrite (write out the current red-black tree to the screen, where the tree is stored in a pre-order format)
 * 		RBread (read in a red-black tree from a file named RBinput.txt, where the tree is stored in a pre-order format)
 *		RBinsert (insert a new node with the data field given as a parameter of the function and perform the fix-up if necessary)
 *		RBdelete (delete the node whose data field matches the data given as a parameter of the function, and perform the fix-up if necessary)
 *				Maintain a linked list to hold deleted nodes (reuse memory)
 */

#ifndef __RBTREE_H__
#define __RBTREE_H__
#include "RBNode.hpp"
#include "DLList.hpp"

// RedBlack Tree class declaration
class RBTree {
public:
	RBTree();
	~RBTree();
	RBNode* GetRoot();
	int		GetSize(){return _size;}
	bool	IsValid();
	void 	BSTInsert(int key, Color color);
	int		RBCreateFromList(int list[], Color colors[], int numNodes);
	RBNode* RBDelete(int key);
	RBTree* RBInsert(int key);
	int		RBInsertFromList(int list[], Color colors[], int numNodes);
	RBTree* RBRead();
	RBNode* RBSearch(RBNode *traverse, int key);
	RBNode* RBSuccessor(RBNode *x);
	RBNode*	TreeMin(RBNode *x);
	RBNode*	TreeMax(RBNode *x);
	void 	RBWrite(RBNode *myRoot);
protected:
	RBNode 	*_root;
	RBNode 	*_nil;
	void 	DeleteFixup(RBNode *x);
	void 	DeleteFixupLeft(RBNode *x);
	void	DeleteFixupRight(RBNode *x);
	void 	DeleteFixupSmall(RBNode*);
	void 	InsertFixup(RBNode *x);
	void 	LeftRotate(RBNode *x);
	void 	RightRotate(RBNode *x);
	int		RBAttachLeft(int key, RBNode *parent, Color newColor, int index);
	int		RBAttachRight(int key, RBNode *parent, Color newColor, int index);
	RBNode*	RBTransplant(RBNode *u, RBNode *v);
	int		_size;
	DLList* _store;
	bool	_valid;
};

#endif /* __RBTREE_H__ */
