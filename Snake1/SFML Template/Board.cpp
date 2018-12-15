#include "Board.h"
#include <iostream>
#include <thread>
#include <vector>



Board::Board(int sizeX,int sizeY,int windowSizeX,int windowSizeY, Player player,bool mlp,bool training,int mode)
	:player(player)
{
	items = new Items;
	pathFinding = new PathFinding;
	playerCanMove = true;
	ai = false;
	this->mode = mode;
	this->training = training;
	this->mlp = mlp;
	if (mlp)
	{
		//MLP
		std::vector<int> tmp;
		tmp.push_back(20);
		tmp.push_back(10);
		this->strengthNetwork = MLP(5, 1, 2, tmp, "StrengthWeights");
		tmp.clear();
		tmp.push_back(25);
		tmp.push_back(20);
		tmp.push_back(15);
		this->magicaNetwork = MLP(5, 1, 3, tmp, "MagicaWeights");
		tmp.clear();
		tmp.push_back(20);
		tmp.push_back(10);
		this->dexterityNetwork = MLP(5,1,2,tmp,"DexterityWeights");
		tmp.clear();
		tmp.push_back(10);
		tmp.push_back(5);
		this->charismaNetwork = MLP(5,1,2,tmp,"CharismaWeights");
		tmp.clear();
		tmp.push_back(25);
		tmp.push_back(20);
		tmp.push_back(15);
		this->intelligenceNetwork = MLP(5,2,3,tmp,"IntelligenceWeights");
		if (!training)
		{
			strengthNetwork.loadWeights();
			magicaNetwork.loadWeights();
			dexterityNetwork.loadWeights();
			charismaNetwork.loadWeights();
			intelligenceNetwork.loadWeights();
		}
	}
	else
	{
		//PNN
		std::vector<std::vector<std::vector<double>>> vector;
		strengthPNN = PNN(5, vector);
		dexterityPNN = PNN(5, vector);
		magicaPNN = PNN(5, vector);
		intelligencePNN = PNN(5, vector);
		charismaPNN = PNN(5, vector);
		if (!training)
		{
			strengthPNN.loadClasses("pnnStrength");
			dexterityPNN.loadClasses("pnnDexterity");
			magicaPNN.loadClasses("pnnMagica");
			intelligencePNN.loadClasses("pnnIntelligence");
			charismaPNN.loadClasses("ppnCharisma");
		}
	}
	this->size_x = sizeX;
	this->size_y = sizeY;
	int windowSize = std::min(windowSizeX,windowSizeY);
	int positionX = windowSizeX/2 - ((windowSize - 200) + (sizeX-1)*1)/2 ;
	int positionY = windowSizeY/2 - ((windowSize - 200)/size_x*sizeY + (sizeY - 1) * 1)/2;

	if (!gateTexture.loadFromFile("./src/textures/gate.png"))
	{
		//TODO throw error
	}


	//Create fields
	fields = new Field**[size_y];
	for (int i = 0; i < size_y; i++)//hight
	{
		fields[i] = new Field*[size_x];
		for (int j = 0; j < size_x; j++)//width
		{
			fields[i][j] = new Field((windowSize -200)/size_x, positionX, positionY);
			fields[i][j]->setTexture(this->player.getPlayerTexture(),this->player.getTextureRect());
			positionY += (windowSize -200) / size_y +1;
			
		}
		positionY = windowSizeY / 2 - ((windowSize - 200) / size_x*sizeY + (sizeY - 1) * 1) / 2;
		positionX += (windowSize -200) / size_x + 1;
	}


	//for (int i = 0; i < size_x; i++)
	//{
	//	for (int j = 0; j < size_y; j++)
	//	{
	//		std::cout << fields[i][j]->getBody().getPosition().x << " ";
	//	}
	//	std::cout << std::endl;
	//}
	fields[player.getPosition().x][player.getPosition().y]->setState(1);
	setDoor();
	setDoor();
	setDoor();
	createItems(10);
	//std::cout << "List before" << std::endl << std::endl;
	//for (auto v : items->itemList)
	//{
	//	std::cout << "Name: " << v.getType()->getName() << "\n";
	//	std::cout << "x: " << v.getPosition().x << " y:" << v.getPosition().y << "\n";
	//}
		
	items->sortListByDistance(player.getPosition());
	//std::cout << "List after" << std::endl << std::endl;
	//for (auto v : items->itemList)
	//{
	//	std::cout << "Name: " << v.getType()->getName() << "\n";
	//	std::cout << "x: " << v.getPosition().x << " y:" << v.getPosition().y << "\n";
	//}
	//setDoor();
}



Board::~Board()
{
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			delete fields[i][j];
		}
		delete[] fields[i];
	}
	delete [] fields;
	delete items;
	delete pathFinding;
}

void Board::draw(sf::RenderWindow & window)
{
	for (int i = 0; i < size_y; i++)
	{
		for (int j = 0; j < size_x; j++)
		{
			window.draw(fields[i][j]->getBody());
		}
	}
}



void Board::goLeft()
{
	if (player.getPosition().x>0)
	{
		fields[player.getPosition().x][player.getPosition().y]->setState(0);
		player.moveLeft();
		checkIfItem();
		fields[player.getPosition().x][player.getPosition().y]->setState(1);
	}


}


void Board::goRight()
{
	if (player.getPosition().x<size_x-1)
	{
		fields[player.getPosition().x][player.getPosition().y]->setState(0);
		player.moveRight();
		checkIfItem();
		fields[player.getPosition().x][player.getPosition().y]->setState(1);
	}
}

void Board::goUp()
{
	if (player.getPosition().y>0)
	{
		fields[player.getPosition().x][player.getPosition().y]->setState(0);
		player.moveUp();
		checkIfItem();
		fields[player.getPosition().x][player.getPosition().y]->setState(1);
	}
}

void Board::goDown()
{
	if (player.getPosition().y<size_y-1)
	{
		fields[player.getPosition().x][player.getPosition().y]->setState(0);
		player.moveDown();
		checkIfItem();
		fields[player.getPosition().x][player.getPosition().y]->setState(1);
	}
}

bool Board::checkField(int x, int y)
//Check if field is empty
{
	if (x<0 || x>size_x - 1 || y<0 || y>size_y - 1)
	{
		return false;
	}
	if (fields[x][y]->getState() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Board::setItem(Item* item)
{
	fields[item->getPosition().x][item->getPosition().y]->setState(item->getType()->getState(),item->getType());
}

bool Board::createItemOnBoard(int numberOnList)//TODO limit number of loop iterations
{
	srand(time(NULL));
	int x = -1;
	int y = -1;
	while (!this->checkField(x, y) || !this->checkField(x+1, y) || !this->checkField(x - 1, y) || !this->checkField(x, y+1) || !this->checkField(x, y-1) || !this->checkField(x + 1, y+1) || !this->checkField(x + 1, y-1) || !this->checkField(x - 1, y-1) || !this->checkField(x - 1, y+1))
	{
		x = rand() % this->getSizeX();
		y = rand() % this->getSizeY();
	}
	std::cout << "Wybrane pozycje to: " << x << " oraz " << y << std::endl;
	Item* itemOne = new Item(&items->getItemTypes()[numberOnList], x, y);
	items->itemList.push_front(*itemOne);

	this->setItem(itemOne);


	return false;
}

void Board::resetBoard(int numberofItems)
{
	items->itemList.clear();
	player.resetPosition();
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			fields[i][j]->setState(0);
		}
	}
	createItems(numberofItems);
	setDoor();

}

void Board::setDoor()
{
	srand(time(NULL));
	int x = -1;
	int y = -1;
	while (!this->checkField(x, y) || !this->checkField(x + 1, y) || !this->checkField(x - 1, y) || !this->checkField(x, y + 1) || !this->checkField(x, y - 1) || !this->checkField(x + 1, y + 1) || !this->checkField(x + 1, y - 1) || !this->checkField(x - 1, y - 1) || !this->checkField(x - 1, y + 1))
	{
		x = rand() % this->getSizeX();
		y = rand() % this->getSizeY();
	}
	std::cout << "Wybrana pozycja drzwi to: " << x << " oraz " << y << std::endl;
	fields[x][y]->setState(2,NULL,&gateTexture);
}


void rightBlocked(Board* board)
{
	board->goUp();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goRight();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goRight();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goDown();
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void upBlocked(Board* board)
{
	board->goRight();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goUp();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goUp();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goLeft();
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void leftBlocked(Board* board)
{
	board->goUp();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goLeft();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goLeft();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goDown();
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void downBlocked(Board* board)
{
	board->goRight();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goDown();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goDown();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	board->goLeft();
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void threadFunction(Board* board,sf::Vector2i distance)
{
	//TODO omijanie drzwi, przedmioty musza miec pusta przestrzen dookola
	board->setPlayerCanMove(false);
	std::this_thread::sleep_for(std::chrono::microseconds(10));
	board->setPlayerCanMove(false);



	std::cout << "Thread" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	if (distance.x > 0)
	{
		for (int i = 0; i < distance.x-1; i++)
		{
			if (board->checkField(board->getRealPlayer()->getPosition().x+1, board->getRealPlayer()->getPosition().y))
			{
				//std::cout << "X: " << board->getRealPlayer()->getPosition().x + 1 << " Y: " << board->getRealPlayer()->getPosition().y << " clear" <<std::endl;
				board->goRight();
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
			else
			{
				rightBlocked(board);
				i++;
				//std::cout << "rightBlocked x: " << board->getRealPlayer()->getPosition().x + 1 << " y: " <<board->getRealPlayer()->getPosition().y << std::endl;
			}
		}
		//Prezdmiot na zakrecie
		if (distance.y != 0 && !board->checkField(board->getRealPlayer()->getPosition().x + 1, board->getRealPlayer()->getPosition().y))
		{
			if (distance.y > 0)	//w dol
			{
				board->goDown();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				board->goRight();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				distance.y--;
			}
			else
			{
				board->goUp();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				board->goRight();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				distance.y++;
			}
		}
		else
		{
			board->goRight();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
	else if(distance.x<0)
	{

		for (int i = 0; i < (distance.x*-1)-1; i++)
		{
			if (board->checkField(board->getRealPlayer()->getPosition().x - 1, board->getRealPlayer()->getPosition().y))
			{
				board->goLeft();
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
			else
			{
				leftBlocked(board);
				i++;
				//std::cout << "leftBlocked" << std::endl;
			}

		}
		if (distance.y != 0 && !board->checkField(board->getRealPlayer()->getPosition().x - 1, board->getRealPlayer()->getPosition().y))
		{
			if (distance.y > 0)	//w dol
			{
				board->goDown();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				board->goLeft();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				distance.y--;
			}
			else
			{
				board->goUp();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				board->goLeft();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				distance.y++;
			}
		}
		else
		{
			board->goLeft();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}

	if (distance.y > 0)
	{
		for (int i = 0; i < distance.y-1; i++)
		{
			if (board->checkField(board->getRealPlayer()->getPosition().x, board->getRealPlayer()->getPosition().y + 1))
			{
				board->goDown();
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
			else
			{
				downBlocked(board);
				i++;
				//std::cout << "downBlocked" << std::endl;
			}

		}
		board->goDown();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	else if(distance.y <0)
	{
		for (int i = 0; i < (distance.y*-1)-1; i++)
		{
			if (board->checkField(board->getRealPlayer()->getPosition().x, board->getRealPlayer()->getPosition().y - 1))
			{
				board->goUp();
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
			else
			{
				upBlocked(board);
				i++;
				std::cout << "UpBlocked" << std::endl;
			}

		}
		board->goUp();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	std::cout << "End" << std::endl;


	board->setPlayerCanMove(true);
}

void Board::checkIfItem()
{
	int state = fields[player.getPosition().x][player.getPosition().y]->getState();
	if (state == 2)
	{
		this->resetBoard(10);
	}
	else if (state)	//ifNotEmpty
	{
		//Podnosze item
		ItemType* type = items->getItemByState(state);
		player.pickUpItem(type);
		items->removeFromItemList(player.getPosition().x, player.getPosition().y);
		player.printPlayerState();
		//Znalezienie drogi do nastepnego itemu
		if (ai)
		{
			items->sortListByDistance(player.getPosition());
			if (!items->getItemList().empty())
			{
				std::list<Item> list = evaluate(items->getItemList());
				if (!list.empty())
				{
					if (training && !mlp)
					{
						addToPnnItemTypePoints(type);
					}
					sf::Vector2i distance = pathFinding->findPath(player.getPosition(), list.front().getPosition());
					/*int x = getPlayer().getPosition().x;
					int y = getPlayer().getPosition().y;*/
					//Player* p = getRealPlayer();
					std::thread t(threadFunction, this, distance);
					t.detach();
				}
			}
			else if(!mlp && training)
			{
				
				createNewPNN();
				std::cout << "Koniec Levela" << std::endl;
				strengthPNN.saveClasses("pnnStrength");
				dexterityPNN.saveClasses("pnnDexterity");
				magicaPNN.saveClasses("pnnMagica");
				intelligencePNN.saveClasses("pnnIntelligence");
				charismaPNN.saveClasses("ppnCharisma");

			}
			//TODO thread going to the gate
		}
		
	}
}

void Board::createItems(int numberOfItems)
{
	//Create items
	srand(time(NULL));
	int itemNumber = 0;
	for (int i = 0; i < numberOfItems; i++)
	{
		itemNumber = rand() % this->items->getSize();
		this->createItemOnBoard(itemNumber);
	}
}

std::list<Item> Board::evaluate(std::list<Item> list)
{
	if (training)
	{
		return list;
	}
	std::vector<Item> it;
	int size = list.size();
	for (int i = 0; i < size; i++)
	{
		it.push_back(list.front());
		list.pop_front();
	}
	for (int i = it.size()-1; i >= 0; i--)
	{
		if (classify(&it[i]))//wynik sieci delete
		{
			it.erase(it.begin() + i);
		}
	}
	std::list<Item> list2;
	for (int i = 0; i < it.size(); i++)
	{
		list2.push_back(it[i]);
	}
	
	return list2;
}

bool Board::classify(Item * item)
{
	if (mlp)
	{
		std::vector<double> input;
		input.push_back(item->getType()->getSize()/6.);
		input.push_back(item->getType()->getColor()/6.);
		input.push_back(item->getType()->getAgressivity()/6.);
		input.push_back(item->getType()->getColorDifference()/6.);
		input.push_back(item->getType()->getEpicLevel()/6.);
		std::vector<double> strength = strengthNetwork.guess(input);
		std::vector<double> dexterity = dexterityNetwork.guess(input);
		std::vector<double> intelligence = intelligenceNetwork.guess(input);
		std::vector<double> magica = magicaNetwork.guess(input);
		std::vector<double> charisma = charismaNetwork.guess(input);
		//std::cout << item->getType()->getName() << std::endl;
		//std::cout << "Sila: " << strength[0]*12 << " powinna byc " << item->getType()->getStrength() <<std::endl;
		//std::cout << "Zrecznosc: " << dexterity[0]*12 << " powinna byc " << item->getType()->getDexterity() << std::endl;
		//std::cout << "Inteligencja: " << intelligence[0]*12 << " powinna byc " << item->getType()->getIntelligence() << std::endl;
		//std::cout << "Magia: " << magica[0]*23 << " powinna byc " << item->getType()->getMagica() << std::endl;
		//std::cout << "Charyzma: " << charisma[0]*3 << " powinna byc " << item->getType()->getCharisma() << std::endl;
		//TODO classification function
		if (mode == 0)
		{
			if (strength[0] * 12 <=0)
			{
				return true;
			}
		}
		else if (mode == 1)
		{
			if (dexterity[0] * 12 <= 0)
			{
				return true;
			}
		}
		else if (mode == 2)
		{
			if (intelligence[0] * 12 <= 0)
			{
				return true;
			}
		}
		else if (mode == 3)
		{
			if (magica[0] * 23 <= 0)
			{
				return true;
			}
		}
		else if (mode == 4)
		{
			if (charisma[0] * 3 <= 0)
			{
				return true;
			}
		}
	}
	else
	{
		std::vector<double> input;
		input.push_back(item->getType()->getSize());
		input.push_back(item->getType()->getColor());
		input.push_back(item->getType()->getAgressivity());
		input.push_back(item->getType()->getColorDifference());
		input.push_back(item->getType()->getEpicLevel());
		int strT = strengthPNN.classify(input);
		int dexT = dexterityPNN.classify(input);
		int intT = intelligencePNN.classify(input);
		int magT = magicaPNN.classify(input);
		int charT = charismaPNN.classify(input);

		std::cout << item->getType()->getName() << std::endl;
		std::cout << "Sila: " << strT << " powinna byc " << item->getType()->getStrengthTier()+3 << std::endl;
		std::cout << "Zrecznosc: " << dexT << " powinna byc " << item->getType()->getDexterityTier()+3 << std::endl;
		std::cout << "Inteligencja: " << intT << " powinna byc " << item->getType()->getIntelligenceTier()+3 << std::endl;
		std::cout << "Magia: " << magT << " powinna byc " << item->getType()->getMagicaTier()+3 << std::endl;
		std::cout << "Charyzma: " << charT << " powinna byc " << item->getType()->getCharismaTier()+3 << std::endl;
		//TODO classify
	}
	return false;//Nie usowaj
}

void Board::createNewPNN()
{

	//Create PNNs
	createStrengthPNN();
	createDexterityPNN();
	createMagicaPNN();
	createIntelligencePNN();
	createCharismaPNN();
}

void Board::createStrengthPNN()
{
	std::vector <std::vector<std::vector<double>>> pointsInEachClass;
	std::vector<std::vector<double>> veryBad;
	std::vector<std::vector<double>> bad;
	std::vector<std::vector<double>> neutral;
	std::vector<std::vector<double>> good;
	std::vector<std::vector<double>> veryGood;

	for (int i = 0; i < pnnItemTypePoints.size(); i++)
	{
		std::vector<double> help;
		help.clear();
		help.push_back(pnnItemTypePoints[i]->getSize());
		help.push_back(pnnItemTypePoints[i]->getColor());
		help.push_back(pnnItemTypePoints[i]->getAgressivity());
		help.push_back(pnnItemTypePoints[i]->getColorDifference());
		help.push_back(pnnItemTypePoints[i]->getEpicLevel());
		switch (pnnItemTypePoints[i]->getStrengthTier())
		{
		case -2:
			veryBad.push_back(help);
			break;
		case -1:
			bad.push_back(help);
			break;
		case 0:
			neutral.push_back(help);
			break;
		case 1:
			good.push_back(help);
			break;
		case 2:
			veryGood.push_back(help);
			break;
		default:
			std::cout << "PNN classification error" << std::endl;
			break;
		}
	}
	pointsInEachClass.push_back(veryBad);
	pointsInEachClass.push_back(bad);
	pointsInEachClass.push_back(neutral);
	pointsInEachClass.push_back(good);
	pointsInEachClass.push_back(veryGood);
	this->strengthPNN = PNN(5, pointsInEachClass);
}

void Board::createDexterityPNN()
{
	std::vector <std::vector<std::vector<double>>> pointsInEachClass;
	std::vector<std::vector<double>> veryBad;
	std::vector<std::vector<double>> bad;
	std::vector<std::vector<double>> neutral;
	std::vector<std::vector<double>> good;
	std::vector<std::vector<double>> veryGood;

	for (int i = 0; i < pnnItemTypePoints.size(); i++)
	{
		std::vector<double> help;
		help.clear();
		help.push_back(pnnItemTypePoints[i]->getSize());
		help.push_back(pnnItemTypePoints[i]->getColor());
		help.push_back(pnnItemTypePoints[i]->getAgressivity());
		help.push_back(pnnItemTypePoints[i]->getColorDifference());
		help.push_back(pnnItemTypePoints[i]->getEpicLevel());
		switch (pnnItemTypePoints[i]->getDexterityTier())
		{
		case -2:
			veryBad.push_back(help);
			break;
		case -1:
			bad.push_back(help);
			break;
		case 0:
			neutral.push_back(help);
			break;
		case 1:
			good.push_back(help);
			break;
		case 2:
			veryGood.push_back(help);
			break;
		default:
			std::cout << "PNN classification error" << std::endl;
			break;
		}
	}
	pointsInEachClass.push_back(veryBad);
	pointsInEachClass.push_back(bad);
	pointsInEachClass.push_back(neutral);
	pointsInEachClass.push_back(good);
	pointsInEachClass.push_back(veryGood);
	this->dexterityPNN = PNN(5, pointsInEachClass);
}

void Board::createMagicaPNN()
{
	std::vector <std::vector<std::vector<double>>> pointsInEachClass;
	std::vector<std::vector<double>> veryBad;
	std::vector<std::vector<double>> bad;
	std::vector<std::vector<double>> neutral;
	std::vector<std::vector<double>> good;
	std::vector<std::vector<double>> veryGood;

	for (int i = 0; i < pnnItemTypePoints.size(); i++)
	{
		std::vector<double> help;
		help.clear();
		help.push_back(pnnItemTypePoints[i]->getSize());
		help.push_back(pnnItemTypePoints[i]->getColor());
		help.push_back(pnnItemTypePoints[i]->getAgressivity());
		help.push_back(pnnItemTypePoints[i]->getColorDifference());
		help.push_back(pnnItemTypePoints[i]->getEpicLevel());
		switch (pnnItemTypePoints[i]->getMagicaTier())
		{
		case -2:
			veryBad.push_back(help);
			break;
		case -1:
			bad.push_back(help);
			break;
		case 0:
			neutral.push_back(help);
			break;
		case 1:
			good.push_back(help);
			break;
		case 2:
			veryGood.push_back(help);
			break;
		default:
			std::cout << "PNN classification error" << std::endl;
			break;
		}
	}
	pointsInEachClass.push_back(veryBad);
	pointsInEachClass.push_back(bad);
	pointsInEachClass.push_back(neutral);
	pointsInEachClass.push_back(good);
	pointsInEachClass.push_back(veryGood);
	this->magicaPNN = PNN(5, pointsInEachClass);
}

void Board::createIntelligencePNN()
{
	std::vector <std::vector<std::vector<double>>> pointsInEachClass;
	std::vector<std::vector<double>> veryBad;
	std::vector<std::vector<double>> bad;
	std::vector<std::vector<double>> neutral;
	std::vector<std::vector<double>> good;
	std::vector<std::vector<double>> veryGood;

	for (int i = 0; i < pnnItemTypePoints.size(); i++)
	{
		std::vector<double> help;
		help.clear();
		help.push_back(pnnItemTypePoints[i]->getSize());
		help.push_back(pnnItemTypePoints[i]->getColor());
		help.push_back(pnnItemTypePoints[i]->getAgressivity());
		help.push_back(pnnItemTypePoints[i]->getColorDifference());
		help.push_back(pnnItemTypePoints[i]->getEpicLevel());
		switch (pnnItemTypePoints[i]->getIntelligenceTier())
		{
		case -2:
			veryBad.push_back(help);
			break;
		case -1:
			bad.push_back(help);
			break;
		case 0:
			neutral.push_back(help);
			break;
		case 1:
			good.push_back(help);
			break;
		case 2:
			veryGood.push_back(help);
			break;
		default:
			std::cout << "PNN classification error" << std::endl;
			break;
		}
	}
	pointsInEachClass.push_back(veryBad);
	pointsInEachClass.push_back(bad);
	pointsInEachClass.push_back(neutral);
	pointsInEachClass.push_back(good);
	pointsInEachClass.push_back(veryGood);
	this->intelligencePNN = PNN(5, pointsInEachClass);
}

void Board::createCharismaPNN()
{
	std::vector <std::vector<std::vector<double>>> pointsInEachClass;
	std::vector<std::vector<double>> veryBad;
	std::vector<std::vector<double>> bad;
	std::vector<std::vector<double>> neutral;
	std::vector<std::vector<double>> good;
	std::vector<std::vector<double>> veryGood;

	for (int i = 0; i < pnnItemTypePoints.size(); i++)
	{
		std::vector<double> help;
		help.clear();
		help.push_back(pnnItemTypePoints[i]->getSize());
		help.push_back(pnnItemTypePoints[i]->getColor());
		help.push_back(pnnItemTypePoints[i]->getAgressivity());
		help.push_back(pnnItemTypePoints[i]->getColorDifference());
		help.push_back(pnnItemTypePoints[i]->getEpicLevel());
		switch (pnnItemTypePoints[i]->getCharismaTier())
		{
		case -2:
			veryBad.push_back(help);
			break;
		case -1:
			bad.push_back(help);
			break;
		case 0:
			neutral.push_back(help);
			break;
		case 1:
			good.push_back(help);
			break;
		case 2:
			veryGood.push_back(help);
			break;
		default:
			std::cout << "PNN classification error" << std::endl;
			break;
		}
	}
	pointsInEachClass.push_back(veryBad);
	pointsInEachClass.push_back(bad);
	pointsInEachClass.push_back(neutral);
	pointsInEachClass.push_back(good);
	pointsInEachClass.push_back(veryGood);
	this->charismaPNN = PNN(5, pointsInEachClass);
}

void Board::addToPnnItemTypePoints(ItemType * type)
{
	bool tmp = true;
	for (int j = 0; j < pnnItemTypePoints.size(); j++)
	{
		if (pnnItemTypePoints[j]->getName() == type->getName())
		{
			tmp = false;
		}
	}
	if (tmp)
	{
		pnnItemTypePoints.push_back(type);
	}
}

