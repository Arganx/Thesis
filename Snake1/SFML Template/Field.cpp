#include "Field.h"
#include <random>
#include "Player.h"


Field::Field(int size,int positionX,int positionY)
{
	body = sf::RectangleShape(sf::Vector2f((float)size, (float)size));
	this->body.setFillColor(sf::Color::White);
	this->body.setPosition((float)positionX, (float)positionY);
	this->state = 0;
	
}


Field::~Field()
{
}

void Field::setState(int state)
{
	this->state = state;
	if (state == 0)
	{
		this->body.setFillColor(sf::Color::White);
		this->body.setTexture(NULL);
	}
	else if (state == 1)
	{
		//this->body.setFillColor(sf::Color::Red);
		this->body.setTexture(player);
		this->body.setTextureRect(*textureRect);
	}
	else if (state == 2)
	{
		this->body.setFillColor(sf::Color::Green);
	}
	else if (state == 3)
	{
		this->body.setFillColor(sf::Color::Blue);
	}
	else if (state == 4)
	{
		this->body.setFillColor(sf::Color::Black);
	}

}

void Field::setTexture(sf::Texture * texture, sf::IntRect* textureRect)
{
	player = texture;
	this->textureRect = textureRect;
}

