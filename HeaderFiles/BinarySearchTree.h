// BinarySearchTree.h header file to manage the BST.
// Brandon Archbold

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

class BinarySearchTree : public BinaryTree
{

public:
	// insert a node at the correct location
	bool insert(Food * newEntry);
	// remove a node if found
	bool remove(int key);
	// find a target node
	Food* search(int key) const;

private:
	BinaryNode* _insert(BinaryNode* nodePtr, BinaryNode* newNodePtr);
	BinaryNode* _remove(BinaryNode* nodePtr, Food *& target, bool & success);
	BinaryNode* _search(BinaryNode* nodePtr, const Food & target) const;
	BinaryNode* deleteNode(BinaryNode* nodePtr);
	BinaryNode* removeLeftmostNode(BinaryNode* nodePtr, Food & successor);
};


#endif