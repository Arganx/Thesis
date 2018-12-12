#pragma once
#include <vector>
class Item
{
private:
	int calculateCharisma();
	int charisma;
	int dexterity;
	int calculateDexterity();
	int size;
	int color;
	int agressivity;
	int colorDifference;
	int epicLevel;
	std::vector<double> input;
	std::vector<double> result;
public:
	Item(int size, int color, int agressivity, int colorDifference, int epicLevel);
	~Item();
	std::vector<double> getInput() { return input; };
	std::vector<double> getResult() { return result; };
	double getCharisma() { return charisma; };
	double getDexterity() { return dexterity; };
};

