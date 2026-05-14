#pragma once
#include "Enemies.h"
#include "PlayableCharacters.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

using namespace std;
using namespace sf;

class EggStinger : public Enemies {
private:
    PlayableCharacters* target = nullptr;
    bool movingRight = true;
    float leftBound = 0;
    float rightBound = 0;
    bool boundsInitialized = false;
    Clock attackTimer;
    const float attackInterval = 10.0f;
    const float flyHeight = 400.0f;
    const float patrolSpeed = 3.0f;
    const float diveSpeed = 5.0f;
    bool isDiving = false;

public:
    EggStinger(string Tpath = "Data/EggStinger.png")
        : Enemies(Tpath, 8, 20) {
        CharacSprite.setScale(0.5f, 0.56f);
        isGrounded = false;
    }

    void setTarget(PlayableCharacters* player) override {
        target = player;
    }

    void setBounds(float startX, int blocks) {
        leftBound = 64;
        rightBound = 18*64;
        boundsInitialized = true;
    }

    void startAttackTimer() {
        attackTimer.restart();
    }

    void move(int blocks) override {
        if (!boundsInitialized) {
            setBounds(posX, blocks);
        }

        if (!target) return;

        float targetY = target->getPosY() - flyHeight;
        if (!isDiving) {
            posY = targetY;
        }

        if (attackTimer.getElapsedTime().asSeconds() >= attackInterval && !isDiving) {
            isDiving = true;
        }

        if (isDiving) {
            float targetX = target->getPosX();
            float dx = targetX - posX; // Distance to player
            float dy = target->getPosY() - posY; // Distance to player

            if (abs(dy) < 5.0f && abs(dx) < 5.0f) {
                destroyGroundBlock(targetX);
                isDiving = false;
                attackTimer.restart();
                posY = targetY;
            }
            else {
                // Move towards player during dive
                float moveX = (dx > 0 ? diveSpeed : -diveSpeed);
                float moveY = (dy > 0 ? diveSpeed : -diveSpeed);
                posX += moveX;
                posY += moveY;

                // Constrain within level bounds without max/min
                if (posX < leftBound) {
                    posX = leftBound;
                }
                else if (posX > rightBound) {
                    posX = rightBound;
                }
                if (posY < 0.0f) {
                    posY = 0.0f; // Prevent moving above screen
                }
                else if (posY > 800) {
                    posY = 600; // Prevent moving below ground
                }
                CharacSprite.setPosition(posX, posY);
            }
        }
        else {
            float speed = patrolSpeed;
            posY = 300;
            if (movingRight) {
                posX += speed;
                if (posX >= rightBound) {
                    posX = rightBound;
                    movingRight = false;
                    CharacSprite.setScale(-0.51f, 0.57f);
                }
            }
            else {
                posX -= speed;
                if (posX <= leftBound) {
                    posX = leftBound;
                    movingRight = true;
                    CharacSprite.setScale(0.51f, 0.57f);
                }
            }
            CharacSprite.setPosition(posX, posY);
        }
    }

    void die() override {
        if (HP == 0) {
            isAlive = false;
            CharacSprite.setPosition(-100, -100);
        }
        else {
            HP--;
        }
        
    }

private:
    void destroyGroundBlock(float xPos) {
        cout << "Ground block at x=" << xPos << " destroyed!" << endl;
    }

    ~EggStinger() {
        target = nullptr;
    }
};