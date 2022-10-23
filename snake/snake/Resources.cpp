#include "Resources.h"

Resources::Resources()
{
	for (int i = 0; i < name_of_images.size(); i++)
	{
		textures.push_back(new sf::Texture);
		sprites.push_back(sf::Sprite());
		textures[i]->loadFromFile(name_of_images[i]);
		sprites[i].setTexture(*textures[i]);
	}

	for (int i = 0; i < name_of_sounds.size(); i++)
	{
		soundbuffs.push_back(new sf::SoundBuffer);
		sounds.push_back(sf::Sound());
		soundbuffs[i]->loadFromFile(name_of_sounds[i]);
		sounds[i].setBuffer(*soundbuffs[i]);
	}

	icon.loadFromFile("assets\\snake_image.png");

}

Resources::~Resources()
{
	for (int i = 0; i < name_of_images.size(); i++)
	{
		delete textures[i];
	}

	for (int i = 0; i < name_of_sounds.size(); i++)
	{
		delete soundbuffs[i];
	}

	for (int i = 0; i < items.size(); i++)
	{
		delete items[i].first;
		delete items[i].second;
	}
}

