#include "Inventory.h"


Inventory::Inventory() : capacity(5), numOfItems(0), itemArray(new Item* [capacity]) {
	this->initialize();
}


Inventory::~Inventory()
{

}

Item& Inventory::operator[](const int index)
{
	if (index < 0 || index >= this->numOfItems) //preverimo ?e je index v arrayu
		throw("napa?en index");

	return *this->itemArray[index];

}


void Inventory::addItem(const Item& item) {
	if (this->numOfItems >= this->capacity) {
		expand();
	}
	this->itemArray[this->numOfItems++] = item.clone();
}


void Inventory::expand() {
	this->capacity *= 2;

	std::unique_ptr<Item* []> tmpArray = std::make_unique<Item * []>(this->capacity);

	for (size_t i = 0; i < this->numOfItems; ++i) {
		tmpArray[i] = this->itemArray[i];
	}

	this->itemArray = std::move(tmpArray); // Premakni lastništvo

	this->initialize(this->numOfItems);
}


void Inventory::initialize(const int from) {
	for (size_t i = from; i < capacity; ++i) {
		itemArray[i] = nullptr;
	}
}


void Inventory::removeItem(int index) {
	if (index >= 0 && index < numOfItems && itemArray[index] != nullptr) {
		itemArray[index] = nullptr; // unique_ptr samodejno izbriše objekt
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