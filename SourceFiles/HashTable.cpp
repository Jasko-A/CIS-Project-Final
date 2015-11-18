#include "../HeaderFiles/HashTable.h"

HashTable::HashTable(int & setSize)
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
  int hash = newEntry->getKey();
  hash = hash % arraySize;
  if(arr[hash].getCount() > 0)
    collisions++;
  arr[hash].addItem(newEntry);
}

bool HashTable::remove(Food * deletePtr)
{
  int id = deletePtr->getKey();
  int hash = id % arraySize;
  if(arr[hash].deleteItem(id)
    return true;
  return false;
}

bool HashTable::search(int & id, Food *& returnedPtr)
{
  int hash = id;
  hash = hash % arraySize;
  if(arr[hash].search(id, returnedPtr))
    return true;
  return false;
}
