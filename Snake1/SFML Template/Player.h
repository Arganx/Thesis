#pragma once
#include <SFML\Graphics.hpp>
class Player
{
public:
	Player(int x,int y);
	~Player();
	sf::Vector2i getPosition() { return position; };
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
private:
	sf::Vector2i position;
};

