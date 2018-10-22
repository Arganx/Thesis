#include "Field.h"
#include <random>
#include "Player.h"


Field::Field(int size,int positionX,int positionY)
{
	this->body.setSize(sf::Vector2f((float)size, (float)size));
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
	}
	else if (state == 1)
	{
		this->body.setFillColor(sf::Color::Red);
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

