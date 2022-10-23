#include "snake.h"

Snake::Snake(Graphics& graph)
{
	snake_lenght = 3;
	snake_diraction = Snake::RIGHT;
	coordinates = graph.getMidleOfField();
}

void Snake::makeMove(Graphics& graph)
{
	switch (snake_diraction)
	{
	case Snake::UP:
		coordinates.setY(coordinates.getY() - 1);
		break;

	case Snake::RIGHT:
		coordinates.setX(coordinates.getX() + 1);
		break;

	case Snake::DOWN:
		coordinates.setY(coordinates.getY() + 1);
		break;

	case Snake::LEFT:
		coordinates.setX(coordinates.getX() - 1);
		break;
	}

	
	
	if (graph.field[coordinates.getY()][coordinates.getX()] != FIELD_CELL_TYPE_NONE)
	{
		switch (graph.field[coordinates.getY()][coordinates.getX()])
		{
		case FIELD_CELL_TYPE_APPLE:
			
			graph.parameters->apples_remain--;		
			graph.parameters->apples_on_field--;
			graph.parameters->timeout_apples = graph.parameters->max_timeout_apples;
			graph.sounds[Resources::Sounds::COLLECT_POINT].play();
			snake_lenght++;
			growSnake(graph);

			if (graph.parameters->apples_remain == 0)
			{
				graph.parameters->door_open = true;
				graph.field[0][graph.field_size_x / 2] = FIELD_CELL_TYPE_UP_ARROW;
			}

			if (graph.parameters->apples_on_field < 1 and !graph.parameters->door_open)
			{	
				graph.addAppleOnGameField();
				graph.parameters->apples_on_field++;
			}	
			break;

		case FIELD_CELL_TYPE_WALL:
			graph.sounds[Resources::Sounds::EXPLOSION].play();
			graph.getGameParameters()->game_over = true;
			break;

		case FIELD_CELL_TYPE_DOOR:
			graph.sounds[Resources::Sounds::EXPLOSION].play();
			graph.getGameParameters()->game_over = true;
			break;

		case FIELD_CELL_TYPE_UP_ARROW:
			graph.sounds[Resources::Sounds::WIN_SOUND].play();
			graph.getGameParameters()->game_win = true;
			break;

		default:
			if (graph.field[coordinates.getY()][coordinates.getX()] > 1)
			{
				graph.sounds[Resources::Sounds::EXPLOSION_2].play();
				graph.getGameParameters()->game_over = true;
			}
		}
	}

	if (!graph.getGameParameters()->game_over)
	{
		for (int j = 0; j < graph.field_size_y; j++)
		{
			for (int i = 0; i < graph.field_size_x; i++)
			{
				if (graph.field[j][i] > FIELD_CELL_TYPE_NONE)
				{
					graph.field[j][i]--;
				}

			}
			graph.field[coordinates.getY()][coordinates.getX()] = snake_lenght;
		}
	}
	
}

std::vector<int> Snake::getSnakeDiractionQueue()
{
	return snake_diraction_queue;
}

void Snake::addInSnakeDiracionQueue(int SNAKE_DIRACTION_X)
{
	snake_diraction_queue.insert(snake_diraction_queue.begin(), SNAKE_DIRACTION_X);
}

int Snake::getSnakeDiraction()
{
	return snake_diraction;
}

void Snake::setSnakeDiraction()
{
	snake_diraction = snake_diraction_queue.back();
}

void Snake::changeSnakeDiractionQueue()
{
	snake_diraction_queue.pop_back();
}

void Snake::growSnake(Graphics& graph)
{
	int empty_cell_count = 0;
	for (int j = 0; j < graph.field_size_y; j++)
	{
		for (int i = 0; i < graph.field_size_x; i++)
		{
			if (graph.field[j][i] > FIELD_CELL_TYPE_NONE)
			{
				graph.field[j][i]++;
			}
		}
	}
}

Point Snake::getCoordinates()
{
	return coordinates;
}

int Snake::getLenght()
{
	return snake_lenght;
}


