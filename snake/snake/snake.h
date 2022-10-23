#pragma once
#include "Point.h"
#include "Graphics.h"

class Graphics;

class Snake
{
public:
	Point getCoordinates();

	int getLenght();

	Snake(Graphics&);

	void makeMove(Graphics&);

	std::vector<int> getSnakeDiractionQueue();

	void addInSnakeDiracionQueue(int);

	int getSnakeDiraction();

	void setSnakeDiraction();

	void changeSnakeDiractionQueue();

	enum Diractions
	{
		UP = 0,
		RIGHT = 1,
		DOWN = 2,
		LEFT = 3
	};

private:
	
	void growSnake(Graphics&);

	Point coordinates;
	int snake_lenght;
	int snake_diraction;
	std::vector<int> snake_diraction_queue;

};
