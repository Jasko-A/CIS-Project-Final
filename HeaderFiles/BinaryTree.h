// BinaryTree.h header file to manage the binary tree.
// Brandon Archbold

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "Food.h"

class BinaryTree
{
private:
	
protected:
	struct BinaryNode
	{
		Food item;
		BinaryNode* leftPtr;
		BinaryNode* rightPtr;
	};

	BinaryNode* rootPtr;
	int count;
public:

	BinaryTree() { rootPtr = 0; count = 0; }
	virtual ~BinaryTree() { }
	BinaryTree & operator = (const BinaryTree & sourceTree);

	bool isEmpty() const { return count == 0; }
	int size() const { return count; }
	void preOrder();
	void inOrder();
	void postOrder();
	void printIndentedTree();
	

	// abstract functions
	virtual bool insert(const Food & newItem) = 0;
	virtual bool remove(const Food & newItem) = 0;
	virtual Food search(const Food & newItem) const = 0;


};


#endif