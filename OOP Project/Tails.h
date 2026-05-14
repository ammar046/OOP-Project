#pragma once
#include "PlayableCharacters.h"

class Tails : public PlayableCharacters {
private:
    string name = "Tails";
    bool isJumping = false, facingRight = true, ballForm = false;
    Animation jumpAnimRight = Animation("Data/TailsJumpR.png", 40, 40, 4);
    Animation jumpAnimLeft = Animation("Data/TailsJumpL.png", 40, 40, 4);
    Animation runAnimLeft = Animation("Data/TailsLRun.png", 40, 40, 4);
    Animation runAnimRight = Animation("Data/TailsRRun.png", 40, 40, 4);

    int moveFrame = 0, jumpFrame = 0;
    Clock moveAnimClock, jumpClock;
    Texture idleTextureLeft, idleTextureRight;

    bool isFlying = false;
    Clock flyClock;
    float flyDuration = 7.0f;

public:
    Tails(float acc) : PlayableCharacters("Data/TestTails.png", 10.0f, acc) {
        selected = false;
        idleTextureRight.loadFromFile("Data/TestTails.png");
        idleTextureLeft.loadFromFile("Data/TestTailsL.png");
        CharacTexture = idleTextureRight;
        CharacSprite.setTexture(CharacTexture);
        CharacSprite.setTextureRect(IntRect(0, 0, 40, 40));
    }

    virtual void move(Keyboard::Key key) override {
        if (selected) {
            speed = 10.0f;
        }
        else {
            speed = 8.5f;
        }

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
            if (!physics.getOnPlatform() && selected ) {
                physics.fly(isFlying, flyClock, flyDuration);  
            }
            else {
                if (selected) {
                    ballForm = true;
                }
                else {
                    ballForm = false;
                }
                physics.jump();  
                isJumping = true;
                
                jumpFrame = 0;
                jumpClock.restart();
            }
            break;
        }
        CharacSprite.setPosition(posX, posY);
    }

    void setFlyDuration(int x) override {
        flyDuration = x;
    }

    int getFlyDuration() const override { return flyDuration; }

    bool getIsFlying() const { return isFlying; }

    void updatePhysics() override {
        if (isFlying && flyClock.getElapsedTime().asSeconds() >= flyDuration) {
            isFlying = false; // disable flying after time limit
        }

        if (!isFlying) {
            physics.applyGravity(posY, initialY);
        }

        if (isFlying && getPosY() >= 64) posY += physics.getVelocityY();

        if (posY >= initialY) {
            posY = initialY;
            physics.isGrounded();
            isFlying = false; // reset flying on landing
        }

        CharacSprite.setPosition(posX, posY);
    }

    virtual void updateAnimation() {
        updateBlinking();

        if (isJumping) {
            if (jumpClock.getElapsedTime().asMilliseconds() > 100) {
                if (jumpFrame < 3) {
                    (facingRight ? jumpAnimRight : jumpAnimLeft).applyFrame(CharacSprite, jumpFrame++);
                }
                else {
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
            moveAnimClock.getElapsedTime().asMilliseconds() > 120) {
            Animation* activeAnim = facingRight ? &runAnimRight : &runAnimLeft;
            activeAnim->applyFrame(CharacSprite, moveFrame++);
            moveFrame %= 4;
            moveAnimClock.restart();
        }
        else if (!Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right)) {
            CharacSprite.setTexture(facingRight ? idleTextureRight : idleTextureLeft);
            CharacSprite.setTextureRect(IntRect(0, 0, 40, 40));
            moveFrame = 0;
        }
    }

    void land() override {
        physics.stopFalling();
        isJumping = false;
        ballForm = false;
        isFlying = false;
        jumpFrame = 0;

        if (!Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right)) {
            moveFrame = 0;
            CharacTexture = facingRight ? idleTextureRight : idleTextureLeft;
            CharacSprite.setTexture(CharacTexture);
            CharacSprite.setTextureRect(IntRect(0, 0, 64, 64));
        }
    }

    bool getBallForm() const override { return ballForm; }
    void notBallForm() override { ballForm = false; }
    void hitAnimation() override {
    }

   
    void invincibility() override {
        if (invincibilityClock.getElapsedTime().asSeconds() > 5) {
            invincible = false;
        }
    }

    void setInvincibility() override { invincible = true; invincibilityClock.restart(); }
    string getName() const override { return name; }

      void setFacingRight(bool x) {
        facingRight = x;
    }
     bool getFacingRight() {
         return facingRight;
     }
    ~Tails() {
    }
};