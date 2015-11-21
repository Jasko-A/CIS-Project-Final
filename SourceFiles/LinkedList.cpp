/**
LinkedList source
Written by: Austin Bohannon
**/

#include "../HeaderFiles/LinkedList.h"

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

void LinkedList::addItem(Food * newFood)
{
  node * newNode = new node;
  newNode->data = newFood;

  node * temp = head;
  while(temp->next != tail && newFood->getKey() > temp->data->getKey())
    temp = temp->next;
  temp->next->back = newNode;
  newNode->next = temp->next;
  temp->next = newNode;
  newNode->back = temp;
  count++;
}

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

bool LinkedList::itemExists(int &id)
{
  node * temp = head;
  while(temp->next != tail && temp->data->getKey() > id)
    temp = temp->next;
  if(temp->data->getKey() == id)
    return true;
  return false;
}

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
