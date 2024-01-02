#pragma once
#include "Item.h"

class Weapon : public Item
{
private:
	int damage;
	float range;
	float coolDown;
	
public:
	virtual Weapon* clone() const; //class se klonira za dodajanje v inventory
	Weapon(int startPosX, int startPosY, int damage = 0, float range = 0, float coolDown = 0, bool picked = false, bool equiped = false, std::string name = "Weapon name");
	
	virtual ~Weapon();
	std::string toString();
};

