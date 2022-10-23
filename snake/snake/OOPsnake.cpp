#include <ctime>
#include "Graphics.h"

void changeSnakeDiraction(Snake& snake, const sf::Event& event)
{
	int snake_diraction_last = snake.getSnakeDiractionQueue().empty() ? snake.getSnakeDiraction() : snake.getSnakeDiractionQueue().at(0);
	
	switch (event.key.code)
	{
	case sf::Keyboard::Up:
		if (snake_diraction_last != Snake::UP && snake_diraction_last != Snake::DOWN)
		{
			if (snake.getSnakeDiractionQueue().size() < 2)
			{
				snake.addInSnakeDiracionQueue(Snake::UP);
			}

		}
		break;

	case sf::Keyboard::Right:
		if (snake_diraction_last != Snake::RIGHT && snake_diraction_last != Snake::LEFT)
		{
			if (snake.getSnakeDiractionQueue().size() < 2)
			{
				snake.addInSnakeDiracionQueue(Snake::RIGHT);
			}

		}
		break;

	case sf::Keyboard::Down:
		if (snake_diraction_last != Snake::UP && snake_diraction_last != Snake::DOWN)
		{
			if (snake.getSnakeDiractionQueue().size() < 2)
			{
				snake.addInSnakeDiracionQueue(Snake::DOWN);
			}

		}
		break;

	case sf::Keyboard::Left:
		if (snake_diraction_last != Snake::LEFT && snake_diraction_last != Snake::RIGHT)
		{
			if (snake.getSnakeDiractionQueue().size() < 2)
			{
				snake.addInSnakeDiracionQueue(Snake::LEFT);
			}

		}
		break;
	}
}

int main()
{
	srand(unsigned int(time(NULL)));
	Graphics graph(20, 41, 50, 32);
	Snake snake(graph);
	

	graph.addSnakeOnGameField(snake);

	while (graph.isOpen())
	{
		sf::Event event;
		while (graph.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				graph.close();
			}
				
			if (event.type == sf::Event::KeyPressed)
			{
				changeSnakeDiraction(snake, event);
			}
		}

		if (!snake.getSnakeDiractionQueue().empty()) 
		{
			snake.setSnakeDiraction();
			snake.changeSnakeDiractionQueue();
		}


		if (!graph.getGameParameters()->game_over and !graph.getGameParameters()->game_win)
		{
			snake.makeMove(graph);
		}
		

		graph.clear(sf::Color(183, 212, 166));
		graph.drawGameField();
		graph.drawScoreBar();
		

		if (graph.getGameParameters()->game_over)
		{
			graph.drawGameOver();
		}

		if (graph.getGameParameters()->game_win)
		{
			graph.drawGameWin();
		}

		if (!graph.getGameParameters()->game_over and graph.getGameParameters()->apples_remain < graph.getGameParameters()->max_amount_apples and !graph.getGameParameters()->door_open)
		{
			graph.getGameParameters()->timeout_apples--;
		}

		if (graph.getGameParameters()->timeout_apples == 0 and !graph.getGameParameters()->game_over and !graph.getGameParameters()->door_open)
		{
			graph.addAppleOnGameField();
			graph.getGameParameters()->timeout_apples = graph.getGameParameters()->max_timeout_apples;
			graph.getGameParameters()->apples_remain++;
			graph.getGameParameters()->apples_on_field++;
		}

		graph.display();
		sf::sleep(sf::milliseconds(100));
	}
	
	return 0;
}