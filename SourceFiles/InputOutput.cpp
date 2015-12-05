// Input Output Source File for file input and output
// Written by Mikhail Smelik

#include "../HeaderFiles/InputOutput.h"

/** =================================== */
/*fileSize calculates the number of lines in a file by opening it and counting
 A string that holds the file name is passed in
 An int is returned with the number of lines */
int fileSize(string fileName)
{
    ifstream inFile(fileName.c_str());
    int count = 0;
    string temp;
    while(getline(inFile, temp))
        count++;
    return count;
}

/** =================================== */
/*hashSize takes the the number of lines in the file and calulates the next prime
 immediately above 2*fileSize to give us the hash size
 An int containing the number of lines is passed in
 An int containg the size of the array is returned */
int hashSize(int fileSize)
{
    int number = 0;
    int hashSize = fileSize * 2;
    int sqrtHashSize;
    bool isPrime;
    
    do
    {
        sqrtHashSize = sqrt(hashSize);
        isPrime = true;
        for (int i = 2; i < sqrtHashSize; i++)
        {
            if (hashSize % i == 0)
            {
                isPrime = false;
                break;
            }
        }
        hashSize++;
    } while (isPrime == false);
    number = hashSize - 1;
    
    return number;
}

/** =================================== */
/* fileInput takes an ifstream, reads a line, and puts data into a Food object, whose pointer it passes back
 It takes an ifstream object by reference
 It returns a Food pointer */
Food* fileInput(ifstream &inFile)//For an example of this function in action, run while(fileInput(inFile)); OR while(temp = fileInput(inFile));
{
    string buffer;
    getline(inFile, buffer);
    
    if (buffer.length()) //Ensures we don't go out of range
    {
        int index;
        int start;
        static const char carrot = '^'; //Not even really necessary
        
        double water;
        int calories;
        double protein;
        double fat;
        double fiber;
        double sugar;
        
        int key = stoi(buffer.substr(1, 6));//Key
        
        buffer = buffer.substr(9, buffer.length());
        index = buffer.find(carrot);
        string name = buffer.substr(0, index-1);//Name
        
        start = index + 2;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot);//Water
        start = 0;
        if ((buffer.substr(start, index)).length())
            water = stod(buffer.substr(start, index));
        else
            water = -1;
        
        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot);//Calories
        start = 0;
        if ((buffer.substr(start, index)).length())
            calories = stoi(buffer.substr(start, index));
        else
            calories = -1;
        
        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot);//Protein
        start = 0;
        if ((buffer.substr(start, index)).length())
            protein = stod(buffer.substr(start, index));
        else
            protein = -1;
        
        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot);//Fat
        start = 0;
        if ((buffer.substr(start, index)).length())
            fat = stod(buffer.substr(start, index));
        else
            fat = -1;
        
        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot); //Ash
        
        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot); //Carbohydrates
        
        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot); //Fiber
        start = 0;
        if ((buffer.substr(start, index)).length())
            fiber = stod(buffer.substr(start, index));
        else
            fiber = -1;
        
        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot); //Fiber
        start = 0;
        if ((buffer.substr(start, index)).length())
            sugar = stod(buffer.substr(start, index));
        else
            sugar = -1;
        
        Food * newFood = new Food(key, name, water, calories, protein, fat, fiber, sugar);
        return newFood;
    }
    else
        return NULL;
}

/** =================================== */
/* createADTs inserts the Food objects passed from fileInput into the ADTs
 It takes an ifstream, two BinarySearchTrees, and a HashTable, all by reference
 It returns nothing (But changes the ADTs passed to it by reference) */
void createADTs(ifstream &inFile, BinarySearchTree &keyBST, BinarySearchTree &secBST, HashTable *hTable)
{
    Food * temp;
    while(temp = fileInput(inFile))
    {
        keyBST.insert(temp);
        secBST.insert(temp);
        hTable->addEntry(temp);
    }
    return;
}

/** =================================== */
/* emptyADTs clears the ADTs so that they can be filled again
 It takes a string for the file name as well as references to two BinarySearchTrees and a HashTable
 It returns nothing */
void emptyADTs(string fileName, BinarySearchTree &keyBST, BinarySearchTree &secBST, HashTable *hTable) //Needs the BSTs
{
    hTable->rehash(hashSize(fileSize(fileName)));
    keyBST.clear();
    secBST.clear();
}

/** =================================== */
/* printToFile prints all of the data to an output file in the same syntax it was recieved
 It takes an ofstream and a BST, both by reference
 It returns nothing, but outputs data to the file */
void printToFile(ofstream &outFile, BinarySearchTree &BST)
{
    const int size = BST.size();
    Food **arr = new Food*[size];
    BST.inOrderArr(arr);
    for (int i = 0; i < size; i++)
    {
        outFile <<"~" << arr[i]->getKey()<< "~^~" << arr[i]->getName() << "~^";
        if(arr[i]->getW() >= 0)
            outFile << arr[i]->getW();
        outFile << "^";
        if(arr[i]->getC() >= 0)
            outFile << arr[i]->getC();
        outFile << "^";
        if(arr[i]->getP() >= 0)
            outFile << arr[i]->getP();
        outFile << "^";
        if(arr[i]->getF() >= 0)
            outFile << arr[i]->getF();
        outFile << "^^^";
        if(arr[i]->getFi() >= 0)
            outFile << arr[i]->getFi();
        outFile << "^";
        if(arr[i]->getS() >= 0)
            outFile << arr[i]->getS();
        outFile << "^\n";
    }
}

/** =================================== */
/* reHash creates a new hash table of a new size and populates it with the data from the old hash
 It takes a BST by reference and a hTable by pointer
 It returns nothing, but changes the pointer of the hTable */
void reHash(HashTable *hTable, BinarySearchTree &BST)
{
    const int size = BST.size();
    Food **arr = new Food*[size];
    BST.inOrderArr(arr);
    
    hTable->rehash(hashSize(hTable->getFilledSlots()));

    
    for (int i = 0; i < size; i++)
    {
        hTable->addEntry(arr[i]);
    }
    
}

