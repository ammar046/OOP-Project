#pragma once
#include "Enemies.h"
#include "PlayableCharacters.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class BatBrain : public Enemies {
private:
    PlayableCharacters* target = nullptr;
    bool movingRight = true;
    float leftBound = 0;
    float rightBound = 0;
    bool boundsInitialized = false;

    const float xThreshold = 640; 
    const float chaseSpeed = 3.0f;       
    const float patrolSpeed = 1.5f;      
    const float minDistance = 20.0f;     

public:
    BatBrain(std::string Tpath = "Data/BatBrain.png")
        : Enemies(Tpath, 8, 1) {
        CharacSprite.setScale(1.4f, 1.4f);
        isGrounded = false;
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
            float dy = target->getPosY() - posY;
            float distance = sqrt(dx * dx + dy * dy);

            if (abs(dx) <= xThreshold && distance > minDistance) {
                float speed = chaseSpeed;
                if (distance > 0) {
                    posX += (dx / distance) * speed;
                    posY += (dy / distance) * speed;
                }
                CharacSprite.setScale(dx >= 0 ? -1.4f : 1.4f, 1.4f);
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
                CharacSprite.setScale(-1.4f, 1.4f);
            }
        }
        else {
            posX -= speed;
            if (posX <= leftBound) {
                posX = leftBound;
                movingRight = true;
                CharacSprite.setScale(1.4f, 1.4f);
            }
        }
        CharacSprite.setPosition(posX, posY);
    }

    void die() override {
        isAlive = false;
        CharacSprite.setPosition(-100,-100);
    }

    ~BatBrain(){
        target = nullptr;
    }
};