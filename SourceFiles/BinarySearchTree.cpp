// BinarySearchTree.cpp implementation file to manage the BST.
// Brandon Archbold

#include "../HeaderFiles/BinarySearchTree.h"

/** =================================== */
/* This is the public function which calls _insert to insert a new value in the BST.
insert takes a pointer to a Food obeject to be inserted into the tree.
The function inserts the item into the tree and then returns true to signify completion. */
bool BinarySearchTree::insert(Food * newNode)
{
		BinaryNode* newFood = new BinaryNode(newNode);
		if (sortedKey)
			rootPtr = _insert(rootPtr, newFood);
		else
			rootPtr = _insertName(rootPtr, newFood);
		count++;
		return true;
}

/** =================================== */
/* This is the privite member function called by insert to access 
private member data recursively and insert a new node into the BST.
Accepts nodePtr which is the root of the current tree. Accepts newNodePtr which is a pointer to the newNode to be inserted.
The function returns the item that was inserted. If the item was not inserted successfully null is returned. */
BinaryNode* BinarySearchTree::_insert(BinaryNode* nodePtr, BinaryNode* newNodePtr)
{
	if (nodePtr == 0)
	{
		nodePtr = newNodePtr;
	}
	else if (newNodePtr->getItem()->getKey() < nodePtr->getItem()->getKey())
	{
		if (nodePtr->getLeftPtr())
			_insert(nodePtr->getLeftPtr(), newNodePtr);
		else
			if (newNodePtr->getItem()->getKey() != nodePtr->getItem()->getKey())
				nodePtr->setLeftPtr(newNodePtr);
			else
				cout << "Cannot insert duplicate key!\n";
	}
	else
	{
		if (nodePtr->getRightPtr())
			_insert(nodePtr->getRightPtr(), newNodePtr);
		else
			if (newNodePtr->getItem()->getKey() != nodePtr->getItem()->getKey())
				nodePtr->setRightPtr(newNodePtr);
			else
				cout << "Cannot insert duplicate key!\n";
	}
	return nodePtr;
}

/** =================================== */
/* Public remove function to remove a node from the BST by calling _remove.
Accepts the unique key of the item to be removed.
If the key is found the item is removed and true is returned. If not false is returned. */
bool BinarySearchTree::remove(int key)
{
	if (sortedKey)
	{
		Food temp;
		temp.setKey(key);
		Food * target = &temp;
		bool isSuccessful = false;
		rootPtr = _remove(rootPtr, target, isSuccessful);
		return isSuccessful;
	}
	else
	{
		cout << "ITEM NOT REMOVED! TREE SORTED BY NAME!\n";
		return false;
	}
}

/** =================================== */
/* Private member function to remove a node from the BST called by remove.
Accepts a pointer to the root of the tree, the target that should be removed and a success flag to determine if the value is null or not.
This function returns the root of the tree when finished. */
BinaryNode* BinarySearchTree::_remove(BinaryNode* nodePtr, Food * target, bool & success)
{
	if (nodePtr == 0)
	{
		success = false;
		return nullptr;
	}
	if (*nodePtr->getItem() > *target)
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (*nodePtr->getItem() < *target)
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else
	{
		if (nodePtr->getLeftPtr() == NULL && nodePtr->getRightPtr() == NULL) 
		{
			deleteNode(nodePtr);
			nodePtr = NULL;
		}
		else if (nodePtr->getRightPtr() == NULL) 
		{
			BinaryNode *temp = nodePtr->getLeftPtr();
			deleteNode(nodePtr);
			nodePtr = temp;
		}
		else if (nodePtr->getLeftPtr() == NULL) 
		{
			BinaryNode *temp = nodePtr->getRightPtr();
			deleteNode(nodePtr);
			nodePtr = temp;
		}
		else 
		{

			BinaryNode *temp = findLeftmostNode(nodePtr->getRightPtr());

			nodePtr->setItem(temp->getItem());

			nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), temp->getItem(), success));
		}
		success = true;
		count--;
	}
	return nodePtr;
}

/** =================================== */
/* This function deletes a node from a tree as long as the node is a leaf.
This function recieves a node that is to be deleted.
This function returns the root of the tree with the deleted node / nodes. */
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
		nodePtr->setItem(&newNodeValue);
		return nodePtr;
	}
}

/** =================================== */
/* To remove the left most node in the BST.
Recieves the root of the tree as well as 
<explanation of all output actions and return value > */
BinaryNode* BinarySearchTree::removeLeftmostNode(BinaryNode* nodePtr, Food & successor)
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

/** =================================== */
/* Public search function to find an item in the BST by calling _search.
Accepts a int key for the item to be searched in the BST.
This function returns a pointer to the Food object if found, else null is returned. */
Food* BinarySearchTree::search(int key) const
{
	if (sortedKey)
	{
		Food temp;
		temp.setKey(key);
		Food * target = &temp;
		BinaryNode* newNodePtr = _search(rootPtr, *target);
		if (newNodePtr)
		{
			return newNodePtr->getItem();
		}
		else
			return nullptr;
	}
	else
	{
		cout << "Cannot search this tree by key, it is sorted by name!\n";
		return nullptr;
	}
}

/** =================================== */
/* Private member function called by search in order to find a specific node.
Accepts the root of the BST as well as the target that is being searched for.
Returns the Node of the item that is found. If not found null is returned. */
BinaryNode* BinarySearchTree::_search(BinaryNode* nodePtr, const Food & target) const
{
	if (!nodePtr)
		return nullptr;
	else if (target == *nodePtr->getItem())
		return nodePtr;
	else if (target < *nodePtr->getItem())
	{
		if (nodePtr->getLeftPtr() == nullptr)
			return nullptr;
		else
			return _search(nodePtr->getLeftPtr(), target);
	}
	else if (target > *nodePtr->getItem())
	{
		if (nodePtr->getRightPtr())
			return _search(nodePtr->getRightPtr(), target);
		else
			return nullptr;

	}
	return nodePtr;
}


// Sorting the BST by NAME
/** =================================== */
/* This is the privite member function called by insert to access
private member data recursively and insert a new node into the BST.
Accepts nodePtr which is the root of the current tree. Accepts newNodePtr which is a pointer to the newNode to be inserted.
The function returns the item that was inserted. If the item was not inserted successfully null is returned. */
BinaryNode* BinarySearchTree::_insertName(BinaryNode* nodePtr, BinaryNode* newNodePtr)
{
	if (nodePtr == 0)
	{
		nodePtr = newNodePtr;
	}
	else if (newNodePtr->getItem()->getName() < nodePtr->getItem()->getName())
	{
		if (nodePtr->getLeftPtr())
			_insertName(nodePtr->getLeftPtr(), newNodePtr);
		else
			nodePtr->setLeftPtr(newNodePtr);
	}
	else
	{
		if (nodePtr->getRightPtr())
			_insertName(nodePtr->getRightPtr(), newNodePtr);
		else
			nodePtr->setRightPtr(newNodePtr);
	}
	return nodePtr;
}

/** =================================== */
/* Public remove function to remove a node from the BST by calling _remove.
Accepts the name of the item to be removed.
If the name is found the item is removed and true is returned. If not false is returned. */
bool BinarySearchTree::remove(string name)
{
	if (!sortedKey)
	{
		Food temp;
		temp.setName(name);
		Food * target = &temp;
		bool isSuccessful = false;
		rootPtr = _remove(rootPtr, target, isSuccessful);
		return isSuccessful;
	}
	else
	{
		cout << "ITEM NOT REMOVED! THIS TREE IS SORTED BY NAME, NOT KEY!\n";
		return false;
	}
}

/** =================================== */
/* Private member function to remove a node from the BST called by remove.
Accepts a pointer to the root of the tree, the target that should be removed and a success flag to determine if the value is null or not.
This function returns the root of the tree when finished. */
BinaryNode* BinarySearchTree::_removeName(BinaryNode* nodePtr, Food *& target, bool & success)
{
	if (nodePtr == 0)
	{
		success = false;
		return nullptr;
	}
	if (nodePtr->getItem()->getName() > target->getName())
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem()->getName() < target->getName())
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else
	{
		if (nodePtr->getLeftPtr() == NULL && nodePtr->getRightPtr() == NULL)
		{
			deleteNode(nodePtr);
			nodePtr = NULL;
		}
		else if (nodePtr->getRightPtr() == NULL)
		{
			BinaryNode *temp = nodePtr->getLeftPtr();
			deleteNode(nodePtr);
			nodePtr = temp;
		}
		else if (nodePtr->getLeftPtr() == NULL)
		{
			BinaryNode *temp = nodePtr->getRightPtr();
			deleteNode(nodePtr);
			nodePtr = temp;
		}
		else
		{

			BinaryNode *temp = findLeftmostNode(nodePtr->getRightPtr());

			nodePtr->setItem(temp->getItem());

			nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), temp->getItem(), success));
		}
		success = true;
		count--;
	}
	return nodePtr;
}

/** == == == == == == == == == == == == == == == == == = */
/* Public search function to find an item in the BST by calling _searchName.
Accepts a int key for the item to be searched in the BST.
This function returns a pointer to the Food object if found, else null is returned. */
Food* BinarySearchTree::search(string name) const
{
	if (!sortedKey)
	{
		Food temp;
		temp.setName(name);
		Food * target = &temp;
		BinaryNode* newNodePtr = _searchName(rootPtr, *target);
		if (newNodePtr)
		{
			return newNodePtr->getItem();
		}
		else
			return nullptr;
	}
	else
	{
		cout << "Cannot search this tree by name, it is sorted by key!\n";
		return nullptr;
	}
}

/** =================================== */
/* Private member function called by search in order to find a specific node.
Accepts the root of the BST as well as the target that is being searched for.
Returns the Node of the item that is found. If not found null is returned. */
BinaryNode* BinarySearchTree::_searchName(BinaryNode* nodePtr, const Food & target) const
{
	if (!nodePtr)
		return nullptr;
	else if (target.getName() == nodePtr->getItem()->getName().substr(0, target.getName().length()))
	{
		if (target.getName() == nodePtr->getRightPtr()->getItem()->getName().substr(0, target.getName().length()))
			_searchName(nodePtr->getRightPtr(), target);
		return nodePtr;
	}
	else if (target.getName() < nodePtr->getItem()->getName())
	{
		if (nodePtr->getLeftPtr() == nullptr)
			return nullptr;
		else
			return _searchName(nodePtr->getLeftPtr(), target);
	}
	else if (target.getName() >= nodePtr->getItem()->getName())
	{
		if (nodePtr->getRightPtr())
			return _searchName(nodePtr->getRightPtr(), target);
		else
			return nullptr;

	}
	return nodePtr;
}

/** =================================== */
/* Find the left most node in the tree
Recieves the root of the tree.
Returns a pointer to the left most node in the tree. */
BinaryNode* BinarySearchTree::findLeftmostNode(BinaryNode* nodePtr)
{
	while (nodePtr->getLeftPtr() != NULL) nodePtr = nodePtr->getLeftPtr();
	return nodePtr;
}