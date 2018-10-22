#include "Player.h"
#include <iostream>


Player::Player(int x, int y)
{
	this->position.x = x;
	this->position.y = y;
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


