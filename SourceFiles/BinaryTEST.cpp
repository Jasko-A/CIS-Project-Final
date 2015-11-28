#include<iostream>
#include"../HeaderFiles/Food.h"
#include"../HeaderFiles/BinarySearchTree.h"

using namespace std;

int main()
{
	Food * a = new Food(12345, "test", 1, 2, 3, 4, 5, 6);

	cout << "Sort by unique key:\n";
	BinarySearchTree keyTree(1);
	keyTree.insert(a);
	if(keyTree.search(a->getKey()))
		cout << "FOUND\n";
	else
		cout << "NOT FOUND\n";
	if(keyTree.remove(a->getKey()))
		cout << "REMOVED\n";
	else
		cout << "FAILED\n";
	if(keyTree.search(a->getKey()))
		cout << "FOUND\n";
	else
		cout << "NOT FOUND\n";

	cout << "\nSort by secondary key:\n";
	BinarySearchTree secTree(0);
	secTree.insert(a);
	if(secTree.search(a->getName()))
		cout << "FOUND\n";
	else
		cout << "NOT FOUND\n";
	if(secTree.remove(a->getName()))
		cout << "REMOVED\n";
	else
		cout << "FAILED\n";
	if(secTree.search(a->getName()))
		cout << "FOUND\n";
	else
		cout << "NOT FOUND\n";
	delete a;
	return 0;
}
