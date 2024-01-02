#pragma once
#include <iostream>
#include <string>
class Item				
{
private:			//nemoreš ustvarit Item objekta, lahko pa pointer na item
	std::string name;

public:
	virtual Item* clone() const = 0;
	Item(std::string name);
	virtual ~Item();
	inline std::string debugPrint() const { return this->name; }
	std::string getName() const { return this->name; }
};

