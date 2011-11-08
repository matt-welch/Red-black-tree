/*
 * DLNode.h
 *
 *  Created on: Oct 26, 2011
 *      Author: mwelch
 */

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
