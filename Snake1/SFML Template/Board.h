#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Field.h"
#include "Player.h"
#include "Item.h"
#include "Items.h"
#include "PathFinding.h"
#include "MLP.h"
#include "PNN.h"
class Board
{
public:
	Board(int sizeX, int sizeY, int windowSizeX, int windowSizeY,Player player,bool mlp,bool training,int mode);
	~Board();
	void draw(sf::RenderWindow& window);
	void goLeft();
	void goRight();
	void goUp();
	void goDown();
	int getSizeX() { return size_x; };
	int getSizeY() { return size_y; };
	bool checkField(int x, int y);
	void setItem(Item* item);
	bool createItemOnBoard(int numberOnList);
	void resetBoard(int numberofItems);
	void setDoor();
	bool getPlayerCanMove() { return playerCanMove; };
	void setPlayerCanMove(bool canMove) { this->playerCanMove = canMove; };
	Player getPlayer() { return player; };
	Player* getRealPlayer() { return &player; };
	bool getAI() { return ai; };
	void setAI(bool ai) { this->ai = ai; };
	bool getTraining() { return training; };
	void setTraining(bool train) { this->training = train; };
private:
	Field*** fields;
	int size_x;
	int size_y;
	Player player;
	Items* items;
	void checkIfItem();
	void createItems(int numberOfItems);
	sf::Texture gateTexture;
	PathFinding* pathFinding;
	bool playerCanMove;
	bool ai;
	bool training;
	std::list<Item> evaluate(std::list<Item> list);
	bool classify(Item* item);
	MLP strengthNetwork;
	MLP dexterityNetwork;
	MLP intelligenceNetwork;
	MLP magicaNetwork;
	MLP charismaNetwork;
	bool mlp;
	PNN strengthPNN;
	PNN dexterityPNN;
	PNN intelligencePNN;
	PNN magicaPNN;
	PNN charismaPNN;
	void createNewPNN();
	void createStrengthPNN();
	void createDexterityPNN();
	void createMagicaPNN();
	void createIntelligencePNN();
	void createCharismaPNN();
	std::vector<ItemType*> pnnItemTypePoints;
	void addToPnnItemTypePoints(ItemType* type);
	int mode;
};

