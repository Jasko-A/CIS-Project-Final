// List Manager Source File for Team Project
// Ahmed Shalan


#include "../HeaderFiles/ListManager.h"

/** =================================== */
/* <function purpose>
<explanation of all input parameters>
<explanation of all output actions and return value > */
void listManager(BinarySearchTree * primaryTree, BinarySearchTree * secondaryTree, HashTable * hashTable){
    bool quit = false;

    //Used during the menu loop
    string input;
    char command;


    //Loop while the user has not entered the quit command (quit = 'q')
    while(!quit){

        //Displays the menu to the user
        cout << "\n           List Manager           \n";
        cout << "----------------------------------\n";
        cout << "U - List Unsorted Data\n";
        cout << "N - List by Nutrient Databank Number\n";
        cout << "D - List by Description\n";
        cout << "I - Print as an Indented List\n";
        cout << "Q - Quit List Manager\n\n";

        //Get the input from the user
        cin.sync();
        cout << "Enter a Menu Option:  ";
        getline(cin, input);
        command = input[0];

        //Forces all command inputs to uppercase (t and T are both T);
        command = toupper(command);

        //Process the menu command
        switch(command){

                 //Option to list unsorted data in hash table sequence
            case 'U':
                unsortedList(hashTable);
                break;

                 //Option to list by a unique key, which is the USDA identification number
            case 'N':
                cout << "Listing by the USDA identification number: \n";
                treeList(primaryTree);
                break;

                //Option to list by a secondary key, which is the food name
            case 'D':
                cout << "Listing alphabetically by the foods name: \n";
                treeList(secondaryTree);
                break;

            case 'I':
                cout << "Printing the indented trees: \n\n";

                cout << "Sorted by USDA number:\n";
                primaryTree->printIndentedTree();

                cout << "Sorted by the food's name:\n";
                secondaryTree->printIndentedTree();
                break;

                //Quit out of the sub menu.
            case 'Q':
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

/** =================================== */
/* <function purpose>
<explanation of all input parameters>
<explanation of all output actions and return value > */
void unsortedList(HashTable * hashTable)
{
    cout << "Listing unsorted data in hash table sequence: \n";

    hashTable->visitAll(displayItem);
}

/** =================================== */
/* <function purpose>
<explanation of all input parameters>
<explanation of all output actions and return value > */
void treeList(BinarySearchTree * tree)
{
    tree->inOrderPrint();
}


/** =================================== */
/* <function purpose>
<explanation of all input parameters>
<explanation of all output actions and return value > */
void displayItem(Food * foodItem){
        cout << "\nFood Key  : " << foodItem->getKey() << endl;
        cout << "Food Name : " << foodItem->getName() << endl;
        if(foodItem->getW() >= 0)
            cout << "\tWater     : " << foodItem->getW() << endl;
        if(foodItem->getC() >= 0)
            cout << "\tCalories  : " << foodItem->getC() << endl;
        if(foodItem->getP() >= 0)
            cout << "\tProtein   : " << foodItem->getP() << endl;
        if(foodItem->getF() >= 0)
            cout << "\tFat       : " << foodItem->getF() << endl;
        if(foodItem->getFi() >= 0)
            cout << "\tFiber     : " << foodItem->getFi() << endl;
        if(foodItem->getS() >= 0)
            cout << "\tSugar     : " << foodItem->getS();
}

