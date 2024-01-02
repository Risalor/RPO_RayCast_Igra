#include "Weapon.h"



Weapon::Weapon(int startPosX, int startPosY, int damage,float range,float coolDown, bool picked, bool equiped, std::string name)
	: Item( startPosX, startPosY, picked, equiped, name)
{
	this->damage = damage;
	this->range = range;
	this->coolDown = coolDown;
}

Weapon::~Weapon()
{
}

std::string Weapon::toString()
{
	return std::to_string(this->damage) + " " + std::to_string(this->range);
}

Weapon* Weapon::clone() const
{
	return new Weapon(*this);
}