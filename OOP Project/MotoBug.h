#pragma once
#include "Enemies.h"
#include "PlayableCharacters.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class MotoBug : public Enemies {
private:
    PlayableCharacters* target = nullptr;
    bool movingRight = true;
    float leftBound = 0;
    float rightBound = 0;
    bool boundsInitialized = false;

    const float xThreshold = 10 * 64.0f; 
    const float chaseSpeed = 4.0f;       
    const float patrolSpeed = 2.0f;      
    const float minDistance = 20.0f;     

public:
    MotoBug(std::string Tpath = "Data/MotoBug.png")
        : Enemies(Tpath, 8, 1) {
        CharacSprite.setScale(1, 1);
        isGrounded = true;
    }

    void setTarget(PlayableCharacters* player) {
        target = player;
  
    }

    void setBounds(float startX, int blocks) {
        leftBound = startX;
        rightBound = startX + blocks * 64.0f;
        boundsInitialized = true;

    }

    void move(int blocks) override {
        if (!boundsInitialized) {
            setBounds(posX, blocks);
        }

        if (target) {
            float dx = target->getPosX() - posX;
            float distance = std::abs(dx);

            if (std::abs(dx) <= xThreshold && distance > minDistance) {
                float speed = chaseSpeed;
                posX += (dx > 0 ? speed : -speed);
                CharacSprite.setScale(dx >= 0 ? -1 : 1, 1);
                CharacSprite.setPosition(posX, posY);
                return;
            }
            
        }
        
        float speed = patrolSpeed;
        if (movingRight) {
            posX += speed;
            if (posX >= rightBound) {
                posX = rightBound;
                movingRight = false;
                CharacSprite.setScale(1, 1);
            }
        }
        else {
            posX -= speed;
            if (posX <= leftBound) {
                posX = leftBound;
                movingRight = true;
                CharacSprite.setScale(-1, 1);
            }
        }
        CharacSprite.setPosition(posX, posY);
        
    }

    void die() override {
        isAlive = false;
        CharacSprite.setPosition(-100,-100);
    }

    ~MotoBug() {
        target = nullptr;
    }
};