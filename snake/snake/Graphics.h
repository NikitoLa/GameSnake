#pragma once
#include<vector>
#include "Resources.h"
#include "snake.h"
#include "Apple.h"


#define FIELD_CELL_TYPE_APPLE -1
#define FIELD_CELL_TYPE_WALL -2
#define FIELD_CELL_TYPE_DOOR -3
#define FIELD_CELL_TYPE_UP_ARROW -4
#define FIELD_CELL_TYPE_NONE 0

class Snake;
	
class Graphics : public sf::RenderWindow, public Resources
{
private:
	class GameParameters;

public:
	Graphics(int, int, int, int);
	~Graphics();
	
	void addSnakeOnGameField(Snake&);
	void drawGameField();
	Point getMidleOfField();
	void drawGameOver();
	void drawGameWin();
	void drawScoreBar();
	void addAppleOnGameField();
	GameParameters* getGameParameters();

	friend Snake;

private:

	Apple getEmptyCellForApple();
	void loadResours();

	int score_bar_height;
	int field_size_x;
	int field_size_y;
	int cell_size;
	int window_width;
	int window_hight;

	std::vector<std::vector<int>> field;

	Point coordinates_of_snake_head;

	class GameParameters
	{
	public:
		bool game_over = false;
		bool game_started = false;
		bool game_paused = true;
		bool door_open = false;
		bool game_win = false;

		const int max_amount_apples = 12;
		const int max_timeout_apples = 50;

		int game_over_timeout = 0;
		int timeout_apples = 50;
		int seettings_volume = 50;
		int apples_remain = 10;
		int apples_on_field = 1;
		
	};

	GameParameters* parameters;
};

