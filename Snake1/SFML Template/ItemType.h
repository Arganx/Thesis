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
	int agressivity,
	int colorDifference,
	int epicLevel,
	std::string path,
	int state);
	~ItemType();

	sf::Texture* getTexture() { return &texture; };
	int getState() { return state; };
	std::string getName() { return name; };
	int getStrength() { return strength; };
	int getMagica() { return magica; };
	int getDexterity() { return dexterity; };
	int getIntelligence() { return intelligence; };
	int getCharisma() { return charisma; };
private:

	sf::Texture texture;

	std::string name;

	int state;

	int size;
	int color;
	int agressivity;
	int colorDifference;
	int epicLevel;

	int strength;
	int magica;
	int dexterity;
	int intelligence;
	int charisma;

	int calculateStrength(int size,int color,int agressivity,int colorDifference,int epicLevel);
	int calculateMagica(int size, int color, int agressivity, int colorDifference, int epicLevel);
	int calculateDexterity(int size, int color, int agressivity, int colorDifference, int epicLevel);
	int calculateIntelligence(int size, int color, int agressivity, int colorDifference, int epicLevel);
	int calculateCharisma(int size, int color, int agressivity, int colorDifference, int epicLevel);
	//int dexterity;
	//int armor;
	//int magic;
	//int health;
};

