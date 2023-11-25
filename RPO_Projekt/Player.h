#pragma once
#include <SFML/Graphics.hpp>
#include "global.h"
#include "Inventory.h"


class Player {
private:
    sf::Vector2f playerPos;
    sf::Vector2f playerDir;
    float movementSpeed;
    float rotationSpeed;
    bool shiftPressed;
    float shiftDelayTime;
    float shiftTimeCount;
    int hp;
    Inventory inventory;
    Weapon weapon;
    Armor armor;


public:
    
    explicit Player(float speed = 10.0f);
    ~Player();
    sf::Vector2f getPos() const { return playerPos; }
    sf::Vector2f getDir() const { return playerDir; }
    void update(float dt);
    void move(float dt);
    const int& getHp() const { return this->hp;}
   
};

