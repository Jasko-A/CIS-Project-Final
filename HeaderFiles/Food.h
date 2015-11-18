#ifndef FOOD_H
#define FOOD_H

#include <iostream>

#include <string>

using namespace std;

class Food
{
private:
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
	
	friend bool operator> (const Food &F1, const Food &F2) {return F1.uniqueKey > F2.uniqueKey}
	friend bool operator< (const Food &F1, const Food &F2) { return F1.uniqueKey < F2.uniqueKey }
	friend bool operator== (const Food &F1, const Food &F2) { return F1.uniqueKey == F2.uniqueKey }

	int getKey(){ return uniqueKey; }
	string getName(){ return foodDescription; }
	double getW(){ return water; }
	int getC(){ return calories; }
	double getP(){ return protein; }
	double getF(){ return fat; }
	double getFi(){ return fiber; }
	double getS(){ return sugar; }

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