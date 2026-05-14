#pragma once
#include "PlayableCharacters.h"

class Knuckles : public PlayableCharacters {
private:
    string name = "Knuckles";
    bool isJumping = false, facingRight = true, ballForm = false;
    Animation jumpAnimRight = Animation("Data/KnucJumpR.png", 40, 40, 4);
    Animation jumpAnimLeft = Animation("Data/KnucJumpL.png", 40, 40, 4);
    Animation jogAnimLeft = Animation("Data/KnucJogL.png", 40, 40, 4);
    Animation jogAnimRight = Animation("Data/KnucJogR.png", 40, 40, 4);
    Animation runAnimLeft = Animation("Data/KnucRunL.png", 40, 40, 4);
    Animation runAnimRight = Animation("Data/KnucRunR.png", 40, 40, 4);

    int moveFrame = 0, jumpFrame = 0;
    Clock moveAnimClock, jumpClock;
    Texture idleTextureLeft, idleTextureRight;

    SoundBuffer buffer;
    Sound jab;
public:
    Knuckles(float acc) : PlayableCharacters("Data/Knuckles_right.png", 12.0f, acc) {
        selected = false;
        idleTextureRight.loadFromFile("Data/Knuckles_right.png");
        idleTextureLeft.loadFromFile("Data/Knuckles_left.png");
        CharacTexture = idleTextureRight;
        CharacSprite.setTexture(CharacTexture);
        CharacSprite.setTextureRect(IntRect(0, 0, 64, 64));

        buffer.loadFromFile("Data/Jab.wav");
        jab.setBuffer(buffer);
    }

    virtual void move(Keyboard::Key key) {
        if (selected) {
            speed = 12.0f;
        }
        else
            speed = 9.0f;
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
            }
            break;
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
    
            if (speed < 14) {
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

    void breakWall(char** grid, int gridY, int gridX) override {
        grid[gridY][gridX] = '0';
        if (grid[gridY - 1][gridX] != 'p' && grid[gridY - 1][gridX] != 'w'){
            grid[gridY - 1][gridX] = '0';
        }
        jab.stop();
        jab.play();
    }
    
    bool getBallForm() const override {return ballForm;}
    void notBallForm() override {ballForm = false;}
    void hitAnimation() override {
        
    }

   
    void invincibility() override {
        if (invincibilityClock.getElapsedTime().asSeconds() > invincibilityDuration){
            invincible = false;
        }
    }

    void setInvincibilityDuration(int x) override {
        invincibilityDuration = x;
    }

    void setInvincibility() override { invincible = true; invincibilityClock.restart();}
    string getName() const override { return name; }

    void setFacingRight(bool x) {
        facingRight = x;
    }
    bool getFacingRight() {
        return facingRight;
    }

    Sound getJabAudio() {
        return jab;
    }

    void setJabAudio(int x) {
        jab.setVolume(x);
    }

    ~Knuckles(){}
};