/**
LinkedList source
Written by: Austin Bohannon

Made to work with pointers to Food objects so that no data has to be copied,
it's just organized.
**/

#include "../HeaderFiles/LinkedList.h"

/***** LinkedList::LinkedList *****
In:
Out:

The constructor sets count to zero,
constructs sentinel nodes with a
blank Food, and sets up the
doubly-linked list.
**********************************/
LinkedList::LinkedList()
{
  count = 0;

  Food *nullFood = new Food(0, "", 0.0, 0, 0.0, 0.0, 0.0, 0.0);

  head = new node;
  tail = new node;

  head->data = nullFood;
  head->next = tail;
  head->back = tail;

  tail->data = nullFood;
  tail->next = head;
  tail->back = head;
}

/***** LinkedList::~LinkedList *****
In:
Out:

The destructor deletes all of the
nodes in the linked list.
***********************************/
LinkedList::~LinkedList()
{
  node * temp = head, * tempNext;
  while (temp != tail)
  {
    tempNext = temp->next;
    delete temp;
    temp = tempNext;
  }
  delete tail;
}

/***** LinkedList::addItem *****
In: Food *
Out:

addItem constructs a new node
with the Food * as data. It
then inserts it intor the linked
list in ascending order.
*******************************/
void LinkedList::addItem(Food * newFood)
{
  node * newNode = new node;
  newNode->data = newFood;

  node * temp = head;
  while(temp->next != tail && newFood->getKey() > temp->next->data->getKey())
    temp = temp->next;
  temp->next->back = newNode;
  newNode->next = temp->next;
  temp->next = newNode;
  newNode->back = temp;
  count++;
}

/***** LinkedList::deleteItem *****
In: int
Out: bool (returned)

deleteItem takes an id, tries to
find it, and deletes it if it does,
returning true, or returning false
if it cannot find it.
**********************************/
bool LinkedList::deleteItem(int &id)
{
  node * temp = head;
  while(temp->next != tail && temp->data->getKey() < id)
    temp = temp->next;
  if(temp->data->getKey() == id)
  {
    temp->back->next = temp->next;
    temp->next->back = temp->back;
    delete temp;
    count--;
    return true;
  }
  return false;
}

/***** LinkedList::itemExists *****
In: int
Out: bool (returned)

itemExists takes a key and tries
to find it in the linked list. It
returns true if it finds it,
otherwise it returns false.
**********************************/
bool LinkedList::itemExists(int &id)
{
  node * temp = head;
  while(temp->next != tail && temp->data->getKey() > id)
    temp = temp->next;
  if(temp->data->getKey() == id)
    return true;
  return false;
}

/***** LinkedList::search *****
In: int, Food *&
Out: Food *&, bool (returned)

search takes a key, and tries
to find it in the linked list.
If it is there, it sets the
Food *& to the found Food's
pointer and returns true.
Otherwise it returns false.
******************************/
bool LinkedList::search(int &id, Food *& returnedItem)
{
  node * temp = head->next;
  while(temp != tail && temp->data->getKey() < id)
    temp = temp->next;
  if(temp->data->getKey() == id)
  {
    returnedItem = temp->data;
    return true;
  }
  return false;
}

/***** LinkedList::visitAll *****
In: void visit(Food *)
Out:

visitAll calls visit() on every
Food in the linked list.
********************************/
void LinkedList::visitAll(void visit(Food *))
{
    node * temp = head->next;
    while(temp != tail)
    {
        visit(temp->data);
        temp = temp->next;
    }
}
