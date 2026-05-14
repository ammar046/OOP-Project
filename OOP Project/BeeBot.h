#pragma once
#include "Enemies.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cmath>

using namespace sf;

class BeeBot : public Enemies {
    Fire fire;
    bool movingRight = true;
    float leftBound;
    float rightBound;
    bool boundsInitialized = false;
    float zigzagTime = 0.0f;
    float phaseOffset;
    float speedOffset;     
    float originalY;       

public:
    BeeBot(std::string Tpath = "Data/Beebot.png")
        : Enemies(Tpath, 8, 1), fire(), movingRight(true), leftBound(0), rightBound(0), boundsInitialized(false)
    {
        CharacSprite.setScale(0.75f, 0.75f);
        phaseOffset = static_cast<float>(std::rand()) / RAND_MAX * 6.28318530718f;
        speedOffset = 0.8f + static_cast<float>(std::rand()) / RAND_MAX * 0.4f;
        isGrounded = false;
    }

    void move(int blocks) override {
        const float cellSize = 64.0f;

        if (!boundsInitialized) {
            leftBound = posX;
            rightBound = leftBound + blocks * cellSize;
            originalY = posY;
            boundsInitialized = true;
        }

        float moveStep = speed * speedOffset;
        if (movingRight) {
            posX += moveStep;
            if (posX >= rightBound) {
                posX = rightBound;
                movingRight = false;
                CharacSprite.setScale(0.75f, 0.75f);
            }
        }
        else {
            posX -= moveStep;
            if (posX <= leftBound) {
                posX = leftBound;
                movingRight = true;
                CharacSprite.setScale(-0.75f, 0.75f);
            }
        }

        zigzagTime += 0.05f;
        float waveAmplitude = 64.0f;
        float newY = originalY + std::sin(zigzagTime + phaseOffset) * waveAmplitude;
        posY = newY;

        CharacSprite.setPosition(posX, posY);
    }

    void die() override {
        isAlive = false;
        CharacSprite.setPosition(-100,-100);
    }

    ~BeeBot(){}
};