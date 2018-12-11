#include "ItemType.h"



ItemType::ItemType(std::string name,
	int size,
	int color,
	int shape,
	int colorDifference,
	int epicLevel,
	std::string path,
	int state)
{

	if (!texture.loadFromFile(path))
	{
		//TODO throw exception
	}
	this->name = name;
	this->size = size;
	this->color = color;//0-white 1-red 2-green 3-blue 4-yellow 5-purple 6-orange
	this->shape = shape;
	this->colorDifference = colorDifference;
	this->epicLevel = epicLevel;
	this->strength = calculateStrength(size,color,shape,colorDifference,epicLevel);
	this->state = state;
}


ItemType::~ItemType()
{
}

int ItemType::calculateStrength(int size, int color, int shape, int colorDifference, int epicLevel)
{
	return 3 * size +2*epicLevel - shape - colorDifference;
}
