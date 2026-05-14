#pragma once
#include"Collectibles.h"

class SpecialBoost : public Collectibles {
private:
	Animation spin = Animation("Data/specialboostspritesheet.png", 16, 16, 4);
	Clock spinAnimClock;
	int spinFrame;
public:
	SpecialBoost(string s) :Collectibles() {
		spinFrame = 0;
		spin.applyFrame(sprite, 0);
	}

	void updateAnimation() override {
        if (spinAnimClock.getElapsedTime().asMilliseconds() > 80) {
            Animation* activeAnim = &spin;

            activeAnim->applyFrame(sprite, spinFrame++);
            spinFrame %= 4;
            spinAnimClock.restart();
        }
    }

	~SpecialBoost(){}
};