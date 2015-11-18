#include "../HeaderFiles/HashTable.h"

HashTable::HashTable(int setSize)
{
  arraySize = setSize;
  filledSlots = 0;
  collisions = 0;
  count = 0;
  arr = new LinkedList [arraySize];
}

HashTable::~HashTable()
{
  delete arr;
}

void HashTable::addEntry(Food * newEntry)
{
  int hash = newEntry->getKey() % arraySize;
  if(arr[hash].getCount() > 0)
    collisions++;
  else
    filledSlots++;
  arr[hash].addItem(newEntry);
  count++;
}

bool HashTable::remove(Food * deletePtr)
{
  int id = deletePtr->getKey();
  int hash = id % arraySize;
  if(arr[hash].deleteItem(id))
  {
    if(arr[hash].getCount() > 0)
      collisions--;
    else
      filledSlots--;
    count--;
    return true;
  }
  return false;
}

bool HashTable::search(int id, Food *& returnedPtr)
{
  int hash = id % arraySize;
  if(arr[hash].search(id, returnedPtr))
    return true;
  return false;
}
