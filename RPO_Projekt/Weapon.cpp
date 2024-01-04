#include "Weapon.h"



Weapon::Weapon(int startPosX, int startPosY, int damage,float range,float coolDown, bool picked, bool equiped, bool valid, std::string name)
	: Item( startPosX, startPosY, picked, equiped, name)
{
	this->damage = damage;
	this->range = range;
	this->coolDown = coolDown;
	this->valid = false;
}

bool Weapon::getPickedStatus() const
{
	return Item::getPickedStatus();
}

void Weapon::setPicked(bool status)
{
	Item::setPicked(status);
}

bool Weapon::getEquiped() const
{
	return Item::getEquiped();
}

void Weapon::setEquiped(bool status)
{
	Item::setEquiped(status);
}

std::string Weapon::getName() const
{
	return Item::getName();
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