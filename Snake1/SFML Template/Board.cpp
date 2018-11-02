#include "Board.h"
#include <iostream>


Board::Board(int sizeX,int sizeY,int windowSizeX,int windowSizeY, Player player)
	:player(player)
{
	items = new Items;
	this->size_x = sizeX;
	this->size_y = sizeY;
	int windowSize = std::min(windowSizeX,windowSizeY);
	int positionX = windowSizeX/2 - ((windowSize - 200) + (sizeX-1)*1)/2 ;
	int positionY = windowSizeY/2 - ((windowSize - 200)/size_x*sizeY + (sizeY - 1) * 1)/2;

	if (!gateTexture.loadFromFile("./src/textures/gate.png"))
	{
		//TODO throw error
	}


	//Create fields
	fields = new Field**[size_y];
	for (int i = 0; i < size_y; i++)//hight
	{
		fields[i] = new Field*[size_x];
		for (int j = 0; j < size_x; j++)//width
		{
			fields[i][j] = new Field((windowSize -200)/size_x, positionX, positionY);
			fields[i][j]->setTexture(this->player.getPlayerTexture(),this->player.getTextureRect());
			positionY += (windowSize -200) / size_y +1;
			
		}
		positionY = windowSizeY / 2 - ((windowSize - 200) / size_x*sizeY + (sizeY - 1) * 1) / 2;
		positionX += (windowSize -200) / size_x + 1;
	}


	//for (int i = 0; i < size_x; i++)
	//{
	//	for (int j = 0; j < size_y; j++)
	//	{
	//		std::cout << fields[i][j]->getBody().getPosition().x << " ";
	//	}
	//	std::cout << std::endl;
	//}
	fields[player.getPosition().x][player.getPosition().y]->setState(1);
	createItems(10);
	setDoor();
}



Board::~Board()
{
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			delete fields[i][j];
		}
		delete[] fields[i];
	}
	delete [] fields;
	delete items;
}

void Board::draw(sf::RenderWindow & window)
{
	for (int i = 0; i < size_y; i++)
	{
		for (int j = 0; j < size_x; j++)
		{
			window.draw(fields[i][j]->getBody());
		}
	}
}



void Board::goLeft()
{
	if (player.getPosition().x>0)
	{
		fields[player.getPosition().x][player.getPosition().y]->setState(0);
		player.moveLeft();
		checkIfItem();
		fields[player.getPosition().x][player.getPosition().y]->setState(1);
	}


}


void Board::goRight()
{
	if (player.getPosition().x<size_x-1)
	{
		fields[player.getPosition().x][player.getPosition().y]->setState(0);
		player.moveRight();
		checkIfItem();
		fields[player.getPosition().x][player.getPosition().y]->setState(1);
	}
}

void Board::goUp()
{
	if (player.getPosition().y>0)
	{
		fields[player.getPosition().x][player.getPosition().y]->setState(0);
		player.moveUp();
		checkIfItem();
		fields[player.getPosition().x][player.getPosition().y]->setState(1);
	}
}

void Board::goDown()
{
	if (player.getPosition().y<size_y-1)
	{
		fields[player.getPosition().x][player.getPosition().y]->setState(0);
		player.moveDown();
		checkIfItem();
		fields[player.getPosition().x][player.getPosition().y]->setState(1);
	}
}

bool Board::checkField(int x, int y)
//Check if field is empty
{
	if (x<0 || x>size_x - 1 || y<0 || y>size_y - 1)
	{
		return false;
	}
	if (fields[x][y]->getState() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Board::setItem(Item* item)
{
	fields[item->getPosition().x][item->getPosition().y]->setState(item->getType()->getState(),item->getType());
}

bool Board::createItemOnBoard(int numberOnList)//TODO limit number of loop iterations
{
	srand(time(NULL));
	int x = -1;
	int y = -1;
	while (!this->checkField(x, y))
	{
		x = rand() % this->getSizeX();
		y = rand() % this->getSizeY();
	}
	std::cout << "Wybrane pozycje to: " << x << " oraz " << y << std::endl;
	Item* itemOne = new Item(&items->getItemTypes()[numberOnList], x, y);
	items->itemList.push_front(*itemOne);

	this->setItem(itemOne);


	return false;
}

void Board::resetBoard(int numberofItems)
{
	items->itemList.clear();
	player.resetPosition();
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			fields[i][j]->setState(0);
		}
	}
	createItems(numberofItems);
	setDoor();

}

void Board::setDoor()
{
	srand(time(NULL));
	int x = -1;
	int y = -1;
	while (!this->checkField(x, y))
	{
		x = rand() % this->getSizeX();
		y = rand() % this->getSizeY();
	}
	std::cout << "Wybrana pozycja drzwi to: " << x << " oraz " << y << std::endl;
	fields[x][y]->setState(2,NULL,&gateTexture);
}

void Board::checkIfItem()
{
	int state = fields[player.getPosition().x][player.getPosition().y]->getState();
	if (state == 2)
	{
		this->resetBoard(10);
	}
	else if (state)	//ifNotEmpty
	{
		ItemType* type = items->getItemByState(state);
		player.pickUpItem(type);
		items->removeFromItemList(player.getPosition().x, player.getPosition().y);
		player.printPlayerState();
	}
}

void Board::createItems(int numberOfItems)
{
	//Create items
	srand(time(NULL));
	int itemNumber = 0;
	for (int i = 0; i < numberOfItems; i++)
	{
		itemNumber = rand() % this->items->getSize();
		this->createItemOnBoard(itemNumber);
	}
}
