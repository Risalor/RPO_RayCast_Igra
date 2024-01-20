#pragma once
#include "Item.h"

class Weapon : public Item
{
private:
	int damage;
	float range;
	float coolDown;
	bool valid;
	
public:
	virtual Weapon* clone() const; //class se klonira za dodajanje v inventory
	Weapon(int startPosX, int startPosY, int damage, float range, float coolDown, bool picked, bool equiped, bool valid, std::string name, int sShWidth, int sSHeight, int numFramesHor, int numFramesVer);
	int getDamage() const { return this->damage; };
	float getRange() const { return this->range; };
	float getCoolDown() const { return this->coolDown; };
	bool getPickedStatus() const override;
	void setPicked(bool status) override;
	bool getEquiped() const override;
	void setEquiped(bool status) override;
	std::string getName() const override;
	bool isValid() const { return this->valid; };
	void setValid(bool status) { this->valid = status; };
	virtual ~Weapon();
	std::string toString();
};

