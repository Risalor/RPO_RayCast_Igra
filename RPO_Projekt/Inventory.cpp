#include "Inventory.h"
Inventory::Inventory()
{
	this->capacity = 5;
	this->numOfItems = 0;
	this->itemArray = new Item * [capacity];
	this->initialize();
}

void Inventory::initialize(const int from)// gre skozi celoten inventory, tudi prazne iteme
{
	for (size_t i = from;i < capacity;i++) {
		itemArray[i] = nullptr;
	}
}

Inventory::~Inventory()
{
	for (size_t i = 0;i < this->numOfItems;i++) {
		delete this->itemArray[i];
	}
	delete[] itemArray;
}

Item& Inventory::operator[](const int index)
{
	if (index < 0 || index >= this->numOfItems) //preverimo ?e je index v arrayu
		throw("napa?en index");

	return *this->itemArray[index];

}


void Inventory::addItem(const Item& item)
{
	if (this->numOfItems >= this->capacity) {
		expand();
	}
	this->itemArray[this->numOfItems++] = item.clone();//nova kopija itema, nerabimo preverjat ali je Weapon ali Armor, naredimo kopijo inn vstavimo
}


void Inventory::expand()
{
	this->capacity *= 2; //podvojimo kapaciteto
	//std::cout << "kapaciteta: " << capacity << std::endl;

	Item **tmpArray = new Item * [this->capacity];

	for (size_t i = 0;i < this->numOfItems;i++) {
		tmpArray[i] = this->itemArray[i];	//ustvarimo novi item in ga kopiramo
	}
	
	delete[] this->itemArray;

	this->itemArray = tmpArray;//ker smo stari array zbrisali mora kazat na tmpArray v katerega smo vse prekopirali

	this->initialize(this->numOfItems);
}

void Inventory::removeItem(int index)
{
	if (index >= 0 && index < numOfItems && itemArray[index] != nullptr) {
		delete itemArray[index];
		itemArray[index] = nullptr;

	}

}

int Inventory::findItem(const std::string& itemName) const {
	for (size_t i = 0; i < numOfItems; ++i) {
		if (itemArray[i] != nullptr && itemArray[i]->getName() == itemName) {
			return i;
		}
	}
	return -1; // Predmet ni najden
}