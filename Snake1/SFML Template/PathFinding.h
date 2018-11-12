#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Item.h"
class PathFinding
{
public:
	PathFinding();
	~PathFinding();

	sf::Vector2i findPath(sf::Vector2i player, sf::Vector2i item);
};

