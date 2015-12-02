// Node for a binary tree header file
// Brandon Archbold

 
#ifndef _BINARY_NODE
#define _BINARY_NODE

#include "Food.h"

class BinaryNode
{   
private:
	Food*          item;         // Data portion
	BinaryNode* leftPtr;		// Pointer to left child
	BinaryNode* rightPtr;		// Pointer to right child

public:
	// constructors
	BinaryNode(Food * anItem)	{item = anItem; leftPtr = 0; rightPtr = 0;}
	BinaryNode(Food * anItem, BinaryNode* left, BinaryNode* right) {item = anItem; leftPtr = left; rightPtr = right;}
	BinaryNode() { leftPtr = 0; rightPtr = 0; }
	// accessors
	void setItem(Food * anItem) {item = anItem;}
	void setLeftPtr(BinaryNode* left) {leftPtr = left;}
    void setRightPtr(BinaryNode* right) {rightPtr = right;}
	// mutators
	Food* getItem() const	 {return item;}
	BinaryNode* getLeftPtr() const  {return leftPtr;}
	BinaryNode* getRightPtr() const {return rightPtr;}

	bool isLeaf() const {return (leftPtr == 0 && rightPtr == 0);}
}; 

#endif 
