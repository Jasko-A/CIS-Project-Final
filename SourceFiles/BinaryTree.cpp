#include "../HeaderFiles/BinaryTree.h"

/** =================================== */
/* DestroyTree function to destroy all nodes in the tree.
Recieves the root of the tree.
No return values. */
void BinaryTree::destroyTree(BinaryNode* nodePtr)
{
	if (nodePtr != 0)
	{
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		delete nodePtr;
	}
}

/** =================================== */
/* Prints the indented tree by level.
Takes in the root of the tree and the current level.
No return values. Outputs the tree to the screen in an indented list. */
void BinaryTree::_printIndentedTree(BinaryNode * nodePtr, int level)
{
	if (nodePtr != 0)//Recursion Terminator Statement
	{
		_printIndentedTree(nodePtr->getRightPtr(), level + 1);
		cout << setw(level * 7) << level << ". " << nodePtr->getItem()->getKey() << " " << nodePtr->getItem()->getName() << endl;
		_printIndentedTree(nodePtr->getLeftPtr(), level + 1);
	}
}

/** =================================== */
/* Public member function to place all items in the tree into a Stack inOrder.
No input paramerters.
Returns the Stack of Food pointers from the inOrder traversal. */
void BinaryTree::inOrderPrint()
{
	_inOrderPrint(rootPtr);
}

/** =================================== */
/* Private member function called by inOrderStack to make an inOrder Stack.
Recieves the root of the tree as well as the Stack.
Returns the stack of Food pointers. */
void BinaryTree::_inOrderPrint(BinaryNode * nodePtr)
{
	if (nodePtr != 0)
	{
		_inOrderPrint(nodePtr->getLeftPtr());
		cout << "\nKey: " << nodePtr->getItem()->getKey();
		_inOrderPrint(nodePtr->getRightPtr());
	}
}