#pragma once
#include <SFML\Graphics.hpp>
class Field
{
public:
	Field(int size, int positionX, int positionY);
	~Field();
	sf::RectangleShape getBody() { return body; };
	int getState() { return state; };
	void setState(int state);
	void setTexture(sf::Texture* texture,sf::IntRect* textureRect);
private:
	int state;
	sf::RectangleShape body;
	sf::Texture* player;
	sf::IntRect* textureRect;
};

