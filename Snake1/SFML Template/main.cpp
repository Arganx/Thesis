#include <SFML\Graphics.hpp>
#include "Board.h"
#include "Items.h"
#include <list>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280,720),"SFML Template");
	Player player(2,2);
	Board board(3,3, 1280, 720,player);
	window.setFramerateLimit(30);
	Items* items = new Items();
	//ItemType test = items->getItemTypeList().back();
	
	items->createItemOnBoard(1, &board);
	items->createItemOnBoard(0, &board);
	items->createItemOnBoard(1, &board);
	items->createItemOnBoard(1, &board);
	
	while (window.isOpen())
	{
		//handle events

		sf::Event mainEvent;
		while (window.pollEvent(mainEvent))
		{
			switch (mainEvent.type)
			{
			case sf::Event::EventType::Closed:
				window.close();
				break;
			case sf::Event::EventType::KeyPressed:
				switch (mainEvent.key.code)
				{
				case sf::Keyboard::A:
					board.goLeft();
					break;
				case sf::Keyboard::D:
					board.goRight();
					break;
				case sf::Keyboard::W:
					board.goUp();
					break;
				case sf::Keyboard::S:
					board.goDown();
					break;
				default:
					break;
				}
			}
		}

		//update game

		window.clear();

		board.draw(window);

		//draw objects

		window.display();
	}
}