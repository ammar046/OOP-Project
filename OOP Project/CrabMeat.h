#pragma once
#include "Enemies.h"
#include "Fire.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class CrabMeat : public Enemies {
private:
    Fire fire;
    bool movingRight = true;
    float leftBound;
    float rightBound;
    bool boundsInitialized = false;
    float speedOffset;

public:
    CrabMeat(string Tpath = "Data/CrabMeat.png")
        : Enemies(Tpath, 5, 4) { 
        CharacSprite.setScale(1.4, 1.4);
        leftBound = 0; 
        rightBound = 0;
        speedOffset = 0.8f + static_cast<float>(rand()) / RAND_MAX * 0.4f;
        isGrounded = true;
    }

    void setBounds(float startX) {
        leftBound = startX;
        rightBound = leftBound; 
        boundsInitialized = true;
    }

    void move(int blocks) override {
        const float cellSize = 64.0f;
        if (!boundsInitialized) {
            leftBound = posX;
            rightBound = leftBound;
            boundsInitialized = true;
        }
        if (rightBound == leftBound) {
            rightBound = leftBound + blocks * cellSize;
        }

        float moveStep = speed * speedOffset;

        if (movingRight) {
            posX += moveStep;
            if (posX >= rightBound) {
                posX = rightBound;
                movingRight = false;
            }
        }
        else {
            posX -= moveStep;
            if (posX <= leftBound) {
                posX = leftBound;
                movingRight = true;
            }
        }

        CharacSprite.setPosition(posX, posY);
    }

    void die() override {
        isAlive = false;
        CharacSprite.setPosition(-100,-100);
    }

    ~CrabMeat(){}
};