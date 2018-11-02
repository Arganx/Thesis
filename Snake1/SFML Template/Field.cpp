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

void Field::setState(int state,ItemType* itemType,sf::Texture* gate)
{
	this->itemtype = itemType;
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
	else if (state == 2)	//gate
	{
		sf::IntRect rect;
		rect.left = 0;
		rect.top = 0;
		rect.width = gate->getSize().x;
		rect.height = gate->getSize().y;
		this->body.setTexture(gate);
		this->body.setTextureRect(rect);

	}
	else if (state == 3)
	{
		this->body.setFillColor(sf::Color::Blue);
	}
	else if (state == 4)
	{
		//this->body.setFillColor(sf::Color::Black);
		sf::IntRect rect;
		rect.left = 0;
		rect.top = 0;
		rect.width = itemType->getTexture()->getSize().x;
		rect.height = itemType->getTexture()->getSize().y;
		this->body.setTexture(itemType->getTexture());
		this->body.setTextureRect(rect);

	}
	else if (state == 5)
	{
		sf::IntRect rect;
		rect.left = 0;
		rect.top = 0;
		rect.width = itemType->getTexture()->getSize().x;
		rect.height = itemType->getTexture()->getSize().y;
		this->body.setTexture(itemType->getTexture());
		this->body.setTextureRect(rect);
	}

}

void Field::setTexture(sf::Texture * texture, sf::IntRect* textureRect)
{
	player = texture;
	this->textureRect = textureRect;
}

