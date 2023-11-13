#pragma once
#include <SFML/Graphics.hpp>
#include "global.h"


class Player {
    sf::Vector2f playerPos;
    sf::Vector2f playerDir;
    float movementSpeed;
    float rotationSpeed;


public:
    
    explicit Player(float speed = 10.0f);
    ~Player();
    sf::Vector2f getPos() const { return playerPos; }
    sf::Vector2f getDir() const { return playerDir; }
    void update(float dt);
};

