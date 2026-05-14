#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Enemies.h"
#include "Collectibles.h"
#include "Sonic.h"
#include "Tails.h"
#include "Knuckles.h"
#include "PlayableCharacters.h"

using namespace std;

class Collision {
private:
    Collectibles** collectibles;
    PlayableCharacters* sonic;
    PlayableCharacters* tails;
    PlayableCharacters* knuckles;
    SoundBuffer bufferRing, bufferEL, bufferSB;
    Sound ringCollect, ELCollect, SBCollect;
    PlayableCharacters* selectedCharacter;

public:
    Collision(Collectibles** c) : collectibles(c), selectedCharacter(nullptr) {
        bufferRing.loadFromFile("Data/Ring.wav");
        ringCollect.setBuffer(bufferRing);
        ringCollect.setVolume(70);
        bufferEL.loadFromFile("Data/Event.wav");
        ELCollect.setBuffer(bufferEL);
        ELCollect.setVolume(70);
        bufferSB.loadFromFile("Data/SpecialRing.wav");
        SBCollect.setBuffer(bufferSB);
        SBCollect.setVolume(70);
    }

    void setSonic(PlayableCharacters* s) { sonic = s; }
    void setTails(PlayableCharacters* t) { tails = t; }
    void setKnuckles(PlayableCharacters* k) { knuckles = k; }
    void setSelectedCharacter(PlayableCharacters* s) { selectedCharacter = s; }

    bool isColliding(float x1, float x2, float y1, float y2, float w1, float w2, float h1, float h2) {
        return (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2);
    }

    int platformCollision(PlayableCharacters* p, char** grid, int w) {
        const int height = 14, width = w;

        int gridX = (int)(p->getPosX() + 36) / 64;
        int gridY = (int)((p->getPosY() + 64) / 64);

        if (gridY >= 0 && gridY < height && gridX >= 0 && gridX < width) {
            if (grid[gridY + 1][gridX] == 'p') {
                if (p->getPosY() < gridY) return 0;
                else return gridY;
            }
        }
        return 0;
    }

    void obstacleCollision(PlayableCharacters* p, char** grid, int width) {
        const int height = 14;

        int gridX = (int)(p->getPosX() + 32) / 64;
        int gridY = (int)((p->getPosY() + 64) / 64);

        if (gridY >= 0 && gridY < height && gridX >= 0 && gridX < width) {

            //collision with wall/platform on right
            if (grid[gridY][gridX + 1] == 'w' || grid[gridY][gridX + 1] == 'p' || grid[gridY][gridX + 1] == 'b') {
                if (p->getPosX() > (gridX - 1) * 64) {
                    p->setPosX(gridX * 64 - 25);
                }
            }

            //collision with top bound
            if (grid[gridY - 1][gridX] == 'w') {
                if (p->getPosY() < (gridY * 64) - 10) {
                    p->setPosY(gridY * 64);
                }
            }

            // //collision with left bound
            // if (grid[gridY][gridX - 1] == 'b') {
            //     if (p->getPosX() < (gridY * 64)) {
            //         p->setPosX(gridY * 64);
            //     }
            // }

            // //collision with right bound
            // if (grid[gridY][gridX + 1] == 'b') {
            //     if (p->getPosX() < (gridY * 64)) {
            //         p->setPosX(gridY * 64);
            //     }
            // }

            //solution for phasing through platform if on top on wall from right
            if (grid[gridY - 1][gridX + 1] == 'p') {
                if (p->getPosX() > (gridX - 1) * 64) {
                    p->setPosX(gridX * 64 - 25);
                }
            }

            //coollision with wall/platform on left
            if (grid[gridY][gridX - 1] == 'w' || grid[gridY][gridX - 1] == 'p' || grid[gridY][gridX - 1] == 'b') {
                if (p->getPosX() < (gridX * 64) - 10) {
                    p->setPosX(gridX * 64);
                }
            }

            //solution for phasing through platform if on top on wall from left
            if (grid[gridY - 1][gridX - 1] == 'p') {
                if (p->getPosX() < (gridX * 64) - 10) {
                    p->setPosX(gridX * 64);
                }
            }

            //knuckles break wall function from right
            if (grid[gridY][gridX + 1] == 'b' && p->getSelected()) {
                p->breakWall(grid, gridY, gridX + 1);
            }

            //knuckles break wall function from left
            if (grid[gridY][gridX - 1] == 'b' && p->getSelected()) {
                p->breakWall(grid, gridY, gridX - 1);
            }

            //hitting spike from right
            if (grid[gridY][gridX + 1] == 's') {
                if (p->getPosX() > (gridX - 1) * 64) {
                    if (p->getSelected()) {
                        p->hit();
                        p->setInvincibility();
                        p->invincibility();
                        p->setPosX(gridX * 64 - 192);
                        p->setPosY(gridY * 64 - 64);
                        p->land();
                    }
                    else {
                        p->setPosX(gridX * 64 - 192);
                        p->setPosY(gridY * 64 - 64);
                        p->land();
                    }
                }
            }

            //hitting spike from left
            if (grid[gridY][gridX - 1] == 's') {
                if (p->getPosX() < (gridX + 1) * 64) {
                    if (p->getSelected()) {
                        p->hit();
                        p->setInvincibility();
                        p->invincibility();
                        p->setPosX(gridX * 64 + 192);
                        p->setPosY(gridY * 64 - 64);
                        p->land();
                    }
                    else {
                        p->setPosX(gridX * 64 + 192);
                        p->setPosY(gridY * 64 - 64);
                        p->land();
                    }
                }
            }
        }
    }

    void collectiblesCollision(PlayableCharacters* p, char** grid, int w) {
        const int height = 14, width = w;

        int gridX1 = (int)(p->getPosX() + 64) / 64;
        int gridX2 = (int)(p->getPosX() + 32) / 64;
        int gridY = (int)((p->getPosY() + 64) / 64);

        if (gridY >= 0 && gridY < height && gridX1 >= 0 && gridX1 < width && gridX2 >= 0 && gridX2 < width) {
            if (grid[gridY][gridX1] == 'R') {
                grid[gridY][gridX1] = ' ';
                p->incrementScore();
                ringCollect.stop();
                ringCollect.play();
            }
            else if (grid[gridY][gridX2] == 'R') {
                grid[gridY][gridX2] = ' ';
                p->incrementScore();
                ringCollect.stop();
                ringCollect.play();
            }

            if (grid[gridY][gridX1] == 'L') {
                grid[gridY][gridX1] = ' ';
                if (p->getHP() < 3) p->incrementHP();
                ELCollect.stop();
                ELCollect.play();
            }
            else if (grid[gridY][gridX2] == 'L') {
                grid[gridY][gridX2] = ' ';
                if (p->getHP() < 3) p->incrementHP();
                ELCollect.stop();
                ELCollect.play();
            }

            if (grid[gridY][gridX1] == 'S') {
                cout << "Hit SB" << endl;
                grid[gridY][gridX1] = ' ';
                if (p->getName() == "Sonic") {
                    p->setSpeed(p->getSpeed() + 4);
                }
                else if (p->getName() == "Tails") {
                    p->setFlyDuration(p->getFlyDuration() + 4);
                }
                else if (p->getName() == "Knuckles") {
                    p->setInvincibilityDuration(15);
                }
                SBCollect.stop();
                SBCollect.play();
            }
            else if (grid[gridY][gridX2] == 'S') {
                cout << "Hit SB" << endl;
                grid[gridY][gridX2] = ' ';
                if (p->getName() == "Sonic") {
                    p->setSpeed(p->getSpeed() + 4);
                }
                else if (p->getName() == "Tails") {
                    p->setFlyDuration(p->getFlyDuration() + 4);
                }
                else if (p->getName() == "Knuckles") {
                    p->setInvincibilityDuration(15);
                }
                SBCollect.stop();
                SBCollect.play();
            }
        }
    }

    bool deadlyPitCollision(PlayableCharacters* p, char** grid, int w) {
        const int height = 14, width = w;

        int gridX = (int)(p->getPosX() + 32) / 64;
        int gridY = (int)((p->getPosY() + 64) / 64);

        if (gridY >= 0 && gridY < height && gridX >= 0 && gridX < width) {
            if (grid[gridY + 1][gridX] == 'd') {
                if (p->getSelected()) {
                    return true;
                }
                else {
                    if (selectedCharacter) {
                        p->setPosX(selectedCharacter->getPosX());
                        p->setPosY(selectedCharacter->getPosY());
                    }
                    else {
                        p->setPosX(p->getPosX());
                        p->setPosY(10.5f * 64);
                    }
                }
                p->getPhysics().isGrounded();
                p->getPhysics().stopFalling();
            }
        }
        return false;
    }

    void checkEnemyCollision(Enemies** e) {
        for (int i = 0; e[i] != nullptr; i++) {
            if (!e[i]->getisGrounded()) {
                if (isColliding(sonic->getPosX(), e[i]->getPosX(), sonic->getPosY(), e[i]->getPosY(), sonic->getWidth(), e[i]->getWidth(), sonic->getHeight(), e[i]->getHeight())) {
                    if (sonic->getSelected()) {
                        if (sonic->getBallForm()) {
                            e[i]->die();
                        }
                        else {
                            if (e[i]->getIsAlive()) {
                                sonic->hit();
                                sonic->setInvincibility();
                                sonic->invincibility();
                                if (rand() % 2) {
                                    sonic->setPosX(sonic->getPosX() - 192);
                                }
                                else {
                                    sonic->setPosX(sonic->getPosX() + 192);
                                }
                            }
                        }
                    }
                    else {
                        sonic->hitAnimation();
                    }
                }

                if (isColliding(tails->getPosX(), e[i]->getPosX(), tails->getPosY(), e[i]->getPosY(), tails->getWidth(), e[i]->getWidth(), tails->getHeight(), e[i]->getHeight())) {
                    if (tails->getSelected()) {
                        if (tails->getBallForm()) {
                            e[i]->die();
                        }
                        else {
                            if (e[i]->getIsAlive()) {
                                tails->hit();
                                tails->setInvincibility();
                                tails->invincibility();
                                if (rand() % 2) {
                                    tails->setPosX(tails->getPosX() - 192);
                                }
                                else {
                                    tails->setPosX(tails->getPosX() + 192);
                                }
                            }
                        }
                    }
                    else {
                        tails->hitAnimation();
                    }
                }

                if (isColliding(knuckles->getPosX(), e[i]->getPosX(), knuckles->getPosY(), e[i]->getPosY(), knuckles->getWidth(), e[i]->getWidth(), knuckles->getHeight(), e[i]->getHeight())) {
                    if (knuckles->getSelected()) {
                        if (knuckles->getBallForm()) {
                            e[i]->die();
                        }
                        else {
                            if (e[i]->getIsAlive()) {
                                knuckles->hit();
                                knuckles->setInvincibility();
                                knuckles->invincibility();
                                if (rand() % 2) {
                                    knuckles->setPosX(knuckles->getPosX() - 192);
                                }
                                else {
                                    knuckles->setPosX(knuckles->getPosX() + 192);
                                }
                            }
                        }
                    }
                    else {
                        tails->hitAnimation();
                    }
                }
            }
            else if (e[i]->getisGrounded()) {
                if (isColliding(sonic->getPosX(), e[i]->getPosX(), sonic->getPosY(), e[i]->getPosY() - 30, sonic->getWidth(), e[i]->getWidth(), sonic->getHeight(), e[i]->getHeight())) {
                    if (sonic->getSelected()) {
                        if (sonic->getBallForm()) {
                            e[i]->die();
                        }
                        else {
                            if (e[i]->getIsAlive()) {
                                sonic->hit();
                                sonic->setInvincibility();
                                sonic->invincibility();
                                if (rand() % 2) {
                                    sonic->setPosX(sonic->getPosX() - 192);
                                }
                                else {
                                    sonic->setPosX(sonic->getPosX() + 192);
                                }
                            }
                        }
                    }
                    else {
                        sonic->hitAnimation();
                    }
                }

                if (isColliding(tails->getPosX(), e[i]->getPosX(), tails->getPosY(), e[i]->getPosY() - 30, tails->getWidth(), e[i]->getWidth(), tails->getHeight(), e[i]->getHeight())) {
                    if (tails->getSelected()) {
                        if (tails->getBallForm()) {
                            e[i]->die();
                        }
                        else {
                            if (e[i]->getIsAlive()) {
                                tails->hit();
                                tails->setInvincibility();
                                tails->invincibility();
                                if (rand() % 2) {
                                    tails->setPosX(tails->getPosX() - 192);
                                }
                                else {
                                    tails->setPosX(tails->getPosX() + 192);
                                }
                            }
                        }
                    }
                    else {
                        tails->hitAnimation();
                    }
                }

                if (isColliding(knuckles->getPosX(), e[i]->getPosX(), knuckles->getPosY(), e[i]->getPosY() - 30, knuckles->getWidth(), e[i]->getWidth(), knuckles->getHeight(), e[i]->getHeight())) {
                    if (knuckles->getSelected()) {
                        if (knuckles->getBallForm()) {
                            e[i]->die();
                        }
                        else {
                            if (e[i]->getIsAlive()) {
                                knuckles->hit();
                                knuckles->setInvincibility();
                                knuckles->invincibility();

                                if (rand() % 2) {
                                    knuckles->setPosX(knuckles->getPosX() - 192);
                                }
                                else {
                                    knuckles->setPosX(knuckles->getPosX() + 192);
                                }
                            }
                        }
                    }
                    else {
                        tails->hitAnimation();
                    }
                }
            }

        }
    }

    void checkObstacleCollision(char** grid, int width) {
        obstacleCollision(sonic, grid, width);
        obstacleCollision(tails, grid, width);
        obstacleCollision(knuckles, grid, width);
    }

    void checkPlatformCollision(char** grid, int w) {

        int platS = platformCollision(sonic, grid, w);
        if (platS) {
            sonic->setPosY(((float)platS - 0.615) * 64);
            sonic->land();
        }
        else {
            sonic->getPhysics().notOnPlatform();
        }

        int platT = platformCollision(tails, grid, w);
        if (platT) {
            tails->setPosY(((float)platT - 0.615) * 64);
            tails->land();
        }
        else {
            tails->getPhysics().notOnPlatform();
        }

        int platK = platformCollision(knuckles, grid, w);
        if (platK) {
            knuckles->setPosY(((float)platK - 0.615) * 64);
            knuckles->land();
        }
        else {
            knuckles->getPhysics().notOnPlatform();
        }
    }

    bool checkDeadlyPitCollision(char** grid, int width) {
        if (deadlyPitCollision(sonic, grid, width) || deadlyPitCollision(tails, grid, width) || deadlyPitCollision(knuckles, grid, width)) return true;
        else return false;
    }

    void checkCollectiblesCollision(char** grid, int w) {
        collectiblesCollision(sonic, grid, w);
        collectiblesCollision(tails, grid, w);
        collectiblesCollision(knuckles, grid, w);
    }

    Sound getRingAudio() {
        return ringCollect;
    }

    void setringAudio(int vol) {
        ringCollect.setVolume(vol);
    }

    Sound getELifeAudio() {
        return ELCollect;
    }

    void setELifeAudio(int vol) {
        ELCollect.setVolume(vol);
    }

    Sound getSBoostAudio() {
        return SBCollect;
    }

    void setSBaudio(int vol) {
        SBCollect.setVolume(vol);
    }

    void OFFCollisionEffects() {
        setELifeAudio(0);
        setSBaudio(0);
        setringAudio(0);
    }

    void ONCollisionEffects() {
        setELifeAudio(70);
        setSBaudio(70);
        setringAudio(70);
    }

    void SetCollisionEffects(float x) {
        setELifeAudio(x);
        setSBaudio(x);
        setringAudio(x);
    }
};