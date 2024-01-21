#pragma once
#include <SFML/Graphics.hpp>
#include "global.h"
#include "Inventory.h"
#include "AnimationManager.h"




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
    int maxHp;
    Inventory inventory;

    sf::Vector2f plane;

    sf::Sprite inventorySprite;
    sf::Texture inventoryTexture;
    bool isInventoryVisible;

    sf::RectangleShape healthBar;
    sf::RectangleShape healthBarBackground;


public:
    
    explicit Player(float speed = 10.0f);
    ~Player();

    sf::Vector2f getPos() const { return playerPos; }
    sf::Vector2f getDir() const { return playerDir; }
    sf::Vector2f getPlane() const { return plane; }
    void setPos(int spx, int spy);

    void updateHealthBar();
    void renderHealthBar(sf::RenderTarget* window);
    void showInventory(sf::RenderTarget* window);


    void update(float dt);
    void updateEquipment(std::vector<Item*> item);
    void equipItem(int itemIndex);
    void move(float dt);
    Weapon* getItem();
    void unequipOthers(const std::string& name);
    bool checkBounds(int number);
    bool inventoryEmpty();
    int getInventorySize() const { return inventory.getSize();}
    void drawWeapons(sf::RenderTarget* window);
  
    //Weapon getWeapon(int index);


    const int& getHp() const { return this->hp;}
    void setHp(int amount) { this->hp = amount;}
    void takeDamage(int damage) {this->hp -= damage;}
   
};

