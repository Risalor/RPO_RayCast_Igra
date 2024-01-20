#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
class Item				
{
private:			//nemoreš ustvarit Item objekta, lahko pa pointer na item
	std::string name;
	sf::Vector2f startPos;
	bool picked;
	bool equiped;
	int sShWidth;
	int sSHeight;
	int numFramesHor;
	int numFramesVer;
public:
	virtual Item* clone() const = 0;
	Item(int startPosX, int startPosY, bool picked, bool equiped, std::string name, int sShWidth, int sSHeight, int numFramesHor, int numFramesVer);
	virtual ~Item();
	sf::Vector2f getStartPos() const { return startPos; }
	virtual bool getPickedStatus() const { return picked; }
	virtual void setPicked(bool status) { this->picked = status; }
	virtual bool getEquiped() const { return equiped; }
	virtual void setEquiped(bool status)  { this->equiped = status; }
	inline std::string debugPrint() const { return this->name; }
	virtual std::string getName() const { return this->name; }
	virtual int getSpriteSheetWidth() const { return this->sShWidth; }
	virtual int getSpriteSheetHeight() const { return this->sSHeight; }
	virtual int getNumFramesHorizontal() const { return this->numFramesHor; }
	virtual int getNumFramesVertical() const { return this->numFramesVer; }
	
};

