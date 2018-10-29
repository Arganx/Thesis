#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Field.h"
#include "Player.h"
#include "Item.h"
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
private:
	Field*** fields;
	int size_x;
	int size_y;
	Player player;

};

