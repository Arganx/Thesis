#pragma once
#include <string>
class Item
{
public:
	Item();
	~Item();
private:
	std::string name;

	int size;
	int color;
	int shape;
	int colorDifference;
	int epicLevel;

	int strength;
	int dexterity;
	int armor;
	int magic;
	int health;
};

