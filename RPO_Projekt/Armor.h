#pragma once
#include "Item.h"
class Armor : public Item
{
private:
	int defence;
public:
	virtual Armor* clone() const;
	Armor(int startPosX, int startPosY, int defence = 0, bool picked = false , bool equiped = false, std::string name= "Armor name");
	virtual ~Armor();
	std::string toString();
};

