#include "BulderText.h"

BulderText::BulderText()
{
	text = new sf::Text();
	font = new sf::Font();
}

BulderText::~BulderText()
{
	delete text;
	delete font;
}

void BulderText::loadFont(std::string path)
{
	font->loadFromFile(path);
}

void BulderText::setFont()
{
	text->setFont(*font);
}

void BulderText::setCharSize(int size)
{
	text->setCharacterSize(size);
}

void BulderText::setColor(sf::Color color)
{
	text->setFillColor(color);
}

void BulderText::setString(std::string str)
{
	text->setString(str);
}

void BulderText::setPosition(int x, int y)
{
	text->setPosition(x, y);
}

sf::Text* BulderText::getText()
{
	return text;
}

std::pair<sf::Text*, sf::Font*> BulderText::returnPair()
{
	sf::Text* tmp_text = text;
	sf::Font* tmp_font = font;
	text = new sf::Text();
	font = new sf::Font();

	return std::pair<sf::Text*, sf::Font*>(tmp_text, tmp_font);
}
