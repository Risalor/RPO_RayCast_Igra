#include "Weapon.h"



Weapon::Weapon(int damageMin, int damageMax, std::string name) : Item(name)
{
	 this->damageMin = damageMin;
	 this->damageMax = damageMax;
}

Weapon::~Weapon()
{
}

std::string Weapon::toString()
{
	return std::to_string(this->damageMin) + " " + std::to_string(this->damageMax);
}

Weapon* Weapon::clone() const
{
	return new Weapon(*this);
}