// Search Manager Source File for screen output
// Written by Ahmed Shalan


#include "../HeaderFiles/SearchManager.h"

/* ==================================================
                    searchManager
 
 Desc- The search manager function starts a menu loop
       with options for searching the data in the BST's
       by key or by name.
 In  - The function recieves pointers of the primary and
       secondary BSTs.
 Out - The function itself has no return value. The
       function displays a menu with options in a loop
       until quit is selected to exit the menu loop.
 ==================================================== */
void searchManager(BinarySearchTree * primaryTree, BinarySearchTree * secondaryTree){
    //Flag to check whether the user selected quit
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

        //Gets the input from the user
        cin.sync();
        cout << "Enter a Menu Option:  ";
        getline(cin, input);
        command = input[0];

        //Forces all command inputs to uppercase (t and T are both T);
        command = toupper(command);

        //Processes the menu command
        switch(command){

                //Option to search using a unique key, which is the USDA databank number
            case 'N':
                PrimaryKeySearchManager(primaryTree);
                break;

                //Option to search using a secondary key, which is the USDA food name
            case 'D':
                SecondaryKeySearchManager(secondaryTree);
                break;

                //Quit out of the search manager sub menu.
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

//Decleration of the enterInt() function from main, which is also
//used in the functions for search manager.
int enterInt();


/* ==================================================
               PrimaryKeySearchManager
 
 Desc- This function searches the BST by unique key
 In  - The function recieves a pointer to the primary BST
 Out - The function has no return values but outputs the
       food item being searched for if it is found.
 ==================================================== */
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


/* ==================================================
            SecondaryKeySearchManager
 
 Desc- This function searches the BST by the secondary key,
       which is the foods name.
 In  - The function recieves a pointer to the secondary BST
 Out - The function has no return values but outputs the
       food item being searched for if it is found.
 ==================================================== */
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

    //Display the item if it's found
    if(!secondaryTree->search(name, displayFoodData))
        cout << endl << name << " was not found in the USDA Nutritional Database.";
}


/* ==================================================
                displayFoodData
 
 Desc- This function displays the contents of a food items
       member data when called. Called during searches
       and lists (in the list manager files)
 In  - The function recieves a pointer to a food object
 Out - The function has no return values but outputs all
       of the foods data in a organized fashion.
 ==================================================== */
void displayFoodData(Food * searchedFoodItem){
        cout << "\n\nNDB_No.    (5 digit): " << searchedFoodItem->getKey() << endl;
        cout << "Shrt_Desc  (60 char): " << searchedFoodItem->getName() << endl;
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
