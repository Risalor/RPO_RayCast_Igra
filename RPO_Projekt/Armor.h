#pragma once
#include "Item.h"
class Armor : public Item
{
private:
	int defence;
public:
	virtual Armor* clone() const;
	Armor(int startPosX, int startPosY, int defence , bool picked , bool equiped , std::string name , int sShWidth, int sSHeight, int numFramesHor, int numFramesVer);
	virtual ~Armor();
	std::string toString();
};

