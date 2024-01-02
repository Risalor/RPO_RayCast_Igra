#include "Item.h"

Item::Item(int startPosX, int startPosY, bool picked, bool equiped, std::string name)
{
	this->name = name;
	this->startPos.x = startPosX;
	this->startPos.y = startPosY;
	this->picked = picked;
	this->equiped = equiped;
}

Item::~Item()
{
}
