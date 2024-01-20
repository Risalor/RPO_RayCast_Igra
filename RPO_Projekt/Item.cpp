#include "Item.h"

Item::Item(int startPosX, int startPosY, bool picked, bool equiped, std::string name, int sShWidth, int sSHeight, int numFramesHor, int numFramesVer)
{
	this->sShWidth = sSHeight;
	this->sSHeight = sShWidth;
	this->numFramesHor = numFramesHor;
	this->numFramesVer = numFramesVer;
	this->name = name;
	this->startPos.x = startPosX;
	this->startPos.y = startPosY;
	this->picked = picked;
	this->equiped = equiped;
}

Item::~Item()
{
}
