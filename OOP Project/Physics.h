#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Physics {
private:
    float velocityY;
    float gravity;
    float jumpStrength;
    float flyStrength;
    float terminalVelocity;
    bool onGround, onPlatform;
    SoundBuffer buffer;
    Sound jumpAudio;

public:
    Physics() : velocityY(0.0f), gravity(1.0f), jumpStrength(-25.0f), flyStrength(-5.0f), terminalVelocity(20.0f), onGround(true), onPlatform(false) {

        buffer.loadFromFile("Data/Jump.wav");
        jumpAudio.setBuffer(buffer);
    }

    void applyGravity(float& posY, float initialY) {
        if (!onGround && !onPlatform) {
            posY += velocityY;
            velocityY += gravity;
            if (velocityY > terminalVelocity) {
                velocityY = terminalVelocity;
            }
        }
    }

    void jump() {
        if (onGround || onPlatform) {
            jumpAudio.stop();
            jumpAudio.play();
            velocityY = jumpStrength;
            onGround = false;
            onPlatform = false;
        }
    }

    void fly(bool& isFlying, Clock& flyClock, float flyDuration) {
        if (!isFlying && (onGround)) {
            flyClock.restart();
            isFlying = true;
            jumpAudio.stop();
            jumpAudio.play();
            velocityY = flyStrength;
            onGround = false;
            onPlatform = false;
        }
        if (isFlying && flyClock.getElapsedTime().asSeconds() < flyDuration) {
            velocityY = flyStrength;
            onGround = false;
            onPlatform = false;
        }
    }

    float getVelocityY() {return velocityY;}
    void isGrounded() {onGround = true;}
    void stopFalling() {velocityY = 0.0f; onPlatform = true; onGround = false;}
    void notOnPlatform() {onPlatform = false;}
    bool getOnPlatform() { return onPlatform; }

    Sound getJumpAudio() {
        return jumpAudio;
    }

    void setJumpAudio(int vol) {
       jumpAudio.setVolume(vol);
    }
};
