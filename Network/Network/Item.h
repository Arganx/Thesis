#pragma once
#include <vector>
class Item
{
private:
	int calculateCharisma();
	int charisma;
	int dexterity;
	int calculateDexterity();
	int strength;
	int calculateStrength();
	int magica;
	int calculateMagica();
	int intelligence;
	int calculateIntelligence();
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
	double getStrength() { return strength; };
	double getMagica() { return magica; };
	double getIntelligence() { return intelligence; };
};

