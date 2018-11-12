#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Field.h"
#include "Player.h"
#include "Item.h"
#include "Items.h"
#include "PathFinding.h"
class Board
{
public:
	Board(int sizeX, int sizeY, int windowSizeX, int windowSizeY,Player player);
	~Board();
	void draw(sf::RenderWindow& window);
	void goLeft();
	void goRight();
	void goUp();
	void goDown();
	int getSizeX() { return size_x; };
	int getSizeY() { return size_y; };
	bool checkField(int x, int y);
	void setItem(Item* item);
	bool createItemOnBoard(int numberOnList);
	void resetBoard(int numberofItems);
	void setDoor();
	bool getPlayerCanMove() { return playerCanMove; };
	void setPlayerCanMove(bool canMove) { this->playerCanMove = canMove; };
	Player getPlayer() { return player; };
	Player* getRealPlayer() { return &player; };
private:
	Field*** fields;
	int size_x;
	int size_y;
	Player player;
	Items* items;
	void checkIfItem();
	void createItems(int numberOfItems);
	sf::Texture gateTexture;
	PathFinding* pathFinding;
	bool playerCanMove;

};

