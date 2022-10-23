#include "Point.h"

Point::Point(int y, int x)
{
	this->y = y;
	this->x = x;
}

Point::Point()
{
	y = 0;
	x = 0;
}

Point& Point::operator=(const Point& other)
{
	this->x = other.x;
	this->y = other.y;
	return *this;
}

int Point::getX()
{
	return x;
}

int Point::getY()
{
	return y;
}

void Point::setX(int x)
{
	this->x = x;
}

void Point::setY(int y)
{
	this->y = y;
}

