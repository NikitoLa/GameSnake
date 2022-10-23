#include "Apple.h"

Apple::Apple(Point& coordinate_of_apple)
{
	coordinates_of_apple = coordinate_of_apple;
	//amount_of_apples--;
}

Apple::Apple(int y, int x)
{
	coordinates_of_apple = Point(y, x);
	//amount_of_apples--;
}

Point Apple::getCoordinatesOfApple()
{
	return coordinates_of_apple;
}

//int Apple::getAmountOfApples()
//{
//	return amount_of_apples;
//}

//void Apple::addOneApple()
//{
//	amount_of_apples++;
//}

//int Apple::amount_of_apples = 10;