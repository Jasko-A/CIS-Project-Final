#include "../SourceFiles/main.cpp"

int fileSize(string fileName)
{
	ifstream inFile(fileName.c_str());
	int count = 0;
	string temp;
	while (getline(inFile, temp))
		count++;
	return count;
}

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
		string name = buffer.substr(0, index - 1);//Name

		start = index + 2;
		buffer = buffer.substr(start, buffer.length());
		index = buffer.find(carrot);//Water
		start = 0;
		if ((buffer.substr(start, index)).length())
			water = stod(buffer.substr(start, index));
		else
			water = 0;

		start = index + 1;
		buffer = buffer.substr(start, buffer.length());
		index = buffer.find(carrot);//Calories
		start = 0;
		if ((buffer.substr(start, index)).length())
			calories = stoi(buffer.substr(start, index));
		else
			calories = 0;

		start = index + 1;
		buffer = buffer.substr(start, buffer.length());
		index = buffer.find(carrot);//Protein
		start = 0;
		if ((buffer.substr(start, index)).length())
			protein = stod(buffer.substr(start, index));
		else
			protein = 0;

		start = index + 1;
		buffer = buffer.substr(start, buffer.length());
		index = buffer.find(carrot);//Fat
		start = 0;
		if ((buffer.substr(start, index)).length())
			fat = stod(buffer.substr(start, index));
		else
			fat = 0;

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
			fiber = 0;

		start = index + 1;
		buffer = buffer.substr(start, buffer.length());
		index = buffer.find(carrot); //Fiber
		start = 0;
		if ((buffer.substr(start, index)).length())
			sugar = stod(buffer.substr(start, index));
		else
			sugar = 0;

		Food * newFood = new Food(key, name, water, calories, protein, fat, fiber, sugar);
		return newFood;
	}
	else
		return NULL;
}

void createADTs(ifstream &inFile, BinarySearchTree &keyBST, BinarySearchTree &secBST, HashTable &hTable)
{
	Food * temp;
	while (temp = fileInput(inFile))
	{
		keyBST.insert(temp);
		secBST.insert(temp);
		hTable.addEntry(temp);
	}
	return;
}

void emptyADTs(string fileName, BinarySearchTree &keyBST, BinarySearchTree &secBST, HashTable &hTable) //Needs the BSTs
{
	hTable.rehash(hashSize(fileSize(fileName)));
}

void printToFile(ofstream &outFile, Stack<Food*>* printStack)
{
	Food * temp;
	outFile << "Sorted Data using the unique key" << endl << endl;
	while (printStack->getCount() != 0)
	{
		printStack->pop(temp);
		outFile << "~" << temp->getKey() << "~^~" << temp->getName() << "~^" << temp->getW() << "^" << temp->getC() << "^" << temp->getP();
		outFile << "^" << temp->getF() << "^" << temp->getFi() << "^" << temp->getS() << "^" << endl;
	}
}

/*void reHash(HashTable &hTable) //Unnecessary
{
int hashActualSize = hTable.getCount();
int newSize = hashSize(hashActualSize);
HashTable newHashTable(newSize);
}*/


void menu()
{
	cout << "\nList of Menu options\n\n";
	cout << "A - Add New Data\n"
		<< "D - Delete Data by key number\n"
		<< "S - Search by unique key or item name\n"
		<< "P - Special Print\n"
		<< "U - Undo Delete\n"
		<< "O - Open a Data File\n"
		<< "W - Write Data to File\n"
		<< "T - Statsitics\n"
		<< "Q - Quit Program\n";
}

Food * addNew()				//needs input validation
{
	int uKey;
	string fName;
	double _water;
	int _cal;
	double _protein;
	double _fat;
	double _fiber;
	double _sugar;

	cout << "\nEnter a key: ";
	cin >> uKey;
	cout << "\nEnter a food name: ";
	cin >> fName;
	cout << "\nEnter water content: ";
	cin >> _water;
	cout << "\nEnter calorie content: ";
	cin >> _cal;
	cout << "\nEnter protein content: ";
	cin >> _protein;
	cout << "\nEnter fat content: ";
	cin >> _fat;
	cout << "\nEnter fiber content: ";
	cin >> _fiber;
	cout << "\nEnter sugar content: ";
	cin >> _sugar;
	cin.ignore(256, '\n');

	Food * newFood = new Food(uKey, fName, _water, _cal, _protein, _fat, _fiber, _sugar);
	return newFood;
}

int enterInt()
{
	int sKey;
	bool success;
	do {
		cout << "Enter a value: ";
		success = cin >> sKey;
		cin.clear();
		cin.ignore(256, '\n');
	} while (!success);
	return sKey;
}

string enterStr()
{
	string str;
	cout << "Enter a string: ";
	cin >> str;
	cin.ignore(256, '\n');
	return str;
}