#pragma once
#include "ExtraLife.h"
#include "SpecialBoost.h"
#include "Ring.h"

class CollectibleFactory {
public:
    Collectibles* createCollectible(string s, string a) {
        if (s == "Ring") {
            return new Ring(a);
        }
        else if (s == "ExtraLife") {
            return new ExtraLife(a);
        }
        else if (s == "SpecialBoost") {
            return new SpecialBoost(a);
        }
        return nullptr;
    }
};