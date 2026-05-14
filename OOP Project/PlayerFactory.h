#pragma once
#include"PlayableCharacters.h"
#include "Sonic.h"
#include "Knuckles.h"
#include "Tails.h"

class PlayerFactory {
public:
	PlayableCharacters* createPlayer(string name, float acc) {
		if (name == "sonic") {
			return new Sonic(acc);
		}
		else if (name == "knuckles") {
			return new Knuckles(acc);
		}
		else if (name == "tails") {
			return new Tails(acc);
		}
		else return nullptr;
	}
};