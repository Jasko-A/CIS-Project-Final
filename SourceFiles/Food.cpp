//Created by: Jasmin Adzic

#include "../HeaderFiles/Food.h"
/** =========================*/
/*This is the food object constructor
The purpose of this function is to set everything to an intial state.
turns all private values in the object to NULL
*/
Food::Food()
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
/** ===========================*/
/*This is another Food constructor that sets all values at once when being read from a file
The pupose of this function is to set all the private values to the values read in by the input function
*/
Food::Food(int _key, string _name, double _water, int _calories, double _protien, double _fat, double _fiber, double _sugar)
{
	uniqueKey = _key;
	foodDescription = _name;
	water = _water;
	calories = _calories;
	protein = _protien;
	fat = _fat;
	fiber = _fiber;
	sugar = _sugar;

}
/** ============================*/
/*Operator equal puropose is to overload the value in refernce to the object.
Accepts a const reference to the object that contains the data values in food
*/
Food & Food::operator=(const Food & F2)
{
	// TODO: insert return statement here
	 uniqueKey = F2.uniqueKey; 
	 foodDescription = F2.foodDescription; 
	 water = F2.water; 
	 calories = F2.calories; 
	 protein = F2.protein; 
	 fat = F2.fat; 
	 fiber = F2.fiber; 
	 sugar = F2.sugar;

	 return *this;
}

/**=======================*/
/*All the setters below are to set just the specific value in that data
each accpet there own parameter that will later be converted into the private data values
*/
void Food::setKey(int _key)
{
	uniqueKey = _key;
}
/*int uniqueKey;
string FoodDescription;
double water;
int calories;
double protein;
double fat;
double fiber;
double sugar;*/
void Food::setName(string _name)
{
	foodDescription = _name;
}
void Food::setW(double _water)
{
	water = _water;
}
void Food::setC(int _calories)
{
	calories = _calories;
}
void Food::setP(double _protien)
{
	protein = _protien;
}
void Food::setF(double _fat)
{
	fat = _fat;
}
void Food::setFi(double _fiber)
{
	fiber = _fiber;
}
void Food::setS(double _sugar)
{
	sugar = _sugar;
}
