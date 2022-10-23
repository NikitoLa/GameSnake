#include "Graphics.h"

Graphics::Graphics(int y, int x, int score_bar, int cell) : sf::RenderWindow(sf::VideoMode(x* cell, y* cell + score_bar), "MySnake")
{
	setIcon(32, 32, icon.getPixelsPtr());

	score_bar_height = score_bar;
	field_size_x = x;
	field_size_y = y;
	cell_size = cell;
	window_width = field_size_x * cell_size;
	window_hight = field_size_y * cell_size;
	parameters = new GameParameters;
	
	field.push_back(std::vector<int>());
	for (int j = 0; j < field_size_y; j++)
	{
		for (int i = 0; i < field_size_x; i++)
		{
			if (j == 0 and i == (field_size_x / 2))
			{
				field[j].push_back(FIELD_CELL_TYPE_DOOR);
			}
			else
			{
				field[j].push_back(FIELD_CELL_TYPE_NONE);
			}
			
		}
		field.push_back(std::vector<int>());
	}


	for (int i = 0; i < field_size_x; i++)
	{
		if (!(i == (field_size_x / 2)))
		{
			field[0][i] = FIELD_CELL_TYPE_WALL;
		}
		
		field[field_size_y - 1][i] = FIELD_CELL_TYPE_WALL;
	}

	for (int j = 1; j < field_size_y - 1; j++)
	{
		field[j][0] = FIELD_CELL_TYPE_WALL;
		field[j][field_size_x - 1] = FIELD_CELL_TYPE_WALL;

	}

	loadResours();
}

Graphics::~Graphics()
{
	delete parameters;
}

void Graphics::loadResours()
{

	//setVolume();

	BulderText bulder;

	bulder.loadFont("assets\\fonts\\BigOldBoldy.ttf");
	bulder.setFont();
	bulder.setString("GAME OVER");
	bulder.setCharSize(120);
	bulder.setColor(sf::Color::Red);
	bulder.setPosition((window_width - bulder.getText()->getLocalBounds().width) / 2, (window_hight - bulder.getText()->getLocalBounds().height + score_bar_height) / 2);
	items.emplace_back(bulder.returnPair());

	bulder.loadFont("assets\\fonts\\BigfatScript.otf");
	bulder.setFont();
	bulder.setString("Snake");
	bulder.setCharSize(30);
	bulder.setColor(sf::Color::Black);
	bulder.setPosition(20, 10);
	items.emplace_back(bulder.returnPair());

	bulder.loadFont("assets\\fonts\\BigfatScript.otf"); // apples remain
	bulder.setFont();
	bulder.setCharSize(32);
	bulder.setColor(sf::Color::Black);
	items.emplace_back(bulder.returnPair());

	bulder.loadFont("assets\\fonts\\BigOldBoldy.ttf");
	bulder.setFont();
	bulder.setString("YOU WIN");
	bulder.setCharSize(120);
	bulder.setColor(sf::Color::Green);
	bulder.setPosition((window_width - bulder.getText()->getLocalBounds().width) / 2, (window_hight - bulder.getText()->getLocalBounds().height + score_bar_height) / 2);
	items.emplace_back(bulder.returnPair());

	/*font_menu.loadFromFile("assets\\fonts\\BigOldBoldy-dEjR.ttf");
	for (int i = 0; i < main_menu_items.size(); i++)
	{
		text_main_menu_items.emplace_back(sf::Text());
		text_main_menu_items.back().setString(main_menu_items.at(i));
		text_main_menu_items.back().setFont(font_menu);
		text_main_menu_items.back().setCharacterSize(30);
	}

	for (int i = 0; i < settings_menu_items.size(); i++)
	{
		text_settings_menu_items.emplace_back(sf::Text());
		text_settings_menu_items.back().setString(settings_menu_items.at(i));
		text_settings_menu_items.back().setFont(font_menu);
		text_settings_menu_items.back().setCharacterSize(30);
	}*/

}

Point Graphics::getMidleOfField()
{
	return Point(field_size_y / 2, field_size_x / 2);
}

void Graphics::drawGameOver()
{
	draw(*items[Resources::Items::GAME_OVER].first);
}

void Graphics::drawGameWin()
{
	draw(*items[Resources::Items::YOU_WIN].first);
}

void Graphics::drawScoreBar()
{
	draw(*items[Resources::Items::SNAKE_TEXT].first);
	items[Resources::Items::APPLE_REMAIN].first->setString("Remain apples: " + std::to_string(parameters->apples_remain));
	items[Resources::Items::APPLE_REMAIN].first->setPosition(window_width - items[Resources::Items::APPLE_REMAIN].first->getLocalBounds().width - 30, 10);
	draw(*items[Resources::Items::APPLE_REMAIN].first);

	/*text_score.setString("Score: " + std::to_string(score));
	text_score.setPosition(window_width - text_score.getLocalBounds().width - 50, 10);
	.draw(text_score);*/
}

void Graphics::addAppleOnGameField()
{
	Apple apple_position = getEmptyCellForApple();
	if (apple_position.getCoordinatesOfApple().getX() != -1)
	{
		field[apple_position.getCoordinatesOfApple().getY()][apple_position.getCoordinatesOfApple().getX()] = FIELD_CELL_TYPE_APPLE;
	}
}

Graphics::GameParameters* Graphics::getGameParameters()
{
	return parameters;
}

Apple Graphics::getEmptyCellForApple()
{
	int empty_cell_count = 0;
	for (int j = 0; j < field_size_y; j++)
	{
		for (int i = 0; i < field_size_x; i++)
		{
			if (field[j][i] == FIELD_CELL_TYPE_NONE)
			{
				empty_cell_count++;
			}
		}
	}

	int target_empty_cell_index = rand() % empty_cell_count;
	int empty_cell_index = 0;
	for (int j = 0; j < field_size_y; j++)
	{
		for (int i = 0; i < field_size_x; i++)
		{
			if (field[j][i] == FIELD_CELL_TYPE_NONE)
			{
				if (target_empty_cell_index == empty_cell_index)
				{
					return Apple(j,i);
				}
				empty_cell_index++;
			}
		}
	}
	return Apple(-1,-1);
}

void Graphics::addSnakeOnGameField(Snake& snake)
{
	for (int i = 0; i < snake.getLenght(); i++)
	{
		field[snake.getCoordinates().getY()][snake.getCoordinates().getX() - i] = snake.getLenght() - i;
	}

	addAppleOnGameField();
}

void Graphics::drawGameField()
{
	for (int j = 0; j < field_size_y; j++)
	{
		for (int i = 0; i < field_size_x; i++)
		{
			sf::Vector2f vec(float(i * cell_size), float(j * cell_size + score_bar_height));
			switch (field[j][i])
			{
			case FIELD_CELL_TYPE_NONE:
			{
				sprites[Resources::Textures::NONE].setPosition(vec);
				draw(sprites[Resources::NONE]);
				break;
			}
				

			case FIELD_CELL_TYPE_APPLE:
			{
				sprites[Resources::Textures::APPLE].setPosition(vec);
				draw(sprites[Resources::Textures::APPLE]);
				break;
			}
				
			case FIELD_CELL_TYPE_WALL:
			{
				sprites[Resources::Textures::WALL].setPosition(vec);
				draw(sprites[Resources::Textures::WALL]);
				
				break; 
			}

			case FIELD_CELL_TYPE_DOOR:
			{
				sprites[Resources::Textures::DOOR].setPosition(vec);
				draw(sprites[Resources::Textures::DOOR]);
				break;
			}

			case FIELD_CELL_TYPE_UP_ARROW:
			{
				sprites[Resources::Textures::UPARROW].setPosition(vec);
				draw(sprites[Resources::Textures::UPARROW]);
				break;
			}
				

			default:
			{
				sprites[Resources::Textures::SNAKE].setPosition(vec);
				draw(sprites[Resources::Textures::SNAKE]);
			}
			
			}
		}
	}
}

