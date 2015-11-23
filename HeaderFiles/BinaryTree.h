// BinaryTree.h header file to manage the binary tree.
// Brandon Archbold

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"

class BinaryTree
{
protected:
	BinaryNode* rootPtr;
	int count;
	
public:

	BinaryTree() { rootPtr = 0; count = 0; }
	virtual ~BinaryTree() { }
	

	bool isEmpty() const { return count == 0; }
	int size() const { return count; }
	bool clear();
	void printIndentedTree();
	void inOrder();


	// abstract functions
	virtual bool insert(const Food & newItem) = 0;
	virtual bool remove(const Food & item) = 0;
	virtual Food search(const Food & item) const = 0;

private:
	void _inOrder();
	void _printIndentedTree();
	void destroyTree();

};


#endif