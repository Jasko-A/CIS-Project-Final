// List Manager Source File for Team Project
// Ahmed Shalan


#include "../HeaderFiles/ListManager.h"


void listManager(BinarySearchTree * primaryTree, BinarySearchTree * secondaryTree, HashTable * hashTable){
    cout << "Search option selected\n";
    cout << "Now displaying the search menu\n\n";
    bool quit = false;

    //Used during the menu loop
    string input;
    char command;

    //Displays the menu to the user initially
    cout << "            List Manager          \n";
    cout << "----------------------------------\n";
    cout << "U) List unsorted data according to hash table\n";
    cout << "P) List by USDA identification number\n";
    cout << "S) List by food name\n";
    cout << "M) Show Menu\n";
    cout << "Q) Quit\n\n";


    //Loop while the user has not entered the quit command (quit = 'q')
    while(!quit){
        //Get the input from the user
        cin.sync();
        cout << "Enter a menu option:  ";
        getline(cin, input);
        command = input[0];

        //Forces all command inputs to uppercase (t and T are both T);
        command = toupper(command);

        //Process the menu command
        switch(command){

                 //Option to list unsorted data in hash table sequence
            case 'H':
                unsortedList(hashTable);
                break;

                 //Option to list by a unique key, which is the USDA identification number
            case 'P':
                treeList(primaryTree);
                break;

                //Option to list by a secondary key, which is the food name
            case 'S':
                treeList(secondaryTree);
                break;

                //Display the menu
            case 'M':
                cout << "\n                 MENU                 \n";
                cout << "----------------------------------------\n";
                cout << "U) List unsorted data according to hash table\n";
                cout << "P) List by USDA identification number\n";
                cout << "S) List by food name\n";
                cout << "M) Show Menu\n";
                cout << "Q) Quit\n\n";

                break;

                //Quit out of the sub menu.
            case 'Q':
                cout << "Now quiting the list manager\n";

                quit = true;
                break;

                //Default option if the command entered was not one of the acceptable options
            default:
                cout << "Command not found. Use 'M' to display the menu" << endl;
                break;
        }
        cout << endl;
    }
}

void unsortedList(HashTable * hashTable)
{
    cout << "Listing unsorted data in hash table sequence: \n";

    hashTable->visitAll(displayItem);
}

void treeList(BinarySearchTree * tree)
{
    cout << "Listing by the USDA identification number: \n";

    Food * food;
    Stack<Food *> tempStack = tree->inOrderStack();

    while(!tempStack.isEmpty()){
        tempStack.pop(food);
        displayItem(food);
    }
}


void displayItem(Food * foodItem){
        cout << "\tFood Key  : " << foodItem->getKey() << endl;
        cout << "\tFood Name : " << foodItem->getName() << endl;
        cout << "\tWater     : " << foodItem->getW() << endl;
        cout << "\tCalories  : " << foodItem->getC() << endl;
        cout << "\tProtein   : " << foodItem->getP() << endl;
        cout << "\tFat       : " << foodItem->getF() << endl;
        cout << "\tFiber     : " << foodItem->getFi() << endl;
        cout << "\tSugar     : " << foodItem->getS() << endl;
}

