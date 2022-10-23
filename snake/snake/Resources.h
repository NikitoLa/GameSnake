#pragma once

#include <algorithm>
#include <vector>
#include "BulderText.h"

class Resources
{
private:
	
public:
	
	~Resources();

	enum Textures
	{
		NONE = 0,
		APPLE = 1,
		WALL = 2,
		DOOR = 3,
		SNAKE = 4,
		UPARROW = 5
	};

	enum Sounds
	{
		COLLECT_POINT = 0,
		EXPLOSION = 1,
		EXPLOSION_2 = 2,
		MENU_NAVIGATE = 3,
		JINGLE_ACHIEVEMENT = 4,
		WIN_SOUND = 5,
	};

	enum Items
	{
		GAME_OVER = 0,
		SNAKE_TEXT = 1,
		APPLE_REMAIN = 2,
		YOU_WIN = 3
	};


protected:
	std::vector<std::string> name_of_images = { "assets\\Images\\none.png", "assets\\Images\\apple.png", "assets\\Images\\wall.png", "assets\\Images\\door.png", "assets\\Images\\snake.png", "assets\\Images\\uparrow.png" };
	std::vector<sf::Texture*> textures;
	std::vector<sf::Sprite> sprites;

	std::vector<std::string> name_of_sounds = { "assets\\sounds\\collect-point.wav", "assets\\sounds\\explosion.wav", "assets\\sounds\\explosion-02.wav", "assets\\sounds\\menu-navigate.wav", "assets\\sounds\\jingle-achievement.wav", "assets\\sounds\\tada.wav" };
	std::vector<sf::SoundBuffer*> soundbuffs;
	std::vector<sf::Sound> sounds;

	std::vector<std::pair<sf::Text*, sf::Font*>> items;

	sf::Image icon;
	
	Resources();

};