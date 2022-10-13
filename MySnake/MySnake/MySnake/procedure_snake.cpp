#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>

#define FIELD_CELL_TYPE_APPLE -1
#define FIELD_CELL_TYPE_WALL -2
#define FIELD_CELL_TYPE_NONE 0
#define SNAKE_DIRACTION_UP 0
#define SNAKE_DIRACTION_RIGHT 1
#define SNAKE_DIRACTION_DOWN 2
#define SNAKE_DIRACTION_LEFT 3
#define MENU_ITEM_START "Start new game"
#define MENU_ITEM_SETTINGS "Settings"
#define MENU_ITEM_QUIT "Quit"
#define MENU_ITEM_BACK "Back to main menu"
#define MENU_ITEM_VOLUME "Volume"
#define MENU_ITEM_RESUME "Resume game"
#define MENU_MAIN 0
#define MENU_SETTINGS 1


const int field_size_x = 35;
const int field_size_y = 25;
const int cell_size = 32;
const int score_bar_height = 50;
const int window_width = field_size_x * cell_size;
const int window_hight = field_size_y * cell_size + score_bar_height;
int field[field_size_y][field_size_x];

int snake_position_x;
int snake_position_y;
int snake_lenght;
int snake_diraction = SNAKE_DIRACTION_RIGHT;
int score = 0;
bool game_over = false;
bool game_started = false;
int game_over_timeout = 0;
bool game_paused = true;
int current_menu = MENU_MAIN;
int current_main_menu_item_index = 0;
int current_settings_menu_item_index = 0;
int seettings_volume = 50;

sf::Texture snake_texture;
sf::Sprite snake_head;

sf::Texture none_texture;
sf::Sprite none;

sf::Texture apple_texture;
sf::Sprite apple;

sf::Texture wall_texture;
sf::Sprite wall;

sf::SoundBuffer sb_ate_apple;
sf::Sound sound_ate_apple;

sf::SoundBuffer sb_died_against_the_wall;
sf::Sound sound_died_against_the_wall;

sf::SoundBuffer sb_ate_himself;
sf::Sound sound_ate_himself;

sf::SoundBuffer sb_menu_navigate;
sf::Sound sound_menu_navigate;

sf::SoundBuffer sb_game_start;
sf::Sound sound_game_start;


sf::Font font_score;
sf::Text text_score;

sf::Font font_title;
sf::Text text_title;

sf::Font font_game_over;
sf::Text text_game_over;

sf::Font font_menu;
std::vector<sf::Text> text_main_menu_items;
std::vector<std::string> main_menu_items = { MENU_ITEM_START, MENU_ITEM_SETTINGS, MENU_ITEM_QUIT };

std::vector<sf::Text> text_settings_menu_items;
std::vector<std::string> settings_menu_items = { MENU_ITEM_BACK, MENU_ITEM_VOLUME};


int getRandomEmptyCell()
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
					return j * field_size_x + i;
				}
				empty_cell_index++;
			}
		}
	}
	return -1;
}

void addApple()
{
	int apple_position = getRandomEmptyCell();
	if (apple_position != -1)
	{
		field[apple_position / field_size_x][apple_position % field_size_x] = FIELD_CELL_TYPE_APPLE;
	}
}

void clearField()
{
	for (int j = 0; j < field_size_y; j++)
	{
		for (int i = 0; i < field_size_x; i++)
		{
			field[j][i] = FIELD_CELL_TYPE_NONE;
		}
	}

	for (int i = 0; i < snake_lenght; i++)
	{
		field[snake_position_y][snake_position_x - i] = snake_lenght - i;
	}

	for (int i = 0; i < field_size_x; i++)
	{
		if (i < 5 || field_size_x - i - 1 < 5)
		{
			field[0][i] = FIELD_CELL_TYPE_WALL;
			field[field_size_y - 1][i] = FIELD_CELL_TYPE_WALL;
		}
	}

	for (int j = 1; j < field_size_y - 1; j++)
	{
		if (j < 5 || field_size_y - j - 1 < 5)
		{
			field[j][0] = FIELD_CELL_TYPE_WALL;
			field[j][field_size_x - 1] = FIELD_CELL_TYPE_WALL;
		}

	}
	addApple();
}

void setVolume()
{
	sound_menu_navigate.setVolume(seettings_volume);
	sound_ate_apple.setVolume(seettings_volume);
	sound_died_against_the_wall.setVolume(seettings_volume);
	sound_game_start.setVolume(seettings_volume);
	sound_ate_himself.setVolume(seettings_volume);
}

void initGame()
{
	srand(time(NULL));
	clearField();
	snake_texture.loadFromFile("assets\\Images\\snake.png");
	snake_head.setTexture(snake_texture);

	none_texture.loadFromFile("assets\\Images\\none.png");
	none.setTexture(none_texture);

	apple_texture.loadFromFile("assets\\Images\\apple.png");
	apple.setTexture(apple_texture);

	wall_texture.loadFromFile("assets\\Images\\wall.png");
	wall.setTexture(wall_texture);

	sb_ate_apple.loadFromFile("assets\\sounds\\cmake-build-debug_sounds_collect-point-01.wav");
	sound_ate_apple.setBuffer(sb_ate_apple);
	
	sb_died_against_the_wall.loadFromFile("assets\\sounds\\cmake-build-debug_sounds_explosion-00.wav");
	sound_died_against_the_wall.setBuffer(sb_died_against_the_wall);
	

	sb_ate_himself.loadFromFile("assets\\sounds\\cmake-build-debug_sounds_explosion-02.wav");
	sound_ate_himself.setBuffer(sb_ate_himself);

	sb_menu_navigate.loadFromFile("assets\\sounds\\cmake-build-debug_sounds_menu-navigate-02.wav");
	sound_menu_navigate.setBuffer(sb_menu_navigate);
	

	sb_game_start.loadFromFile("assets\\sounds\\cmake-build-debug_sounds_jingle-achievement-01.wav");
	sound_game_start.setBuffer(sb_game_start);
	
	setVolume();

	font_score.loadFromFile("assets\\fonts\\BigfatScript-2OvA8.otf");
	text_score.setFont(font_score);
	text_score.setCharacterSize(32);
	text_score.setFillColor(sf::Color::Black);

	font_title.loadFromFile("assets\\fonts\\BigfatScript-2OvA8.otf");
	text_title.setFont(font_title);
	text_title.setString("Snake");
	text_title.setCharacterSize(30);
	text_title.setFillColor(sf::Color::Black);
	text_title.setPosition(20, 10);

	font_game_over.loadFromFile("assets\\fonts\\BigOldBoldy-dEjR.ttf");
	text_game_over.setFont(font_game_over);
	text_game_over.setString("GAME OVER");
	text_game_over.setCharacterSize(120);
	text_game_over.setFillColor(sf::Color::Red);
	text_game_over.setPosition((window_width - text_game_over.getLocalBounds().width) / 2, (window_hight - text_game_over.getLocalBounds().height + score_bar_height) / 2);

	font_menu.loadFromFile("assets\\fonts\\BigOldBoldy-dEjR.ttf");
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
	}

}

void startGame()
{
	snake_position_x = field_size_x / 2;
	snake_position_y = field_size_y / 2;
	snake_lenght = 4;
	snake_diraction = SNAKE_DIRACTION_RIGHT;
	score = 0;

	game_started = true;
	game_over = false;
	game_paused = false;
	clearField();
	sound_game_start.play();

}

void finishGame()
{
	game_over_timeout = 20;
	game_over = true;
	game_paused = true;
	current_main_menu_item_index = 0;
}

void drawField(sf::RenderWindow& window)
{
	for (int j = 0; j < field_size_y; j++)
	{
		for (int i = 0; i < field_size_x; i++)
		{
			switch (field[j][i])
			{
			case FIELD_CELL_TYPE_NONE:
				none.setPosition(float(i * cell_size), float(j * cell_size + score_bar_height));
				window.draw(none);
				break;

			case FIELD_CELL_TYPE_APPLE:
				apple.setPosition(float(i * cell_size), float(j * cell_size + score_bar_height));
				window.draw(apple);
				break;

			case FIELD_CELL_TYPE_WALL:
				wall.setPosition(float(i * cell_size), float(j * cell_size + score_bar_height));
				window.draw(wall);
				break;

			default:
				snake_head.setPosition(float(i * cell_size), float(j * cell_size + score_bar_height));
				window.draw(snake_head);
			}
		}
	}
}

void drawScoreBar(sf::RenderWindow& window)
{
	
	window.draw(text_title);

	text_score.setString("Score: " + std::to_string(score));
	text_score.setPosition(window_width - text_score.getLocalBounds().width - 50, 10);
	window.draw(text_score);
}

void drawMainMenu(sf::RenderWindow& window)
{
	float const menu_padding_horizontal = 40;
	float const menu_paddind_vertical = 30;
	float const menu_item_interval = 20;

	float current_menu_item_offset_y = 0;
	float menu_item_max_width = 0;

	for (int i = 0; i < main_menu_items.size(); i++)
	{

		if (main_menu_items.at(i) == MENU_ITEM_START)
		{
			if (!game_over && game_started)
			{
				text_main_menu_items.at(i).setString(MENU_ITEM_RESUME);
			}

			else
			{
				text_main_menu_items.at(i).setString(MENU_ITEM_START);
			}
			
		}

		text_main_menu_items.at(i).setPosition(0, current_menu_item_offset_y);
		text_main_menu_items.at(i).setFillColor(current_main_menu_item_index == i ? sf::Color(224, 224, 224) : sf::Color(128, 128, 128));
		current_menu_item_offset_y += text_main_menu_items.at(i).getLocalBounds().height + menu_item_interval;
		menu_item_max_width = std::max(menu_item_max_width, text_main_menu_items.at(i).getLocalBounds().width);
		
		
	}

	float const menu_width = menu_item_max_width + menu_padding_horizontal * 2;
	float const menu_hight = current_menu_item_offset_y - menu_item_interval + menu_paddind_vertical * 2;

	float const menu_position_x = (window_width - menu_width) / 2;
	float const menu_position_y = (window_hight - menu_hight) / 2;

	sf::RectangleShape menu_rect(sf::Vector2f(menu_width, menu_hight));
	menu_rect.setPosition(menu_position_x, menu_position_y);
	menu_rect.setFillColor(sf::Color(0, 0, 0, 224));
	window.draw(menu_rect);

	for (int i = 0; i < text_main_menu_items.size(); i++)
	{
		text_main_menu_items.at(i).move(menu_position_x + menu_padding_horizontal, menu_position_y + menu_paddind_vertical);
		window.draw(text_main_menu_items.at(i));
	}
}

void drawSettingsMenu(sf::RenderWindow& window)
{
	float const menu_padding_horizontal = 40;
	float const menu_paddind_vertical = 30;
	float const menu_item_interval = 20;

	float current_menu_item_offset_y = 0;
	float menu_item_max_width = 0;

	for (int i = 0; i < settings_menu_items.size(); i++)
	{
		if (settings_menu_items.at(i) == MENU_ITEM_VOLUME)
		{
			text_settings_menu_items.at(i).setString(settings_menu_items.at(i) + ": " + std::to_string(seettings_volume));
		}

		text_settings_menu_items.at(i).setPosition(0, current_menu_item_offset_y);
		text_settings_menu_items.at(i).setFillColor(current_settings_menu_item_index == i ? sf::Color(224, 224, 224) : sf::Color(128, 128, 128));
		current_menu_item_offset_y += text_settings_menu_items.at(i).getLocalBounds().height + menu_item_interval;
		menu_item_max_width = std::max(menu_item_max_width, text_settings_menu_items.at(i).getLocalBounds().width);
		
	}

	float const menu_width = menu_item_max_width + menu_padding_horizontal * 2;
	float const menu_hight = current_menu_item_offset_y - menu_item_interval + menu_paddind_vertical * 2;

	float const menu_position_x = (window_width - menu_width) / 2;
	float const menu_position_y = (window_hight - menu_hight) / 2;

	sf::RectangleShape menu_rect(sf::Vector2f(menu_width, menu_hight));
	menu_rect.setPosition(menu_position_x, menu_position_y);
	menu_rect.setFillColor(sf::Color(0, 0, 0, 224));
	window.draw(menu_rect);

	for (int i = 0; i < text_settings_menu_items.size(); i++)
	{
		text_settings_menu_items.at(i).move(menu_position_x + menu_padding_horizontal, menu_position_y + menu_paddind_vertical);
		window.draw(text_settings_menu_items.at(i));
	}
}

void growSnake()
{
	int empty_cell_count = 0;
	for (int j = 0; j < field_size_y; j++)
	{
		for (int i = 0; i < field_size_x; i++)
		{
			if (field[j][i] > FIELD_CELL_TYPE_NONE)
			{
				field[j][i]++;
			}
		}
	}
}

void makeMove()
{
	switch (snake_diraction)
	{
	case SNAKE_DIRACTION_UP:
		snake_position_y--;
		if (snake_position_y < 0)
		{
			snake_position_y = field_size_y - 1;
		}
		break;

	case SNAKE_DIRACTION_RIGHT:
		snake_position_x++;
		if (snake_position_x > field_size_x - 1)
		{
			snake_position_x = 0;
		}
		break;

	case SNAKE_DIRACTION_DOWN:
		snake_position_y++;
		if (snake_position_y > field_size_y - 1)
		{
			snake_position_y = 0;
		}
		break;

	case SNAKE_DIRACTION_LEFT:
		snake_position_x--;
		if (snake_position_x < 0)
		{
			snake_position_x = field_size_x - 1;
		}
		break;

	default:
		break;
	}

	if (field[snake_position_y][snake_position_x] != FIELD_CELL_TYPE_NONE)
	{
		switch (field[snake_position_y][snake_position_x])
		{
		case FIELD_CELL_TYPE_APPLE:
			sound_ate_apple.play();
			score++;
			snake_lenght++;
			growSnake();
			addApple();
			break;

		case FIELD_CELL_TYPE_WALL:
			sound_died_against_the_wall.play();
			finishGame();
			break;

		default:
			if (field[snake_position_y][snake_position_x] > 1)
			{
				sound_ate_himself.play();
				finishGame();
			}
		}
	}

	if (!game_over)
	{
		
		for (int j = 0; j < field_size_y; j++)
		{
			for (int i = 0; i < field_size_x; i++)
			{
				if (field[j][i] > FIELD_CELL_TYPE_NONE)
				{
					field[j][i]--;
				}

			}
			field[snake_position_y][snake_position_x] = snake_lenght;
		}
	}

}

int main()
{

	initGame();
	sf::RenderWindow window(sf::VideoMode(window_width, window_hight), "MySnake");

	std::vector<int> snake_diraction_queue;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (game_paused)
				{
					if (game_over_timeout == 0)
					{
						if (current_menu == MENU_MAIN)
						{
							switch (event.key.code)
							{
							case sf::Keyboard::Up:
								current_main_menu_item_index--;
								sound_menu_navigate.play();
								if (current_main_menu_item_index < 0)
								{
									current_main_menu_item_index = text_main_menu_items.size() - 1;
								}
								break;

							case sf::Keyboard::Down:
								current_main_menu_item_index++;
								sound_menu_navigate.play();
								if (current_main_menu_item_index > text_main_menu_items.size() - 1)
								{
									current_main_menu_item_index = 0;
								}
								break;

							case sf::Keyboard::Enter:
							{
								sound_menu_navigate.play();
								if (main_menu_items.at(current_main_menu_item_index) == MENU_ITEM_START)
								{
									if (!game_over && game_started)
									{
										game_paused = false;
									}

									else
									{
										startGame();
									}
									
								}

								if (main_menu_items.at(current_main_menu_item_index) == MENU_ITEM_SETTINGS)
								{
									current_menu = MENU_SETTINGS;
									current_settings_menu_item_index = 0;
								}

								if (main_menu_items.at(current_main_menu_item_index) == MENU_ITEM_QUIT)
								{
									window.close();
								}
								break;
							}

							case sf::Keyboard::Escape:
								sound_menu_navigate.play();
								if (!game_over && game_started)
								{
									game_paused = false;
								}

								break;

							default:
								break;
							}
						}
						
						else if (current_menu == MENU_SETTINGS)
						{
							switch (event.key.code)
							{
							case sf::Keyboard::Up:
								current_settings_menu_item_index--;
								sound_menu_navigate.play();
								if (current_settings_menu_item_index < 0)
								{
									current_settings_menu_item_index = text_settings_menu_items.size() - 1;
								}
								break;

							case sf::Keyboard::Down:
								current_settings_menu_item_index++;
								sound_menu_navigate.play();
								if (current_settings_menu_item_index > text_settings_menu_items.size() - 1)
								{
									current_settings_menu_item_index = 0;
								}
								break;

							case sf::Keyboard::Left:
								
								if (settings_menu_items.at(current_settings_menu_item_index) == MENU_ITEM_VOLUME)
								{
									if (seettings_volume > 0)
									{
										seettings_volume -= 5;
										setVolume();
										sound_menu_navigate.play();
									}
									
								}
								break;

							case sf::Keyboard::Right:
								
								if (settings_menu_items.at(current_settings_menu_item_index) == MENU_ITEM_VOLUME)
								{
									if (seettings_volume < 100)
									{
										seettings_volume += 5;
										setVolume();
										sound_menu_navigate.play();
									}
								}
								break;

							case sf::Keyboard::Enter:
							{
								sound_menu_navigate.play();
								if (settings_menu_items.at(current_settings_menu_item_index) == MENU_ITEM_BACK)
								{
									current_menu = MENU_MAIN;
								}								
								break;
							}

							case sf::Keyboard::Escape:
								sound_menu_navigate.play();
								current_menu = MENU_MAIN;
								break;

							}
						}
					}
					

					else
					{
						game_over_timeout = 0;
					}
				}

				else
				{
					int snake_diraction_last = snake_diraction_queue.empty() ? snake_diraction : snake_diraction_queue.at(0);
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						if (snake_diraction_last != SNAKE_DIRACTION_UP && snake_diraction_last != SNAKE_DIRACTION_DOWN)
						{
							if (snake_diraction_queue.size() < 2)
							{
								snake_diraction_queue.insert(snake_diraction_queue.begin(), SNAKE_DIRACTION_UP);
							}

						}
						break;

					case sf::Keyboard::Right:
						if (snake_diraction_last != SNAKE_DIRACTION_RIGHT && snake_diraction_last != SNAKE_DIRACTION_LEFT)
						{
							if (snake_diraction_queue.size() < 2)
							{
								snake_diraction_queue.insert(snake_diraction_queue.begin(), SNAKE_DIRACTION_RIGHT);
							}

						}
						break;

					case sf::Keyboard::Down:
						if (snake_diraction_last != SNAKE_DIRACTION_DOWN && snake_diraction_last != SNAKE_DIRACTION_UP)
						{
							if (snake_diraction_queue.size() < 2)
							{
								snake_diraction_queue.insert(snake_diraction_queue.begin(), SNAKE_DIRACTION_DOWN);
							}

						}
						break;

					case sf::Keyboard::Left:
						if (snake_diraction_last != SNAKE_DIRACTION_LEFT && snake_diraction_last != SNAKE_DIRACTION_RIGHT)
						{
							if (snake_diraction_queue.size() < 2)
							{
								snake_diraction_queue.insert(snake_diraction_queue.begin(), SNAKE_DIRACTION_LEFT);
							}

						}
						break;

					case sf::Keyboard::Escape:
						game_paused = true;
						break;
					}
				}
				
			}

		}
		if (!snake_diraction_queue.empty())
		{
			snake_diraction = snake_diraction_queue.back();
			snake_diraction_queue.pop_back();
		}

		if (!game_paused)
		{
			makeMove();
		}

		
	
		window.clear(sf::Color(183, 212, 166));
		drawField(window);
		drawScoreBar(window);

		if (game_over)
		{
			window.draw(text_game_over);
			if (game_over_timeout > 0)
			{
				game_over_timeout--;
			}
		}

		if (game_paused && game_over_timeout == 0)
		{
			switch (current_menu)
			{
			case MENU_MAIN:
				drawMainMenu(window);
				break;

			case MENU_SETTINGS:
				drawSettingsMenu(window);
				break;
			}
			
		}

		window.display();
		sf::sleep(sf::milliseconds(100));
	}

	return 0;
}