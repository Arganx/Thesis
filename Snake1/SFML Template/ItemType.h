#pragma once
#include <string>
#include "SFML\Graphics.hpp"
class ItemType
{

public:
	ItemType() {};
	ItemType(
	std::string name,
	int size,
	int color,
	int shape,
	int colorDifference,
	int epicLevel,
	int strength,
	std::string path,
	int state);
	~ItemType();

	sf::Texture* getTexture() { return &texture; };
	int getState() { return state; };
private:

	sf::Texture texture;

	std::string name;

	int state;

	int size;
	int color;
	int shape;
	int colorDifference;
	int epicLevel;

	int strength;
	//int dexterity;
	//int armor;
	//int magic;
	//int health;
};

