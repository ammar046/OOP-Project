#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

using namespace std;
using namespace sf;

class Collectibles {
protected:
    Texture texture;
    Sprite sprite;
    float posX;
    float posY;

public:
    Collectibles(){
		sprite.setScale(3.0f, 3.0f);
        posX = 0;
        posY = 0;
    }

    void draw(RenderWindow& window, float x, float y) {
        sprite.setPosition(x, y);
        window.draw(sprite);
    }

    virtual ~Collectibles() {} 
    virtual void updateAnimation(){}
};