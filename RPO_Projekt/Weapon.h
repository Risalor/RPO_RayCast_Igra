#pragma once
#include "Item.h"

class Weapon : public Item
{
private:
	int damageMin;
	int damageMax;
public:
	virtual Weapon* clone() const; //class se klonira za dodajanje v inventory
	Weapon(int damageMin = 0, int damageMax = 0, std::string name = "Weapon name");
	virtual ~Weapon();
	std::string toString();
};

