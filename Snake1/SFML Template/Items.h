#pragma once
#include <list>
#include "ItemType.h"
#include "Item.h"
class Items
{
public:
	Items();
	~Items();

	ItemType* getItemTypes() { return types; };
	ItemType* getItemByState(int state);
	void removeFromItemList(int x, int y);
	int getSize() { return size; };

public:
	ItemType* types;
	std::list<Item> itemList;
private:
	int size;

};

