// BinaryTree.cpp implementation file to manage the BT.
// Brandon Archbold

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
No return value. */
void BinaryTree::inOrderPrint()
{
	_inOrderPrint(rootPtr);
}

/** =================================== */
/* Private member function called by inOrderStack to make an inOrder Stack.
Recieves the root of the tree.
No return value. Output's an inOrder of the BT. */
void BinaryTree::_inOrderPrint(BinaryNode * nodePtr)
{
	if (sortedKey)
	{
		if (nodePtr != 0)
		{
			_inOrderPrint(nodePtr->getLeftPtr());
			cout << "\nKey: " << nodePtr->getItem()->getKey() << " Name: " << nodePtr->getItem()->getName();
			_inOrderPrint(nodePtr->getRightPtr());
		}
	}
	else
	{
		if (nodePtr != 0)
		{
			_inOrderPrint(nodePtr->getLeftPtr());
			cout << "\nKey: " << nodePtr->getItem()->getKey() << " Name: " << nodePtr->getItem()->getName();
			_inOrderPrint(nodePtr->getRightPtr());
		}
	}
}

/** =================================== */
/* Fills an array with Food objects inorder
Accepts the Food array to be filled.
No return value. */
void BinaryTree::inOrderArr(Food arr[])
{
	int *i = new int;
	*i = 0;
	_inOrderArr(rootPtr, arr, i);
}



/** =================================== */
/* Fills an array with Food objects inorder.
Accepts the root of the tree, the array, and the value of the array to be filled.
No return value. */
void BinaryTree::_inOrderArr(BinaryNode * nodePtr, Food arr[], int * i)
{
	if (nodePtr != 0)
	{
		_inOrderArr(nodePtr->getLeftPtr(), arr, i);
		arr[*i] = *nodePtr->getItem();
		(*i)++;
		_inOrderArr(nodePtr->getRightPtr(), arr, i);
	}
}