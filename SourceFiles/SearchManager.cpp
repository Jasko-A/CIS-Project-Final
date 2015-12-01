// Search Manager Source File for Team Project
// Ahmed Shalan

#include "../HeaderFiles/SearchManager.h"


void searchManager(BinarySearchTree * primaryTree, BinarySearchTree * secondaryTree){
    cout << "Search option selected\n";
    cout << "Now displaying the search menu\n\n";
    bool quit = false;

    //Used during the menu loop
    string input;
    char command;

    //Displays the menu to the user initially
    cout << "          Search Manager          \n";
    cout << "----------------------------------\n";
    cout << "P) Search by USDA identification number\n";
    cout << "S) Search by food name\n";
    cout << "M) Show Menu\n";
    cout << "Q) Quit Search Manager\n\n";


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

                //Option to search using a unique key, which is the USDA identification number
            case 'P':
                PrimaryKeySearchManager(primaryTree);
                break;

                //Option to search using a secondary key, which is the USDA food name
            case 'S':
                SecondaryKeySearchManager(secondaryTree);
                break;

                //Display the menu
            case 'M':
                cout << "\n                 MENU                 \n";
                cout << "----------------------------------------\n";
                cout << "P) Search by USDA identification number\n";
                cout << "S) Search by food name\n";
                cout << "M) Show Menu\n";
                cout << "Q) Quit Search Manager\n";
                break;

                //Quit out of the sub menu.
            case 'Q':
                cout << "Now quiting the search\n";

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



void PrimaryKeySearchManager(BinarySearchTree * primaryTree)
{
    int key;
    Food * searchedFoodItem;

    //Have the user enter the ID number
    cout << "Please enter the USDA identification number: ";
    cin >> key;

    //Check if the Food is in the tree
    searchedFoodItem = primaryTree->search(key);

    //Display the item if it's found
    if(searchedFoodItem != nullptr){
        cout << searchedFoodItem->getKey() << " found.\n";
        displayFoodData(searchedFoodItem);
    }else
        cout << key << " was not found in the USDA Nutritional Database.\n";
}

void SecondaryKeySearchManager(BinarySearchTree * secondaryTree)
{
    string name;
    Food * searchedFoodItem;

    //Have the user enter the name
    cout << "Please enter the name of the food as listed in the USDA database: ";
    getline(cin, name);

    //Check if the Food is in the tree
    searchedFoodItem = secondaryTree->search(name);

    //Display the item if it's found
    if(searchedFoodItem != nullptr){
        cout << searchedFoodItem->getName() << " found.\n";
        displayFoodData(searchedFoodItem);
    }else
        cout << name << " was not found in the USDA Nutritional Database.\n";
}

void displayFoodData(Food * searchedFoodItem){
        cout << "\tFood Key  : " << searchedFoodItem->getKey() << endl;
        cout << "\tFood Name : " << searchedFoodItem->getName() << endl;
        cout << "\tWater     : " << searchedFoodItem->getW() << endl;
        cout << "\tCalories  : " << searchedFoodItem->getC() << endl;
        cout << "\tProtein   : " << searchedFoodItem->getP() << endl;
        cout << "\tFat       : " << searchedFoodItem->getF() << endl;
        cout << "\tFiber     : " << searchedFoodItem->getFi() << endl;
        cout << "\tSugar     : " << searchedFoodItem->getS() << endl;
}