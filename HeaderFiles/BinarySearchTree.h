// BinarySearchTree.h header file to manage the BST.
// Brandon Archbold

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

class BinarySearchTree : public BinaryTree
{
private:
	BinaryNode* insert(BinaryNode* rootPtr, BinaryNode* newNode);
	BinaryNode* remove(BinaryNode* rootPtr, const Food target);
	BinaryNode* searchTree(BinaryNode* rootPtr, const Food & target) const;
protected:

public:

};


#endif