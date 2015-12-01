// BinarySearchTree.h header file to manage the BST.
// Brandon Archbold

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

class BinarySearchTree : public BinaryTree
{

public:
	BinarySearchTree(bool sortedByKey) { rootPtr = 0; count = 0; sortedKey = sortedByKey; }		// If true it is sorted by key, if false it is sorted by name.

	// insert a node at the correct location
	bool insert(Food * newEntry);			//BST sorted by ID
	// remove a node if found
	bool remove(int key);					//remove by key
	bool remove(string name);				//remove by Name
	// find a target node
	Food* search(int key) const;			//Search by key
	Food* search(string name) const;		//Search by name

private:
	BinaryNode* _insert(BinaryNode* nodePtr, BinaryNode* newNodePtr);
	BinaryNode* _insertName(BinaryNode* nodePtr, BinaryNode* newNodePtr);
	BinaryNode* _remove(BinaryNode* nodePtr, Food *& target, bool & success);
	BinaryNode* _removeName(BinaryNode* nodePtr, Food *& target, bool & success);
	BinaryNode* _search(BinaryNode* nodePtr, const Food & target) const;
	BinaryNode* _searchName(BinaryNode* nodePtr, const Food & target) const;
	BinaryNode* deleteNode(BinaryNode* nodePtr);
	BinaryNode* removeLeftmostNode(BinaryNode* nodePtr, Food & successor);
};


#endif