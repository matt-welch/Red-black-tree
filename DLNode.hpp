/*******************************************************************************
 * FILENAME:	DLNode.hpp
 * DESCRIPTION:	Doubly-Linked List Node Class Definition
 * AUTHOR: 		James Matthew Welch [JMW]
 * SCHOOL:		Arizona State University
 * CLASS:		CSE310::Data Structures and Algorithms
 * INSTRUCTOR:	Dr. Guoliang Xue
 * SECTION:		71409
 * TERM:		Fall 2011
 ******************************************************************************/

#ifndef __DLNODE_H__
#define __DLNODE_H__
#include "RBNode.hpp"

// Doubly Linked List node declaration
class DLNode {
public:
	DLNode();
	~DLNode();
	DLNode(RBNode* node);
	RBNode *_data;
	DLNode *_next;
	DLNode *_prev;
};

#endif /* __DLNODE_H__ */
