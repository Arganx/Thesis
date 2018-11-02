#include "Items.h"
#include "Item.h"
#include <iostream>

Items::Items()
{
	size = 2;
	types = new ItemType[size];
	types[0]= ItemType("Zwoj", 1, 1, 1, 1, 1, 1,"./src/textures/Daily Doodles - Pixel Art Asset Pack/magic07scroll.png",4);
	types[1] = ItemType("Miecz", 2, 2, 2, 2, 2, 2, "./src/textures/Daily Doodles - Pixel Art Asset Pack/weapon01crystalsword.png", 5);

}


Items::~Items()
{
}

ItemType * Items::getItemByState(int state)
{
	for (int i = 0; i < size; i++)
	{
		if (types[i].getState() == state)
		{
			return &types[i];
		}
	}
	return nullptr;
}

void Items::removeFromItemList(int x, int y)
{

	itemList.remove_if([x,y](Item i) { 
		if (i.getPosition().x == x && i.getPosition().y == y)
		{
			return true;
		}
		return false;
	});

}

