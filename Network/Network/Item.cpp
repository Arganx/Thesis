#include "Item.h"



Item::Item(int size, int color, int agressivity, int colorDifference, int epicLevel)
{
	this->size = size;
	this->color = color;//0-white 1-red 2-green 3-blue 4-yellow 5-purple 6-orange
	this->agressivity = agressivity;
	this->colorDifference = colorDifference;
	this->epicLevel = epicLevel;
	this->charisma = calculateCharisma();
	this->dexterity = calculateDexterity();
	this->strength = calculateStrength();
	this->magica = calculateMagica();
	this->intelligence = calculateIntelligence();
	input.push_back((double)size/6.);
	input.push_back((double)color/6.);
	input.push_back((double)agressivity/6.);
	input.push_back((double)colorDifference/6.);
	input.push_back((double)epicLevel/6.);
	result.push_back((double)dexterity/12.);
}


int Item::calculateCharisma()
{
	return epicLevel - 3;
}

int Item::calculateDexterity()
{
	return epicLevel - size + agressivity - colorDifference;
}

int Item::calculateStrength()
{
	if (agressivity == 0)
	{
		return -2;
	}
	return agressivity + size - colorDifference - color;
}

int Item::calculateMagica()
{
	if (color == 3)
	{
		return epicLevel + colorDifference - size - agressivity + 5 + color;
	}
	else if (color == 4)
	{
		return epicLevel + colorDifference - size - agressivity + 3 + color;
	}
	return epicLevel + colorDifference - size - agressivity + color;
}

int Item::calculateIntelligence()
{
	if (color == 4 || color == 5)
	{
		return 5 + epicLevel - agressivity;
	}
	return epicLevel - agressivity;
}

Item::~Item()
{
}
