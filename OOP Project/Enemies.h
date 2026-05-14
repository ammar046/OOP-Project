#pragma once
#include "Fire.h"
#include "Characters.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Enemies : public Characters {
protected:
    bool isAlive = true;
    bool isGrounded =true;

public:
    Enemies(string Tpath, float spd, int hp, bool shoots = false, float blocks = 2.0f)
        : Characters(Tpath, spd, 100, 0, 0, 2.5f, 2.5f) {}

    virtual void move(int blocks) {}
    bool getIsAlive() const { return isAlive; }
    virtual void die(){}
    bool getisGrounded() {
        return isGrounded;
    }
    virtual void setTarget(PlayableCharacters* player){}
    virtual ~Enemies() {}
};