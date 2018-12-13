#include "ItemType.h"



ItemType::ItemType(std::string name,
	int size,
	int color,
	int agressivity,
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
	this->agressivity = agressivity;
	this->colorDifference = colorDifference;
	this->epicLevel = epicLevel;
	this->strength = calculateStrength(size,color, agressivity,colorDifference,epicLevel);
	this->magica = calculateMagica(size, color, agressivity, colorDifference, epicLevel);
	this->dexterity = calculateDexterity(size, color, agressivity, colorDifference, epicLevel);
	this->intelligence= calculateIntelligence(size, color, agressivity, colorDifference, epicLevel);
	this->charisma = calculateCharisma(size, color, agressivity, colorDifference, epicLevel);
	this->state = state;
}


ItemType::~ItemType()
{
}

int ItemType::calculateStrength(int size, int color, int agressivity, int colorDifference, int epicLevel)
{
	if (agressivity == 0)
	{
		return -2;
	}
	return agressivity+size- colorDifference-color;
}

int ItemType::calculateMagica(int size, int color, int agressivity, int colorDifference, int epicLevel)
{
	if (color == 3)
	{
		return epicLevel + colorDifference - size - agressivity+5 + color;
	}
	else if (color == 4)
	{
		return epicLevel + colorDifference - size - agressivity + 3 + color;
	}
	return epicLevel + colorDifference - size - agressivity+color;
}

int ItemType::calculateDexterity(int size, int color, int agressivity, int colorDifference, int epicLevel)
{
	return epicLevel - size + agressivity-colorDifference;
}

int ItemType::calculateIntelligence(int size, int color, int agressivity, int colorDifference, int epicLevel)
{
	if (color == 4 || color == 5)
	{
		return 5 + epicLevel - agressivity;
	}
	return epicLevel - agressivity;

}

int ItemType::calculateCharisma(int size, int color, int agressivity, int colorDifference, int epicLevel)
{
	return epicLevel - 3;
}


