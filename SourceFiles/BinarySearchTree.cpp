#include "..\HeaderFiles\BinarySearchTree.h"

bool BinarySearchTree::insert(const Food *& newNode)
{
	BinaryNode* newFood = new BinaryNode(*newNode);
	rootPtr = _insert(rootPtr, newFood);
	count++;
	return true;
}

BinaryNode* BinarySearchTree::_insert(BinaryNode* nodePtr, BinaryNode* newNodePtr)
{
	if (nodePtr == 0)
	{
		nodePtr = newNodePtr;
	}
	else if (newNodePtr->getItem() < nodePtr->getItem())
	{
		if (nodePtr->getLeftPtr())
			_insert(nodePtr->getLeftPtr(), newNodePtr);
		else
			nodePtr->setLeftPtr(newNodePtr);
	}
	else
	{
		if (nodePtr->getRightPtr())
			_insert(nodePtr->getRightPtr(), newNodePtr);
		else
			nodePtr->setRightPtr(newNodePtr);
	}
	return nodePtr;
}

bool BinarySearchTree::remove(const Food *& target)
{
	bool isSuccessful = false;
	rootPtr = _remove(rootPtr, target, isSuccessful);
	return isSuccessful;
}

BinaryNode* BinarySearchTree::_remove(BinaryNode* nodePtr, const Food *& target, bool & success)
{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
	if (nodePtr->getItem() > *target)
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem() < *target)
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
		count--;
	}
	return nodePtr;
}

BinaryNode* BinarySearchTree::deleteNode(BinaryNode* nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)
	{
		BinaryNode* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0)
	{
		BinaryNode* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else
	{
		Food newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}
}

BinaryNode* BinarySearchTree::removeLeftmostNode(BinaryNode* nodePtr, Food & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}
}

bool BinarySearchTree::search(const Food *& target, Food *& returnedItem) const
{
	BinaryNode* newNodePtr = _search(rootPtr, *target);
	if (newNodePtr)
	{
		returnedItem = &newNodePtr->getItem();
		return true;
	}
	else
		return false;
}

BinaryNode* BinarySearchTree::_search(BinaryNode* nodePtr, const Food & target) const
{
	if (!nodePtr)
		return nullptr;
	else if (target == nodePtr->getItem())
		return nodePtr;
	else if (target < nodePtr->getItem())
	{
		if (nodePtr->getLeftPtr() == nullptr)
			return nullptr;
		else
			return _search(nodePtr->getLeftPtr(), target);
	}
	else if (target > nodePtr->getItem())
	{
		if (nodePtr->getRightPtr())
			return _search(nodePtr->getRightPtr(), target);
		else
			return nullptr;

	}
	return nodePtr;
}