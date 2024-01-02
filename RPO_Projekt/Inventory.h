#pragma once
#include "Weapon.h"
#include "Armor.h"


class Inventory
{
private:
	int capacity;
	int numOfItems;
	Item** itemArray;
	void expand();
	void initialize(const int from = 0);
public:
	Inventory();
	virtual ~Inventory();
	inline int getSize() const { return this->numOfItems; }
	Item& operator[](const int index);//prekritveni, da lahko v gameplaystate razredu izpišem iteme v arrayu
	void addItem(const Item& item);
	
	void removeItem(int index);
	int findItem(const std::string& itemName) const;
	inline void debugPrint() const {
		for (size_t i = 0;i < this->numOfItems;i++) {
			std::cout << this->itemArray[i]->debugPrint() << std::endl;
		}
	}
};

