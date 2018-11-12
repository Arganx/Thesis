#pragma once
#include "ItemType.h"
#include "SFML/Graphics.hpp"
class Item
{
public:
	Item(ItemType* type, int x,int y);
	~Item();
	sf::Vector2i getPosition() { return position; };
	ItemType* getType() { return type; };
private:
	ItemType* type;
	sf::Vector2i position;

};

