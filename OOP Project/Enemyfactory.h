#pragma once
#include "Enemies.h"
#include "BatBrain.h"
#include "BeeBot.h"
#include "MotoBug.h"
#include "CrabMeat.h"
#include "EggStinger.h"

using namespace std;
using namespace sf;

class EnemyFactory {
private:
    const string BAT_BRAIN = "BatBrain";
    const string BEE_BOT = "BeeBot";
    const string MOTOBUG = "Motobug";
    const string CRAB_MEAT = "CrabMeat";
    const string EGG_STINGER = "EggStinger";

public:
    EnemyFactory() {}

    Enemies* createEnemy(const string& enemyType) {
        Enemies* enemy = nullptr;

        if (enemyType == BAT_BRAIN) {
            enemy = new BatBrain();
        }
        else if (enemyType == BEE_BOT) {
            enemy = new BeeBot();
        }
        else if (enemyType == MOTOBUG) {
            enemy = new MotoBug();
        }
        else if (enemyType == CRAB_MEAT) {
            enemy = new CrabMeat();
        }
       /* else if (enemyType == EGG_STINGER) {
            enemy = new EggStinger();
        }*/

        return enemy;
    }
};