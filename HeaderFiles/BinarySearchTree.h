// BinarySearchTree.h header file to manage the BST.
// Brandon Archbold

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

class BinarySearchTree : public BinaryTree
{

public:
	// insert a node at the correct location
	bool insert(const Food * newEntry);
	// remove a node if found
	bool remove(const Food *& anEntry);
	// find a target node
	bool search(const Food *& target, Food *& returnedItem) const;

private:
	BinaryNode* _insert(BinaryNode* nodePtr, BinaryNode* newNodePtr);
	BinaryNode* _remove(BinaryNode* nodePtr, const Food *& target, bool & success);
	BinaryNode* _search(BinaryNode* nodePtr, const Food & target) const;
	BinaryNode* deleteNode(BinaryNode* nodePtr);
	BinaryNode* removeLeftmostNode(BinaryNode* nodePtr, Food & successor);
};


#endif