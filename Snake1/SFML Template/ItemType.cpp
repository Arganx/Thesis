#include "ItemType.h"



ItemType::ItemType(std::string name,
	int size,
	int color,
	int shape,
	int colorDifference,
	int epicLevel,
	int strength,
	std::string path,
	int state)
{

	if (!texture.loadFromFile(path))
	{
		//TODO throw exception
	}
	this->name = name;
	this->size = size;
	this->color = color;
	this->shape = shape;
	this->colorDifference = colorDifference;
	this->epicLevel = epicLevel;
	this->strength = strength;
	this->state = state;
}


ItemType::~ItemType()
{
}
