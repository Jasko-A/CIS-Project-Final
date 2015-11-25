#ifndef FOOD_H
#define FOOD_H

#include <iostream>

#include <string>

using namespace std;

class Food
{
private:
	struct node
	{
		string key;
		node * next;
	};
	node * rootPtr;
	int uniqueKey;
	string foodDescription;
	double water;
	int calories;
	double protein;
	double fat;
	double fiber;
	double sugar;

public:
	Food();
	Food(int key, string name, double w, int c, double p, double f, double fi, double s);

	friend bool operator> (const Food &F1, const Food &F2) {return F1.uniqueKey > F2.uniqueKey;}
	friend bool operator< (const Food &F1, const Food &F2) {return F1.uniqueKey < F2.uniqueKey;}
	friend bool operator== (const Food &F1, const Food &F2) {return F1.uniqueKey == F2.uniqueKey;}
	Food & operator=(const Food &F2);

	int getKey() const { return uniqueKey; }
	string getName() const { return foodDescription; }
	double getW() const { return water; }
	int getC() const { return calories; }
	double getP()const { return protein; }
	double getF() const { return fat; }
	double getFi() const { return fiber; }
	double getS() const { return sugar; }
	bool secondaryKey(string testKey);

	void setKey(int key);
	void setName(string name);
	void setW(double w);
	void setC(int c);
	void setP(double p);
	void setF(double f);
	void setFi(double fi);
	void setS(double s);
};






#endif
