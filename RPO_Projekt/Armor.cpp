#include "Armor.h"


Armor* Armor::clone() const
{
	return new Armor(*this);
}

Armor::Armor(int startPosX, int startPosY, int defence, bool picked, bool equiped, std::string name)
	: Item(startPosX, startPosY, picked, equiped, name)
{
	this->defence = defence;
}

Armor::~Armor()
{
}

std::string Armor::toString()
{
	return std::to_string(this->defence);
}
