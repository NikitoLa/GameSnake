#pragma once
#include "Point.h"

class Apple
{
public:
	Apple(Point&);
	Apple(int, int);
	Point getCoordinatesOfApple();
	//static int getAmountOfApples();
	//static void addOneApple();

private:
	Point coordinates_of_apple;
	//static int amount_of_apples;
};

