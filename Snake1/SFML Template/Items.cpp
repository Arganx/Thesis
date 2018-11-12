#include "Items.h"
#include "Item.h"
#include <iostream>
#include <math.h> 
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

void Items::sortListByDistance(sf::Vector2i player)
{
	struct ItemComparator
	{
		sf::Vector2i p;
		// Compare 2 Player objects using name
		bool operator ()(Item & item1, Item & item2)
		{
			if (item1.getPosition() == item2.getPosition())
				return false;;
			double distance1 = sqrt(pow(item1.getPosition().x-p.x,2.0) + pow(item1.getPosition().y - p.y, 2.0));
			double distance2 = sqrt(pow(item2.getPosition().x - p.x, 2.0) + pow(item2.getPosition().y - p.y, 2.0));
			return distance1 < distance2;

		}
	};
	ItemComparator comperator;
	comperator.p = player;
	itemList.sort(comperator);
}