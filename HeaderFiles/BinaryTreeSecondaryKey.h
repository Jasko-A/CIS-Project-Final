// BinaryTreeScondaryKey.h header file to manage the binary tree sorted by name.
// Brandon Archbold

#ifndef _BINARY_TREE_SECONDARY_TREE
#define _BINARY_TREE_SECONDARY_TREE

#include "BinaryNode.h"
#include <iomanip>
#include "Stack.h"

class BinaryTreeSecondaryKey
{
protected:
	BinaryNode* rootPtr;
	int count;
	
public:

	BinaryTreeSecondaryKey() { rootPtr = 0; count = 0; }
	virtual ~BinaryTreeSecondaryKey() { clear(); }
	

	bool isEmpty() const { return count == 0; }
	int size() const { return count; }
	bool clear() { destroyTree(rootPtr); rootPtr = 0; count = 0; return true; }
	void printIndentedTree() { _printIndentedTree(rootPtr, 0); }
	Stack<Food*> inOrderStack();


	// abstract functions
	virtual bool insert(Food * newItem) = 0;
	virtual bool remove(string name) = 0;
	virtual Food* search(string name) const = 0;

private:
	void destroyTree(BinaryNode* nodePtr);
	void _printIndentedTree(BinaryNode* nodePtr, int level);
	Stack<Food*> _inOrderStack(BinaryNode * nodePtr, Stack<Food*> inOrderStack);

};


#endif