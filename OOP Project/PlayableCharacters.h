#pragma once
#include <SFML/Graphics.hpp>
#include "Characters.h"
#include "Physics.h"
using namespace sf;

class PlayableCharacters : public Characters {
protected:
    Physics physics;
    bool selected;
    float velocityX = 0.0f;
    Clock flyTime;
    float velocityXLeft = 0.0f, velocityXRight = 0.0f;
    float acceleration;
    bool invincible = false;
    Clock invincibilityClock;
    int invincibilityDuration = 5;
    Clock blinkClock;
    bool isBlinking = false;
    bool visible = true;
    Clock blinkToggleClock;


public:
    PlayableCharacters(string Tpath, float spd, float acc)
        : Characters(Tpath, spd, 100, 10.5f * 64, 10.5f * 64, 2.5f, 2.5f), selected(false), acceleration(acc) {}

    virtual ~PlayableCharacters() {}
    virtual void move(Keyboard::Key key) = 0;

    virtual void updatePhysics() {
        physics.applyGravity(posY, initialY);
        if (posY >= initialY) {
            posY = initialY;
            notBallForm();
            physics.isGrounded();
        }
        CharacSprite.setPosition(posX, posY);
    }

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
    float getSpeed() const { 
        return speed; 
    }
    void setSpeed(float x) {
        speed = x;
    }
    void setSelected(bool x) {
        selected = x;
    }

    void setHP(int hp) {
        HP = hp;
    }

    void setInitialY(float y) {initialY = y;}
    Physics& getPhysics() {return physics;}
    virtual void updateAnimation() {} 
    virtual bool getSelected() const { return selected; }
    virtual void followAndAnimate(const PlayableCharacters* leader) {}
    virtual void land(){}
    virtual void breakWall(char** grid, int gridY, int gridX){}
    virtual bool getBallForm() const { return false; }

    void hit() {
        cout << "HP: " << HP << endl;
        if (!invincible) {
            HP--;
            isBlinking = true;
            visible = true;
            blinkClock.restart();
            blinkToggleClock.restart();
        }
    }

    virtual void hitAnimation(){}
    virtual void invincibility(){}
    virtual void setInvincibility(){}
    virtual string getName() const { return  ""; }
    virtual void setFlyDuration(int x){}
    virtual int getFlyDuration() const { return 0; }
    virtual void setInvincibilityDuration(int x){}
    virtual void notBallForm(){}
    virtual bool getIsFlying() const { return false; }
    virtual  void setFacingRight(bool x) {}
    virtual bool getFacingRight()=0;

    virtual void setJabAudio(int x){}
    void ScoreSetting(int x){
        score = x;
    }

    bool shouldDraw() const {
        return visible;
    }

    virtual void updateBlinking() {
        if (isBlinking) {
            if (blinkClock.getElapsedTime().asSeconds() >= 3.0f) {
                isBlinking = false;
                visible= true;
            }
            else if (blinkToggleClock.getElapsedTime().asMilliseconds() >= 200) {
                visible = !visible;
                blinkToggleClock.restart();
            }
        }
    }
};