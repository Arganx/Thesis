#include "PathFinding.h"
#include <iostream>


PathFinding::PathFinding()
{
}


PathFinding::~PathFinding()
{
}

sf::Vector2i PathFinding::findPath(sf::Vector2i player, sf::Vector2i item)
{
	std::cout << "Find path for Player: " << player.x << " " << player.y << "\nItem: " << item.x << " " << item.y << std::endl;
	int diffX = item.x - player.x;
	int diffY = item.y - player.y;
	return sf::Vector2i(diffX,diffY);

}

