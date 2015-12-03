// Search Manager Source File for Team Project
// Ahmed Shalan

#include "../HeaderFiles/SearchManager.h"

int enterInt();

/*
Purpose of the seachManager is to display menu where the user will enter one of few choices.
If the user wants to search by key it will go to the appropriate functions,
same for food name.
nothing is returned.
*/
void searchManager(BinarySearchTree * primaryTree, BinarySearchTree * secondaryTree){
    bool quit = false;

    //Used during the menu loop
    string input;
    char command;

    //Loop while the user has not entered the quit command (quit = 'q')
    while(!quit){

        //Displays the menu to the user
        cout << "\n          Search Manager          \n";
        cout << "----------------------------------\n";
        cout << "N - Search by Nutrient Databank Number\n";
        cout << "D - Search by Short Description\n";
        cout << "Q - Quit Search Manager\n\n";

        //Get the input from the user
        cin.sync();
        cout << "Enter a Menu Option:  ";
        getline(cin, input);
        command = input[0];

        //Forces all command inputs to uppercase (t and T are both T);
        command = toupper(command);

        //Process the menu command
        switch(command){

                //Option to search using a unique key, which is the USDA identification number
            case 'N':
                PrimaryKeySearchManager(primaryTree);
                break;

                //Option to search using a secondary key, which is the USDA food name
            case 'D':
                SecondaryKeySearchManager(secondaryTree);
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

/*
Purpose of this function is to search by a unique key through the hash table
*/
void PrimaryKeySearchManager(BinarySearchTree * primaryTree)
{
    int key;
    Food * searchedFoodItem;

    //Have the user enter the ID number
    cout << "Nutrient Databank Number- ";
    key = enterInt();

    //Check if the Food is in the tree
    searchedFoodItem = primaryTree->search(key);

    //Display the item if it's found
    if(searchedFoodItem != nullptr){
        displayFoodData(searchedFoodItem);
    }else
        cout << key << " was not found in the USDA Nutritional Database.";
}
/*
Purpose of this function is to search the hash table by food name
*/
void SecondaryKeySearchManager(BinarySearchTree * secondaryTree)
{
    string name;
    Food * searchedFoodItem;

    //Have the user enter the name
    cout << "Short Description- Enter a string: ";
    getline(cin, name);

    //Check if the Food is in the tree
    for(int i = 0; i < name.size(); i++)
        name[i] = toupper(name[i]);

    searchedFoodItem = secondaryTree->search(name);

    //Display the item if it's found
    if(!secondaryTree->search(name, displayFoodData))
        cout << endl << name << " was not found in the USDA Nutritional Database.";
}
/*
The purpose of this function is to, display the contents of the food object
that was searched by the above functions
Shows everthing in the object form the name to the nutrtional facts
*/
void displayFoodData(Food * searchedFoodItem){
        cout << "\tNDB_No.    (5 digit): " << searchedFoodItem->getKey() << endl;
        cout << "\tShrt_Desc  (60 char): " << searchedFoodItem->getName() << endl;
        if(searchedFoodItem->getW() >= 0)
            cout << "\tWater       (g/100g): " << searchedFoodItem->getW() << endl;
        if(searchedFoodItem->getC() >= 0)
            cout << "\tCalories (kcal/100g): " << searchedFoodItem->getC() << endl;
        if(searchedFoodItem->getP() >= 0)
            cout << "\tProtein     (g/100g): " << searchedFoodItem->getP() << endl;
        if(searchedFoodItem->getF() >= 0)
            cout << "\tFat         (g/100g): " << searchedFoodItem->getF() << endl;
        if(searchedFoodItem->getFi() >= 0)
            cout << "\tFiber       (g/100g): " << searchedFoodItem->getFi() << endl;
        if(searchedFoodItem->getS() >= 0)
            cout << "\tSugar       (g/100g): " << searchedFoodItem->getS();
}
