#include "../HeaderFiles/HashTable.h"

int HashTable::_hash(int id) const
{
    return id % arraySize;
}

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
  delete[] arr;
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
  int hash = _hash(id);
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

int HashTable::getNumberLL()
{
    int num = 0;
    for(int i = 0; i < arraySize; i++){
        if(arr[i].getCount() > 1)
            num++;
    }
    return num;
}

int HashTable::getLongestLL()
{
    int k = 0;
    for(int i = 0; i < arraySize; i++)
    {
        if(arr[i].getCount() > k)
            k = arr[i].getCount();
    }
    if(k)
        return k - 1;
    else
        return 0;
}

int HashTable::getAverageLL()
{
    int num = 0;
    for(int i = 0; i < arraySize; i++)
    {
        if(arr[i].getCount() > 1)
            num += arr[i].getCount() - 1;
    }
    return num/getNumberLL();
}
