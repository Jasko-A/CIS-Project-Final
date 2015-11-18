#include "Food.h"

food::food()
{
	uniqueKey = 0;
	foodDescription = "";
	water = 0.0;
	calories = 0;
	protein = 0.0;
	fat = 0.0;
	fiber = 0.0;
	sugar = 0.0;

}
food::food(int _key, string _name, double _water, int _calories, double _protien, double _fat, double _fiber, double _sugar)
{
	uniqueKey = _key;
	foodDescription = _name;
	water = water;
	calories = _calories;
	protein = _protien;
	fat = _fat;
	fiber = _fiber;
	sugar = _sugar;

	/*
	setKey(_key);
	setName(_name);
	setW(_water);
	setC(_calories);
	setP(_protien);
	setF(_fat);
	setFi(_fiber);
	setS(_sugar);

	*/

}

void food::setKey(int _key)
{
	uniqueKey = _key;
}
/*int uniqueKey;
string foodDescription;
double water;
int calories;
double protein;
double fat;
double fiber;
double sugar;*/
void food::setName(string _name)
{
	foodDescription = _name;
}
void food::setW(double _water)
{
	water = water;
}
void food::setC(int _calories)
{
	calories = _calories;
}
void food::setP(double _protien)
{
	protein = _protien;
}
void food::setF(double _fat)
{
	fat = _fat;
}
void food::setFi(double _fiber)
{
	fiber = _fiber;
}
void food::setS(double _sugar)
{
	sugar = _sugar;
}