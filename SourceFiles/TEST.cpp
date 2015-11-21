/**
TESTING FILE FOR HashTable
DO NOT INCLUDE IN FINAL PROJECT
**/
#include "../HeaderFiles/Food.h"
#include "../HeaderFiles/HashTable.h"
#include <iostream>

using namespace std;

int main()
{
    //Create the objects to be used
    Food *a = new Food(12345, "Test Item", 1.1, 2, 3.3, 4.4, 5.5, 6.6), *b = new Food(54325, "Test Item 2", 0,0,0,0,0,0), *temp;
    HashTable table(10);

    //Add Food to table
    table.addEntry(a);
    table.addEntry(b);

    //Get stats
    cout << "Collisions: " << table.getCollisions() << " Filled Slots: " << table.getFilledSlots() << " Count: " << table.getCount() << endl;
    //Do a search. They are in the same linked list
    if(table.search(b->getKey(), temp))
        cout << "SEARCH SUCCESS, ID: " << temp->getKey() << endl;
    else
        cout << "SEARCH FAILURE, ID: " << b->getKey() << endl;

    //Get stats
    cout << "Collisions: " << table.getCollisions() << " Filled Slots: " << table.getFilledSlots() << " Count: " << table.getCount() << endl;
    //Attempt to remove
    if(table.remove(a))
        cout << "a REMOVED\n";
    else
        cout << "REMOVE FAILED\n";

    //Get stats
    cout << "Collisions: " << table.getCollisions() << " Filled Slots: " << table.getFilledSlots() << " Count: " << table.getCount() << endl;

    return 0;
}
