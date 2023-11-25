#pragma once
#include "Item.h"
class Armor : public Item
{
private:
	int defence;
public:
	virtual Armor* clone() const;
	Armor(int defence = 0, std::string name= "Armor name");
	virtual ~Armor();
	std::string toString();
};

