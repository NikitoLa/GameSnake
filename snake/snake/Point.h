#pragma once

class Point
{
public:
	Point(int, int);
	Point();
	Point& operator=(const Point&);
	int getX();
	int getY();
	void setX(int);
	void setY(int);


private:
	int x;
	int y;
};
