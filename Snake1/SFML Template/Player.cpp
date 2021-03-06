#include "Player.h"
#include <iostream>


Player::Player(int x, int y)
{
	this->position.x = x;
	this->position.y = y;

	if (!texture.loadFromFile("./src/textures/player.png"))
	{
		//TODO error
	}
	else
	{
		this->textureRect.left = 20;
		this->textureRect.top = 18;
		this->textureRect.width = 20;
		this->textureRect.height = 19;
		this->strength = 0;
		this->magic = 0;
	}
}


Player::~Player()
{
}

void Player::moveLeft()
{
	this->position.x--;
}

void Player::moveRight()
{
	position.x++;
}

void Player::moveUp()
{
	position.y--;
}

void Player::moveDown()
{
	position.y++;
}

void Player::printPlayerState()
{
	std::cout << "Player: strength - " << strength << " magic - " << magic << std::endl;
}

void Player::pickUpItem(ItemType * itemType)
{
	std::cout << "Picked up " << itemType->getName() << std::endl;
	strength += itemType->getStrength();
}

void Player::resetPosition()
{
	position.x = 0;
	position.y = 0;
}


