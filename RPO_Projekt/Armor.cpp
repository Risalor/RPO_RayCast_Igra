#include "Armor.h"


Armor* Armor::clone() const
{
	return new Armor(*this);
}

Armor::Armor(int defence, std::string name) : Item(name)
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
