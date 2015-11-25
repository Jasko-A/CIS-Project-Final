/**
TESTING FILE FOR HashTable
DO NOT INCLUDE IN FINAL PROJECT
**/
#include "../HeaderFiles/Food.h"
#include "../HeaderFiles/HashTable.h"
#include <iostream>
#include <iomanip>

using namespace std;

void display(Food * a);

int main()
{
    cout << left;
    //Create the objects to be used
    Food *a = new Food(12345, "Test Item", 1.1, 2, 3.3, 4.4, 5.5, 6.6), *b = new Food(54325, "Test Item 2", 0,0,0,0,0,0), *temp;
    HashTable table(10);

    //Get stats
    cout << setw(20) << "INITAL STATE-" << "Collisions: " << table.getCollisions() << " Filled Slots: " << table.getFilledSlots() << " Count: " << table.getCount() << endl;
    //Add Food to table
    table.addEntry(a);

    //Get stats
    cout << setw(20) << "ADD a-" << "Collisions: " << table.getCollisions() << " Filled Slots: " << table.getFilledSlots() << " Count: " << table.getCount() << endl;
    table.addEntry(b);

    //Get stats
    cout << setw(20) << "ADD b-" << "Collisions: " << table.getCollisions() << " Filled Slots: " << table.getFilledSlots() << " Count: " << table.getCount() << endl;

    cout << endl;
    table.visitAll(display);
    cout << endl;

    //Do a search. They are in the same linked list
    if(table.search(b->getKey(), temp))
        cout << "SEARCH SUCCESS, ID: " << temp->getKey() << endl;
    else
        cout << "SEARCH FAILURE, ID: " << b->getKey() << endl;

    //Get stats
    cout << setw(20) << "POST-SEARCH-" << "Collisions: " << table.getCollisions() << " Filled Slots: " << table.getFilledSlots() << " Count: " << table.getCount() << " Number of Linked Lists: " << table.getNumberLL() << " Longest Linked List: " << table.getLongestLL() << " Average Linked List: " << table.getAverageLL() << endl;
    //Attempt to remove
    if(table.remove(a))
        cout << "REMOVE SUCCESS, a\n";
    else
        cout << "REMOVE FAILED\n";

    //Get stats
    cout << setw(20) << "POST-REMOVAL-" << "Collisions: " << table.getCollisions() << " Filled Slots: " << table.getFilledSlots() << " Count: " << table.getCount() << endl;

    return 0;
}

void display(Food * a)
{
    cout << a->getName() << endl;
}
