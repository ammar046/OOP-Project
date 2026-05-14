#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Fire {
private:
	Texture texture;
	Sprite sprite;
	float posX, posY;
	float speed;
	bool active;
	int direction; 

public:
	Fire() {
		texture.loadFromFile("Data/bullet.png");
		sprite.setTexture(texture);
		sprite.setScale(1.5f, 1.5f);
		posX = posY = 0;
		active = false;
		speed = 7.0f;
		direction = 1;
	}

	void shoot(float x, float y, int dir) {
		posX = x;
		posY = y;
		direction = dir;
		active = true;

		posX += (direction > 0) ? 30.0f : -30.0f;
		sprite.setPosition(posX, posY);
	}

	void update(float deltaTime) {
		if (!active) return;

		posX += speed * direction * deltaTime;
		sprite.setPosition(posX, posY);

		if (posX < -50 || posX > 1000) {
			active = false;
		}
	}

	void draw(RenderWindow& window) {
		if (active) {
			window.draw(sprite);
		}
	}

	bool isActive() const {
		return active;
	}

	void deactivate() {
		active = false;
	}

	float getposX(){
		return posX;
	}

	float getposY() {
		return posY;
	}

	void setSpeed(float newSpeed) {
		speed = newSpeed;
	}
};