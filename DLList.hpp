/*******************************************************************************
 * FILENAME:	DLList.hpp
 * DESCRIPTION:	Doubly-Linked List Class Definition
 * AUTHOR: 		James Matthew Welch [JMW]
 * SCHOOL:		Arizona State University
 * CLASS:		CSE310::Data Structures and Algorithms
 * INSTRUCTOR:	Dr. Guoliang Xue
 * SECTION:		71409
 * TERM:		Fall 2011
 ******************************************************************************/

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
