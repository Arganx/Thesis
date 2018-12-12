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

Item::~Item()
{
}
