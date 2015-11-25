#include "../HeaderFiles/BSTSecondaryKey.h"

/** =================================== */
/* This is the public function which calls _insert to insert a new value in the BST.
insert takes a pointer to a Food obeject to be inserted into the tree.
The function inserts the item into the tree and then returns true to signify completion. */
bool BSTSecondaryTree::insert(Food * newNode)
{
	BinaryNode* newFood = new BinaryNode(newNode);
	rootPtr = _insert(rootPtr, newFood);
	count++;
	return true;
}

/** =================================== */
/* This is the privite member function called by insert to access
private member data recursively and insert a new node into the BST.
Accepts nodePtr which is the root of the current tree. Accepts newNodePtr which is a pointer to the newNode to be inserted.
The function returns the item that was inserted. If the item was not inserted successfully null is returned. */
BinaryNode* BSTSecondaryTree::_insert(BinaryNode* nodePtr, BinaryNode* newNodePtr)
{
	if (nodePtr == 0)
	{
		nodePtr = newNodePtr;
	}
	else if (newNodePtr->getItem()->getName() < nodePtr->getItem()->getName())
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

/** =================================== */
/* Public remove function to remove a node from the BST by calling _remove.
Accepts the name of the item to be removed.
If the name is found the item is removed and true is returned. If not false is returned. */
bool BSTSecondaryTree::remove(string name)
{
	Food temp;
	temp.setName(name);
	Food * target = &temp;
	bool isSuccessful = false;
	rootPtr = _remove(rootPtr, target, isSuccessful);
	return isSuccessful;
}

/** =================================== */
/* Private member function to remove a node from the BST called by remove.
Accepts a pointer to the root of the tree, the target that should be removed and a success flag to determine if the value is null or not.
This function returns the root of the tree when finished. */
BinaryNode* BSTSecondaryTree::_remove(BinaryNode* nodePtr, Food *& target, bool & success)
{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
	if (nodePtr->getItem()->getName() > target->getName())
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem()->getName() < target->getName())
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
		count--;
	}
	return nodePtr;
}

/** =================================== */
/* This function deletes a node from a tree as long as the node is a leaf.
This function recieves a node that is to be deleted.
This function returns the root of the tree with the deleted node / nodes. */
BinaryNode* BSTSecondaryTree::deleteNode(BinaryNode* nodePtr)
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
		nodePtr->setItem(&newNodeValue);
		return nodePtr;
	}
}

/** =================================== */
/* To remove the left most node in the BST.
Recieves the root of the tree as well as
<explanation of all output actions and return value > */
BinaryNode* BSTSecondaryTree::removeLeftmostNode(BinaryNode* nodePtr, Food & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = *nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}
}

/** == == == == == == == == == == == == == == == == == = */
/* Public search function to find an item in the BST by calling _search.
Accepts a int key for the item to be searched in the BST.
This function returns a pointer to the Food object if found, else null is returned. */
Food* BSTSecondaryTree::search(string name) const
{
	Food temp;
	temp.setName(name);
	Food * target = &temp;
	BinaryNode* newNodePtr = _search(rootPtr, *target);
	if (newNodePtr)
	{
		return newNodePtr->getItem();
	}
	else
		return nullptr;
}

/** =================================== */
/* Private member function called by search in order to find a specific node.
Accepts the root of the BST as well as the target that is being searched for.
Returns the Node of the item that is found. If not found null is returned. */
BinaryNode* BSTSecondaryTree::_search(BinaryNode* nodePtr, const Food & target) const
{
	if (!nodePtr)
		return nullptr;
	else if (target.getName() == nodePtr->getItem()->getName())
		return nodePtr;
	else if (target.getName() < nodePtr->getItem()->getName())
	{
		if (nodePtr->getLeftPtr() == nullptr)
			return nullptr;
		else
			return _search(nodePtr->getLeftPtr(), target);
	}
	else if (target.getName() > nodePtr->getItem()->getName())
	{
		if (nodePtr->getRightPtr())
			return _search(nodePtr->getRightPtr(), target);
		else
			return nullptr;

	}
	return nodePtr;
}