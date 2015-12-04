/**
HashTable class member functions
Written by: Austin Bohannon

Made to work with pointers to Food objects so that no data has to be copied,
it's just organized.
**/
#include "../HeaderFiles/HashTable.h"

/***** HashTable::_hash *****
In: int
Out: int (returned)

_hash is a function that
takes an int and returns the
hash of it, for use as an
index.
****************************/
int HashTable::_hash(int id) const
{
    return id % arraySize;
}

/***** HashTable::HashTable *****
In: int
Out:

The constructor takes an int that
is the size of the hash array to
be made. It sets default values
and constructs the array.
********************************/
HashTable::HashTable(int setSize)
{
  arraySize = setSize;
  filledSlots = 0;
  collisions = 0;
  count = 0;
  arr = new LinkedList [arraySize];
}

/***** HashTable::~HashTable *****
In:
Out:

The destructor returns the array
to the heap.
*********************************/
HashTable::~HashTable()
{
  delete[] arr;
}

/***** HashTable::addEntry *****
In: Food *
Out:

addEntry adds a food pointer to
the array. It hashes the key and
then adds it to the respective
LinkedList.
*******************************/
bool HashTable::addEntry(Food * newEntry)
{
  int hash = _hash(newEntry->getKey());
  if(!arr[hash].addItem(newEntry))
    return false;
  if(arr[hash].getCount() > 1)
    collisions++;
  else
    filledSlots++;
  count++;
  return true;
}

/***** HashTable::remove *****
In: Food *
Out: bool (returned)

remove takes a Food *, hashes
its id to find where it should
be, and attempts to remove it
from the LinkedList. It
returns whether it was
successful or not.
*****************************/
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

/***** HashTable::search *****
In: int, Food *&
Out: Food*&, bool (returned)

search takes a key as an int,
hashes it to find where it
should be, then calls the
search function of that
LinkedList. If it is successful,
the Food *& now contains a
pointer to it. It returns a bool
for success or not.
*****************************/
bool HashTable::search(int id, Food *& returnedPtr)
{
  int hash = _hash(id);
  if(arr[hash].search(id, returnedPtr))
    return true;
  return false;
}

void HashTable::rehash(int setSize)
{
  arraySize = setSize;
  filledSlots = 0;
  collisions = 0;
  count = 0;
  delete[] arr;
  arr = new LinkedList [arraySize];
}

/***** HashTable::getNumberLL *****
In:
Out: Int (returned)

getNumberLL counts the number of
LinkedLists that have more than one
Food * in them and returns that
value.
**********************************/
int HashTable::getNumberLL()
{
    int num = 0;
    for(int i = 0; i < arraySize; i++){
        if(arr[i].getCount() > 1)
            num++;
    }
    return num;
}

/***** HashTable::getLongestLL *****
In:
Out: int (returned)

getLongestLL finds the longest
LinkedList and returns that value.
***********************************/
int HashTable::getLongestLL()
{
    int k = 0;
    for(int i = 0; i < arraySize; i++)
    {
        if(arr[i].getCount() > k)
            k = arr[i].getCount();
    }
    if(k)
        return k--; //The first one doesn't count, and shouldn't -- if k == 0
    else
        return 0;
}

/***** HashTable::getAverageLL *****
In:
Out: Int (returned)

getAverageLL adds up all of the
LinkedList lengths and divides them
by the number of LinkedLists. Again,
LinkedLists of length 1 are not
counted.
***********************************/
double HashTable::getAverageLL()
{
    int num = 0;
    for(int i = 0; i < arraySize; i++)
    {
        if(arr[i].getCount() > 1)
            num += arr[i].getCount() - 1;
    }
    if(getNumberLL())
        return static_cast<double>(num)/getNumberLL();
    else
        return 0;
}

/***** HashTable::visitAll *****
In: void visit(Food *)
Out:

visitAll takes a visit function
and passes it to all of the
LinkedLists.
*******************************/
void HashTable::visitAll(void visit(Food *))
{
    for(int i = 0; i < arraySize; i++)
    {
        if(arr[i].getCount())
            arr[i].visitAll(visit);
    }
}