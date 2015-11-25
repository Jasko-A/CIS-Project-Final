#include "../HeaderFiles/BinaryTreeSecondaryKey.h"

/** =================================== */
/* DestroyTree function to destroy all nodes in the tree.
Recieves the root of the tree.
No return values. */
void BinaryTreeSecondaryKey::destroyTree(BinaryNode* nodePtr)
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
void BinaryTreeSecondaryKey::_printIndentedTree(BinaryNode * nodePtr, int level)
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
Stack<Food*> BinaryTreeSecondaryKey::inOrderStack()
{
	Stack<Food*> inOrderStack;
	return _inOrderStack(rootPtr, inOrderStack);
}

/** =================================== */
/* Private member function called by inOrderStack to make an inOrder Stack.
Recieves the root of the tree as well as the Stack.
Returns the stack of Food pointers. */
Stack<Food*> BinaryTreeSecondaryKey::_inOrderStack(BinaryNode * nodePtr, Stack<Food*> inOrderStack)
{
	if (nodePtr != 0)
	{
		_inOrderStack(nodePtr->getRightPtr(), inOrderStack);
		inOrderStack.push(nodePtr->getItem());						
		_inOrderStack(nodePtr->getLeftPtr(), inOrderStack);
	}
	return inOrderStack;
}
