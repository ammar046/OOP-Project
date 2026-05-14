#pragma once
#include "PlayableCharacters.h"
#include "Animation.h"

using namespace sf;

class Sonic : public PlayableCharacters {
private:
    string name = "Sonic";
    bool isJumping = false, facingRight = true, ballForm = false;
    Animation jumpAnimRight = Animation("Data/0upR.png", 40, 40, 4);
    Animation jumpAnimLeft = Animation("Data/0upL.png", 40, 40, 4);
    Animation walkAnimLeft = Animation("Data/0left.png", 40, 40, 4);
    Animation walkAnimRight = Animation("Data/0right.png", 40, 40, 4);
    Animation jogAnimLeft = Animation("Data/0jog_left.png", 40, 40, 4);
    Animation jogAnimRight = Animation("Data/0jog_right.png", 40, 40, 4);
    Animation runAnimLeft = Animation("Data/0left_run.png", 40, 40, 4);
    Animation runAnimRight = Animation("Data/0right_run.png", 40, 40, 4);

    int moveFrame = 0, jumpFrame = 0;
    Clock moveAnimClock, jumpClock;
    Texture idleTextureLeft, idleTextureRight;

public:
    Sonic(float acc) : PlayableCharacters("Data/0right_still.png", 18.0f, acc) {
        selected = true;
        idleTextureRight.loadFromFile("Data/0right_still.png");
        idleTextureLeft.loadFromFile("Data/0left_still.png");
        CharacTexture = idleTextureRight;
        CharacSprite.setTexture(CharacTexture);
        CharacSprite.setTextureRect(IntRect(0, 0, 64, 64));
    }
    virtual void move(Keyboard::Key key) {
        if (selected) {
            speed = 14.0f;
        }
        else
            speed = 9.5f;
        switch (key) {
        case Keyboard::Left:
            if (!selected) {
                if (posX >= 64)
                    posX -= speed;
                facingRight = false;
            }
            else {
                posX += velocityXLeft;
                facingRight = false;
                velocityXLeft -= acceleration;
                if (velocityXLeft < -speed) velocityXLeft = -speed;
                velocityXRight = -5.0f;
            }

            break;
        case Keyboard::Right:
            if (!selected) {
                posX += speed;
                facingRight = true;
            }
            else {
                posX += velocityXRight;
                facingRight = true;
                velocityXRight += acceleration;
                if (velocityXRight > speed) velocityXRight = speed;
                velocityXLeft = 5.0f;
            }break;
        case Keyboard::Space:
            physics.jump();
            isJumping = true;
            ballForm = true;
            jumpFrame = 0;
            jumpClock.restart();
            break;
        }
        CharacSprite.setPosition(posX, posY);
    }

    virtual void updateAnimation() override {
        updateBlinking();

        if (isJumping) {
            if (jumpClock.getElapsedTime().asMilliseconds() > 100) {
                if (jumpFrame < 3) {
                    (facingRight ? jumpAnimRight : jumpAnimLeft).applyFrame(CharacSprite, jumpFrame++);
                } else {
                    (facingRight ? jumpAnimRight : jumpAnimLeft).applyFrame(CharacSprite, 3);
                }
                jumpClock.restart();
            }
    
            if (getPosY() >= initialY) {
                isJumping = false;
                moveFrame = 0;
            }
            return;
        }
        if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Right)) &&
            moveAnimClock.getElapsedTime().asMilliseconds() > 120)
        {
            Animation* activeAnim = nullptr;
    
            if (speed < 10) {
                activeAnim = facingRight ? &walkAnimRight : &walkAnimLeft;
            } else if (speed >= 10 && speed < 14) {
                activeAnim = facingRight ? &jogAnimRight : &jogAnimLeft;
            } else {
                activeAnim = facingRight ? &runAnimRight : &runAnimLeft;
            }
    
            activeAnim->applyFrame(CharacSprite, moveFrame++);
            moveFrame %= 4;
            moveAnimClock.restart();
        }
        else if (!Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right)) {
            CharacTexture = facingRight ? idleTextureRight : idleTextureLeft;
            CharacSprite.setTexture(CharacTexture);
            CharacSprite.setTextureRect(IntRect(0, 0, 64, 64));
            moveFrame = 0;
        }
    }
    
    void land() override {
        physics.stopFalling();
        isJumping = false;
        ballForm = false;
        jumpFrame = 0;

        if (!Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right)) {
            moveFrame = 0;
            CharacTexture = facingRight ? idleTextureRight : idleTextureLeft;
            CharacSprite.setTexture(CharacTexture);
            CharacSprite.setTextureRect(IntRect(0, 0, 64, 64));
        }
    }

    bool getBallForm() const override {return ballForm;}
    void notBallForm() override {ballForm = false;}
    void hitAnimation() override {
        
    }

    void invincibility() override {
        if (invincibilityClock.getElapsedTime().asSeconds() > 5){
            invincible = false;
            invincibilityClock.restart();
        }
    }

    void setInvincibility() override { invincible = true;}
    string getName() const override { return name; }
    void setFacingRight(bool x) {
        facingRight = x;
    }
     bool getFacingRight() {
         return facingRight;
     }
    ~Sonic() {}
    
};
