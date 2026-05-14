#pragma once
#include"Collectibles.h"

class ExtraLife : public Collectibles {
public:
	ExtraLife(string s) :Collectibles() {
		texture.loadFromFile(s);
		sprite.setTexture(texture);
		sprite.setScale(0.075, 0.075);
	}
	~ExtraLife(){}
	
};