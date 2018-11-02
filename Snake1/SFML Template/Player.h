#pragma once
#include <SFML\Graphics.hpp>
#include "ItemType.h"
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
	sf::Texture* getPlayerTexture() { return &texture; };
	sf::IntRect* getTextureRect() { return &textureRect; };
	void printPlayerState();
	void pickUpItem(ItemType* itemType);
	void resetPosition();
private:
	sf::Vector2i position;
	sf::Texture texture;
	sf::IntRect textureRect;
	int strength;
	int magic;
};

