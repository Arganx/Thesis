#include "Board.h"
#include <iostream>


Board::Board(int sizeX,int sizeY,int windowSizeX,int windowSizeY, Player player)
	:player(player)
{
	this->size_x = sizeX;
	this->size_y = sizeY;
	int windowSize = std::min(windowSizeX,windowSizeY);
	int positionX = windowSizeX/2 - ((windowSize - 200) + (sizeX-1)*1)/2 ;
	int positionY = windowSizeY/2 - ((windowSize - 200)/size_x*sizeY + (sizeY - 1) * 1)/2;



	//Create fields
	fields = new Field**[size_y];
	for (int i = 0; i < size_y; i++)//hight
	{
		fields[i] = new Field*[size_x];
		for (int j = 0; j < size_x; j++)//width
		{
			fields[i][j] = new Field((windowSize -200)/size_x, positionX, positionY);
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
		fields[player.getPosition().x][player.getPosition().y]->setState(1);
	}


}


void Board::goRight()
{
	if (player.getPosition().x<size_x-1)
	{
		fields[player.getPosition().x][player.getPosition().y]->setState(0);
		player.moveRight();
		fields[player.getPosition().x][player.getPosition().y]->setState(1);
	}
}

void Board::goUp()
{
	if (player.getPosition().y>0)
	{
		fields[player.getPosition().x][player.getPosition().y]->setState(0);
		player.moveUp();
		fields[player.getPosition().x][player.getPosition().y]->setState(1);
	}
}

void Board::goDown()
{
	if (player.getPosition().y<size_y-1)
	{
		fields[player.getPosition().x][player.getPosition().y]->setState(0);
		player.moveDown();
		fields[player.getPosition().x][player.getPosition().y]->setState(1);
	}
}