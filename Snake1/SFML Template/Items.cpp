#include "Items.h"
#include "Item.h"
#include <iostream>

Items::Items()
{
	types = new ItemType[2];
	types[0]= ItemType("Zwoj", 1, 1, 1, 1, 1, 1,"./src/textures/Daily Doodles - Pixel Art Asset Pack/magic07scroll.png",4);
	types[1] = ItemType("Miecz", 2, 2, 2, 2, 2, 2, "./src/textures/Daily Doodles - Pixel Art Asset Pack/weapon01crystalsword.png", 5);

}


Items::~Items()
{
}

bool Items::createItemOnBoard(int numberOnList, Board* board)//TODO limit number of loop iterations
{
	srand(time(NULL));
	int x = -1;
	int y = -1;
	while (!board->checkField(x, y))
	{
		x = rand() % board->getSizeX();
		y = rand() % board->getSizeY();
	}
	std::cout << "Wybrane pozycje to: " << x << " oraz " << y << std::endl;
	Item* itemOne = new Item(&types[numberOnList], x, y);
	itemList.push_front(*itemOne);

	board->setItem(itemOne);


	return false;
}
