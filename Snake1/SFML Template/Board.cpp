#include "Board.h"
#include <iostream>
#include <thread>

Board::Board(int sizeX,int sizeY,int windowSizeX,int windowSizeY, Player player)
	:player(player)
{
	items = new Items;
	pathFinding = new PathFinding;
	playerCanMove = true;
	ai = false;
	training = false;
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
	setDoor();
	setDoor();
	setDoor();
	createItems(10);
	//std::cout << "List before" << std::endl << std::endl;
	//for (auto v : items->itemList)
	//{
	//	std::cout << "Name: " << v.getType()->getName() << "\n";
	//	std::cout << "x: " << v.getPosition().x << " y:" << v.getPosition().y << "\n";
	//}
		
	items->sortListByDistance(player.getPosition());
	//std::cout << "List after" << std::endl << std::endl;
	//for (auto v : items->itemList)
	//{
	//	std::cout << "Name: " << v.getType()->getName() << "\n";
	//	std::cout << "x: " << v.getPosition().x << " y:" << v.getPosition().y << "\n";
	//}
	//setDoor();
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
	delete pathFinding;
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
	while (!this->checkField(x, y) || !this->checkField(x+1, y) || !this->checkField(x - 1, y) || !this->checkField(x, y+1) || !this->checkField(x, y-1) || !this->checkField(x + 1, y+1) || !this->checkField(x + 1, y-1) || !this->checkField(x - 1, y-1) || !this->checkField(x - 1, y+1))
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
	while (!this->checkField(x, y) || !this->checkField(x + 1, y) || !this->checkField(x - 1, y) || !this->checkField(x, y + 1) || !this->checkField(x, y - 1) || !this->checkField(x + 1, y + 1) || !this->checkField(x + 1, y - 1) || !this->checkField(x - 1, y - 1) || !this->checkField(x - 1, y + 1))
	{
		x = rand() % this->getSizeX();
		y = rand() % this->getSizeY();
	}
	std::cout << "Wybrana pozycja drzwi to: " << x << " oraz " << y << std::endl;
	fields[x][y]->setState(2,NULL,&gateTexture);
}


void rightBlocked(Board* board)
{
	board->goUp();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goRight();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goRight();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goDown();
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void upBlocked(Board* board)
{
	board->goRight();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goUp();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goUp();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goLeft();
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void leftBlocked(Board* board)
{
	board->goUp();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goLeft();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goLeft();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goDown();
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void downBlocked(Board* board)
{
	board->goRight();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goDown();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goDown();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goLeft();
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void threadFunction(Board* board,sf::Vector2i distance)
{
	//TODO omijanie drzwi, przedmioty musza miec pusta przestrzen dookola
	board->setPlayerCanMove(false);
	std::this_thread::sleep_for(std::chrono::microseconds(10));
	board->setPlayerCanMove(false);



	std::cout << "Thread" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	if (distance.x > 0)
	{
		for (int i = 0; i < distance.x-1; i++)
		{
			if (board->checkField(board->getRealPlayer()->getPosition().x+1, board->getRealPlayer()->getPosition().y))
			{
				//std::cout << "X: " << board->getRealPlayer()->getPosition().x + 1 << " Y: " << board->getRealPlayer()->getPosition().y << " clear" <<std::endl;
				board->goRight();
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
			else
			{
				rightBlocked(board);
				i++;
				//std::cout << "rightBlocked x: " << board->getRealPlayer()->getPosition().x + 1 << " y: " <<board->getRealPlayer()->getPosition().y << std::endl;
			}
		}
		//Prezdmiot na zakrecie
		if (distance.y != 0 && !board->checkField(board->getRealPlayer()->getPosition().x + 1, board->getRealPlayer()->getPosition().y))
		{
			if (distance.y > 0)	//w dol
			{
				board->goDown();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				board->goRight();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				distance.y--;
			}
			else
			{
				board->goUp();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				board->goRight();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				distance.y++;
			}
		}
		else
		{
			board->goRight();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
	else if(distance.x<0)
	{

		for (int i = 0; i < (distance.x*-1)-1; i++)
		{
			if (board->checkField(board->getRealPlayer()->getPosition().x - 1, board->getRealPlayer()->getPosition().y))
			{
				board->goLeft();
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
			else
			{
				leftBlocked(board);
				i++;
				//std::cout << "leftBlocked" << std::endl;
			}

		}
		if (distance.y != 0 && !board->checkField(board->getRealPlayer()->getPosition().x - 1, board->getRealPlayer()->getPosition().y))
		{
			if (distance.y > 0)	//w dol
			{
				board->goDown();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				board->goLeft();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				distance.y--;
			}
			else
			{
				board->goUp();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				board->goLeft();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				distance.y++;
			}
		}
		else
		{
			board->goLeft();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}

	if (distance.y > 0)
	{
		for (int i = 0; i < distance.y-1; i++)
		{
			if (board->checkField(board->getRealPlayer()->getPosition().x, board->getRealPlayer()->getPosition().y + 1))
			{
				board->goDown();
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
			else
			{
				downBlocked(board);
				i++;
				//std::cout << "downBlocked" << std::endl;
			}

		}
		board->goDown();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	else if(distance.y <0)
	{
		for (int i = 0; i < (distance.y*-1)-1; i++)
		{
			if (board->checkField(board->getRealPlayer()->getPosition().x, board->getRealPlayer()->getPosition().y - 1))
			{
				board->goUp();
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
			else
			{
				upBlocked(board);
				i++;
				std::cout << "UpBlocked" << std::endl;
			}

		}
		board->goUp();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	std::cout << "End" << std::endl;


	board->setPlayerCanMove(true);
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
		//Podnosze item
		ItemType* type = items->getItemByState(state);
		player.pickUpItem(type);
		items->removeFromItemList(player.getPosition().x, player.getPosition().y);
		player.printPlayerState();
		//Znalezienie drogi do nastepnego itemu
		if (ai)
		{
			items->sortListByDistance(player.getPosition());
			if (!items->getItemList().empty())
			{
				sf::Vector2i distance = pathFinding->findPath(player.getPosition(), items->getItemList().front().getPosition());
				/*int x = getPlayer().getPosition().x;
				int y = getPlayer().getPosition().y;*/
				//Player* p = getRealPlayer();
				std::thread t(threadFunction, this, distance);
				t.detach();
			}
			//TODO thread going to the gate
		}
		
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

