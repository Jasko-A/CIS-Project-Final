// List Manager Source File for screen output
// Written by Ahmed Shalan


#include "../HeaderFiles/ListManager.h"

/* ==================================================
                    listManager
 
Desc- The list manager function starts a menu loop
      with options for listing the data contained
      in the two binary trees and the hash table
In  - The function recieves pointers of the primary and
      secondary BSTs and a pointer to the hash table
Out - The function itself has no return value. The
      function displays a menu with options in a loop
      until quit is selected to exit the menu loop.
 ==================================================== */
void listManager(BinarySearchTree * primaryTree, BinarySearchTree * secondaryTree, HashTable * hashTable){
    //Flag to check whether quit was selected
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
                
                //Option to list the indented primary and secondary trees
            case 'I':
                indentedPrint(primaryTree, secondaryTree);
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

/* ==================================================
                    unsortedList
 
 Desc- Calls the visitAll function from the HashTable 
       class to list the data in an unsorted sequence.
 In  - A pointer to the hash table.
 Out - Outputs the unsorted data in hash table sequence.
 ==================================================== */
void unsortedList(HashTable * hashTable)
{
    cout << "Listing unsorted data in hash table sequence: \n";

    //Calls the visitAll function from the hash table class
    hashTable->visitAll(displayFoodData);
}

/* ==================================================
                    treeList
 
 Desc- Calls the inOrderPrint function from the BST
       class to list the data in a sorted sequence
 In  - A pointer to the binary search tree
 Out - Outputs the data in the tree sorted
 ==================================================== */
void treeList(BinarySearchTree * tree)
{
    //Calls the inOrder print function from the BST
    tree->inOrderPrint(displayFoodData);
}

/* ==================================================
                 indentedPrint
 
 Desc- Calls the printIndentedTree function from the 
       BST class to list the data in a special print
 In  - A pointer to the primary and secondary BST
 Out - Outputs the indented trees
 ==================================================== */
void indentedPrint(BinarySearchTree * primaryTree, BinarySearchTree * secondaryTree){
    cout << "Printing the indented trees: \n\n";
    
    //Prints the indented primary tree
    cout << "Sorted by USDA number:\n";
    primaryTree->printIndentedTree();
    
    //Prints the indented secondary tree
    cout << "Sorted by the food's name:\n";
    secondaryTree->printIndentedTree();
}

