#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Characters {
protected:
    Texture CharacTexture;
    Sprite CharacSprite;
    float posX, posY;
    float initialY;
    float scaleX, scaleY;
    float speed;
    static int HP;
    static int score;
public:
    Characters(string Tpath, float spd, float x, float y, float inital, float sX, float sY): posX(x), posY(y), initialY(inital), scaleX(sX), scaleY(sY), speed(spd) {
        CharacTexture.loadFromFile(Tpath);
        CharacSprite.setTexture(CharacTexture);
        CharacSprite.setPosition(posX, posY);
        CharacSprite.setScale(scaleX, scaleY);
    }

    virtual ~Characters() {}
    virtual void move(Keyboard::Key key) {};

    void draw(RenderWindow& window, float offsetX = 0) {
        CharacSprite.setPosition(posX - offsetX, posY);
        window.draw(CharacSprite);
    }
    float getPosX() const {
        return posX;
    }
    float getPosY() const {
        return posY;
    }
    void setPosX(float x) {
        posX = x;
        CharacSprite.setPosition(posX, posY);
    }
    void setPosY(float y) {
        posY = y;
        CharacSprite.setPosition(posX, posY);
    }
    float getWidth() const{ return CharacTexture.getSize().x; }
    float getHeight() const{ return CharacTexture.getSize().y; }

    void incrementScore() { score++; }
    int getScore() const { return score; }
    int getHP() const { return HP; }
    void incrementHP() { HP++; }

    float getSpeed() const {
        return speed;
    }
}; int Characters::HP = 3; int Characters::score = 0;