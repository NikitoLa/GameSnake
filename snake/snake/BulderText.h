#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class BulderText
{
public:
	BulderText();
	~BulderText();

	void loadFont(std::string);
	void setFont();
	void setCharSize(int);
	void setColor(sf::Color);
	void setString(std::string);
	void setPosition(int, int);
	sf::Text* getText();
	std::pair<sf::Text*, sf::Font*> returnPair();

private:
	sf::Text* text;
	sf::Font* font;
};

