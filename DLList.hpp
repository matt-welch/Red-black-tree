/*
 * DLList.h
 *
 *  Created on: Oct 26, 2011
 *      Author: mwelch
 */

#ifndef __DLLIST_H__
#define __DLLIST_H__
#include "DLNode.hpp"

// Doubly Linked List to hold "deleted" values
class DLList {
public:
	DLList();
	~DLList();
	bool 	IsEmpty();
	void 	Add(RBNode *deletedNode);
	DLNode* Remove();
protected:
	DLNode 	*_head;
	DLNode 	*_tail;
	int 	_size;
};

#endif /* __DLLIST_H__ */
