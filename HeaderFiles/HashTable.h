/*****
HashTable Class
Written by: Austin Bohannon

Made to work with pointers to objects so that no data has to be copied,
it's just organized.
*****/

#include "LinkedList.h"

template <class T>
class HashTable
{
    LinkedList<T> * arr[];
    int arraySize, filledSlots, collisions, count;
    int _hash(int & id);
public:
    //Constructor - Destructor
    HashTable(int & setSize);
    ~HashTable();
    //Mutators and accessors
    void addEntry(T * newEntry);
    bool remove(T * deletePtr);
    bool search(int & id, T * returnedPtr);
    //Const accessors
    int getSize() const {return arraySize;}
    int getFilledSlots() const {return filledSlots;}
    int getCollisions() const {return collisions;}
    int getCount() const {return count;}
}
