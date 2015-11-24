#include "..\HeaderFiles\BinaryTree.h"

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
