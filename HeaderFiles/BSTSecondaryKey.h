// BSTSecondaryKey.h header file to manage the BST sorted by secondary key.
// Brandon Archbold

#ifndef _BST_SECONDARY_TREE
#define _BST_SECONDARY_TREE

#include "BinaryTreeSecondaryKey.h"

class BSTSecondaryTree : public BinaryTreeSecondaryKey
{

public:
	// insert a node at the correct location
	bool insert(Food * newEntry);
	// remove a node if found
	bool remove(string name);
	// find a target node
	Food* search(string name) const;

private:
	BinaryNode* _insert(BinaryNode* nodePtr, BinaryNode* newNodePtr);
	BinaryNode* _remove(BinaryNode* nodePtr, Food *& target, bool & success);
	BinaryNode* _search(BinaryNode* nodePtr, const Food & target) const;
	BinaryNode* deleteNode(BinaryNode* nodePtr);
	BinaryNode* removeLeftmostNode(BinaryNode* nodePtr, Food & successor);
};


#endif