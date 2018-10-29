#include "Item.h"



Item::Item(ItemType* type, int x, int y)
{
	this->type = type;
	this->position.x = x;
	this->position.y = y;
}


Item::~Item()
{
}
