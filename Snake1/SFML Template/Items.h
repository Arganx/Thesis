#pragma once
#include <list>
#include "ItemType.h"
#include "Board.h"
class Items
{
public:
	Items();
	~Items();

	ItemType* getItemTypes() { return types; };
	bool createItemOnBoard(int numberOnList,Board* board);

public:
	ItemType* types;
	std::list<Item> itemList;

};

