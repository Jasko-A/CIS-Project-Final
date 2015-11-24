#include "..\HeaderFiles\BinaryTree.h"

Stack<Food> BinaryTree::inOrderStack()
{
	return _inOrderStack(rootPtr);
}

void BinaryTree::destroyTree(BinaryNode* nodePtr)
{
	if (nodePtr != 0)
	{
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		delete nodePtr;
	}
}

void BinaryTree::_printIndentedTree(BinaryNode * nodePtr, int level)
{
	if (nodePtr != 0)//Recursion Terminator Statement
	{
		_printIndentedTree(nodePtr->getRightPtr(), level + 1); 
		cout << setw(level * 7) << level << ". " << nodePtr->getItem().getKey() << " " << nodePtr->getItem().getName() << endl;
		_printIndentedTree(nodePtr->getLeftPtr(), level + 1); 
	}
}

Stack<Food> BinaryTree::_inOrderStack(BinaryNode * nodePtr)
{
	Stack<Food> inOrderStack;
	if (nodePtr != 0)
	{
		_inOrderStack(nodePtr->getRightPtr());
		inOrderStack.push(&nodePtr->getItem());
		_inOrderStack(nodePtr->getLeftPtr());
	}
	return inOrderStack;
}
