#pragma once
#include "Item.h"

class Weapon : public Item
{
private:
	int damage;
	float range;
	float coolDown;
	
public:
	virtual Weapon* clone() const; //class se klonira za dodajanje v inventory
	Weapon(int startPosX, int startPosY, int damage, float range, float coolDown, bool picked, bool equiped, std::string name);
	bool getPickedStatus() const override;
	void setPicked(bool status) override;
	bool getEquiped() const override;
	void setEquiped(bool status) override;
	std::string getName() const override;
	virtual ~Weapon();
	std::string toString();
};

