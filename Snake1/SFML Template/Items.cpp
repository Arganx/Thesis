#include "Items.h"
#include "Item.h"
#include <iostream>
#include <math.h> 
Items::Items()
{
	size = 37;
	types = new ItemType[size];
	types[0]= ItemType("Zwoj", 5, 4, 0, 1, 1,"./src/textures/Daily Doodles - Pixel Art Asset Pack/magic07scroll.png",4);
	types[1] = ItemType("Miecz", 3, 3, 5, 3, 5, "./src/textures/Daily Doodles - Pixel Art Asset Pack/weapon01crystalsword.png", 5);
	types[2] = ItemType("Sztylet", 2, 0, 3, 3, 1, "./src/textures/Daily Doodles - Pixel Art Asset Pack/weapon02dagger.png", 6);
	types[3] = ItemType("Topor", 3, 0, 6, 3, 2, "./src/textures/Daily Doodles - Pixel Art Asset Pack/weapon05doubleaxe.png", 7);
	types[4] = ItemType("Plaszcz", 4, 3, 1, 1, 2, "./src/textures/Daily Doodles - Pixel Art Asset Pack/armour01magiciansrobe.png", 8);
	types[5] = ItemType("Lekki Pancerz", 4, 0, 3, 1, 0, "./src/textures/Daily Doodles - Pixel Art Asset Pack/armour02whiteshirt.png", 9);
	types[6] = ItemType("Ciezki Pancerz", 6, 2, 5, 2, 6, "./src/textures/Daily Doodles - Pixel Art Asset Pack/armour03velvetoutfit.png", 10);
	types[7] = ItemType("Kolczuga", 4, 0, 3, 2, 2, "./src/textures/Daily Doodles - Pixel Art Asset Pack/armour04chainmail.png", 11);
	types[8] = ItemType("Kaptur", 4, 1, 0, 1, 2, "./src/textures/Daily Doodles - Pixel Art Asset Pack/armour05monksrobe.png", 12);
	types[9] = ItemType("Zbroja", 5, 0, 4, 0, 4, "./src/textures/Daily Doodles - Pixel Art Asset Pack/armour05platemail.png", 13);
	types[10] = ItemType("Kurtka", 4, 1, 1, 0, 1, "./src/textures/Daily Doodles - Pixel Art Asset Pack/armour07leatherjerkin.png", 14);
	types[11] = ItemType("Niebieska roslina", 1, 3, 0, 2, 1, "./src/textures/Daily Doodles - Pixel Art Asset Pack/berry01blue.png", 15);
	types[12] = ItemType("Zolta roslina", 1, 4, 6, 1, 1, "./src/textures/Daily Doodles - Pixel Art Asset Pack/berry02yellow.png", 16);
	types[13] = ItemType("Fioletowa roslina", 1, 5, 0, 2, 1, "./src/textures/Daily Doodles - Pixel Art Asset Pack/berry03purple.png", 17);
	types[14] = ItemType("Czerwona roslina", 1, 1, 2, 2, 1, "./src/textures/Daily Doodles - Pixel Art Asset Pack/berry04red.png", 18);
	types[15] = ItemType("Zwykly miecz", 3, 0, 3, 3, 2, "./src/textures/Daily Doodles - Pixel Art Asset Pack/weapon03longsword.png", 19);
	types[16] = ItemType("Kiscien", 4, 6, 5, 1, 3, "./src/textures/Daily Doodles - Pixel Art Asset Pack/weapon04rustyflail.png", 20);
	types[17] = ItemType("Luk", 3, 4, 3, 3, 2, "./src/textures/Daily Doodles - Pixel Art Asset Pack/weapon06bow.png", 21);
	types[18] = ItemType("Wlocznia", 2, 6, 3, 1, 3, "./src/textures/Daily Doodles - Pixel Art Asset Pack/weapon07spear.png", 22);
	types[19] = ItemType("Naszyjnik", 3, 2, 0, 1, 2, "./src/textures/Daily Doodles - Pixel Art Asset Pack/magic06necklace.png", 23);
	types[20] = ItemType("Rozdzka", 2, 6, 0, 2, 2, "./src/textures/Daily Doodles - Pixel Art Asset Pack/magic05wand.png", 24);
	types[21] = ItemType("Pierscien", 3, 4, 1, 0, 3, "./src/textures/Daily Doodles - Pixel Art Asset Pack/magic04ring.png", 25);
	types[22] = ItemType("Kula", 2, 1, 0, 0, 4, "./src/textures/Daily Doodles - Pixel Art Asset Pack/magic03orb.png", 26);
	types[23] = ItemType("Ksiazka", 4, 3, 0, 0, 0, "./src/textures/Daily Doodles - Pixel Art Asset Pack/magic02spellbook.png", 27);
	types[24] = ItemType("Laska", 2, 4, 0, 2, 5, "./src/textures/Daily Doodles - Pixel Art Asset Pack/magic01crystalwand.png", 28);
	types[25] = ItemType("Eliksir Pomaranczowy", 4, 6, 2, 2, 3, "./src/textures/Daily Doodles - Pixel Art Asset Pack/glass01orange.png", 29);
	types[26] = ItemType("Eliksir Niebieski", 4, 3, 2, 2, 3, "./src/textures/Daily Doodles - Pixel Art Asset Pack/glass02blue.png", 30);
	types[27] = ItemType("Eliksir Zolty", 4, 4, 2, 2, 3, "./src/textures/Daily Doodles - Pixel Art Asset Pack/glass03yellow.png", 31);
	types[28] = ItemType("Eliksir Fioletowy", 4, 5, 2, 2, 3, "./src/textures/Daily Doodles - Pixel Art Asset Pack/glass04purple.png", 32);
	types[29] = ItemType("Eliksir Czerwony", 4, 1, 6, 2, 3, "./src/textures/Daily Doodles - Pixel Art Asset Pack/glass05red.png", 33);
	types[30] = ItemType("Eliksir Zielony", 4, 2, 2, 2, 3, "./src/textures/Daily Doodles - Pixel Art Asset Pack/glass06green.png", 34);
	types[31] = ItemType("Kamien Pomaranczowy", 0, 6, 0, 0, 1, "./src/textures/Daily Doodles - Pixel Art Asset Pack/gem01orange.png", 35);
	types[32] = ItemType("Kamien Niebieski", 0, 3, 0, 0, 1, "./src/textures/Daily Doodles - Pixel Art Asset Pack/gem02blue.png", 36);
	types[33] = ItemType("Kamien Zolty", 0, 4, 0, 0, 1, "./src/textures/Daily Doodles - Pixel Art Asset Pack/gem03yellow.png", 37);
	types[34] = ItemType("Kamien Fioletowy", 0, 5, 0, 0, 1, "./src/textures/Daily Doodles - Pixel Art Asset Pack/gem04purple.png", 38);
	types[35] = ItemType("Kamien Czerwony", 0, 1, 0, 0, 1, "./src/textures/Daily Doodles - Pixel Art Asset Pack/gem05red.png", 39);
	types[36] = ItemType("Kamien Zielony", 0, 2, 0, 0, 1, "./src/textures/Daily Doodles - Pixel Art Asset Pack/gem06green.png", 40);
	for (int i = 0; i < 37; i++)
	{
		std::cout << types[i].getName() << ": " <<types[i].getCharisma() << std::endl;
	}
}


Items::~Items()
{
}

ItemType * Items::getItemByState(int state)
{
	for (int i = 0; i < size; i++)
	{
		if (types[i].getState() == state)
		{
			return &types[i];
		}
	}
	return nullptr;
}

void Items::removeFromItemList(int x, int y)
{

	itemList.remove_if([x,y](Item i) { 
		if (i.getPosition().x == x && i.getPosition().y == y)
		{
			return true;
		}
		return false;
	});

}

void Items::sortListByDistance(sf::Vector2i player)
{
	struct ItemComparator
	{
		sf::Vector2i p;
		// Compare 2 Player objects using name
		bool operator ()(Item & item1, Item & item2)
		{
			if (item1.getPosition() == item2.getPosition())
				return false;;
			double distance1 = sqrt(pow(item1.getPosition().x-p.x,2.0) + pow(item1.getPosition().y - p.y, 2.0));
			double distance2 = sqrt(pow(item2.getPosition().x - p.x, 2.0) + pow(item2.getPosition().y - p.y, 2.0));
			return distance1 < distance2;

		}
	};
	ItemComparator comperator;
	comperator.p = player;
	itemList.sort(comperator);
}