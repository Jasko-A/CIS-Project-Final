// BinaryTree.h header file to manage the binary tree.
// Brandon Archbold

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include <iomanip>
#include "Stack.h"

class BinaryTree
{
protected:
	BinaryNode* rootPtr;
	int count;
	bool sortedKey;
	
public:

	BinaryTree() { rootPtr = 0; count = 0; }		// If true it is sorted by key, if false it is sorted by name.
	virtual ~BinaryTree() { }
	

	bool isEmpty() const { return count == 0; }
	int size() const { return count; }
	bool clear() { destroyTree(rootPtr); rootPtr = 0; count = 0; return true; }
	void printIndentedTree() { _printIndentedTree(rootPtr, 0); }
	void inOrderPrint();
	void inOrderArr(Food arr[]);


	// abstract functions
	virtual bool insert(Food * newItem) = 0;
	virtual bool remove(int key) = 0;
	virtual Food* search(int key) const = 0;

private:
	void destroyTree(BinaryNode* nodePtr);
	void _printIndentedTree(BinaryNode* nodePtr, int level);
	void _inOrderPrint(BinaryNode * nodePtr);
	void _inOrderArr(BinaryNode * nodePtr, Food arr[], int *i);

};


#endif