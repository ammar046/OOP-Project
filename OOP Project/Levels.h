#pragma once
#include <SFML/Graphics.hpp>
#include "PlayableCharacters.h"
#include "PlayerFactory.h"
#include "Collision.h"
#include "Enemies.h"
#include "BeeBot.h"
#include "Collectibles.h"
#include "CollectibleFactory.h"
#include "Enemyfactory.h"
#include "EggStinger.h"  

using namespace std;
using namespace sf;

class Level {
private:
    Clock LvlClock;
    Text Hpcount;
    Text ringCount;
    Font font;

    Texture heart;
    Sprite heartSprite;

    Texture clk;
    Sprite clkSprite;
    Text clkT;

    EnemyFactory enemyFactory;
    CollectibleFactory collectibleFactory;
    PlayerFactory playerFactory;
    PlayableCharacters** characters;
    int selectedIndex;
    int playerCount;
    float acceleration;

    Texture backgroundTexture;
    Sprite backgroundSprite;

    const int cellSize = 64;
    int height;
    int width;

    float offsetX;
    float targetOffsetX;
    float scrollSpeed;

    char** grid;

    Texture brickTexture;
    Sprite brickSprite;

    Texture ringTexture;
    Sprite ringSprite;

    Texture spikeT;
    Sprite spikeSprite;

    Collision collision;
    Enemies** Crab;
    Enemies** Bee;
    Enemies** Bat;
    Enemies** Moto;

    Collectibles** collectibles;

    int eCrabCount;
    int eBeeCount;
    int eBatCount;
    int eMotoCount;

    int totalRings;
    EggStinger* boss;


public:
    Level(const string& bgPath, char** levelGrid, int w, int h, float acc)
        : selectedIndex(0), playerCount(3), offsetX(0), targetOffsetX(0), scrollSpeed(0.1f),
        grid(levelGrid), Crab(nullptr), Bee(nullptr), Bat(nullptr), collectibles(nullptr),
        collision(collectibles), acceleration(acc), boss(nullptr)  
    {

        clk.loadFromFile("Data/clock.png");
        clkSprite.setTexture(clk);
        clkSprite.setScale(0.022, 0.022);
        clkSprite.setPosition(75, 155);

        heart.loadFromFile("Data/ExtraLife.png");
        heartSprite.setTexture(heart);
        heartSprite.setScale(0.075, 0.075);
        heartSprite.setPosition(60, 50);

        font.loadFromFile("fonts/SegaSonic.TTF");
        Hpcount.setFont(font);
        Hpcount.setString(": 3");
        Hpcount.setCharacterSize(25);
        Hpcount.setFillColor(sf::Color::White);
        Hpcount.setOutlineColor(sf::Color::Black);
        Hpcount.setPosition(130.f, 75.f);

        clkT.setFont(font);
        clkT.setString(": 150");
        clkT.setCharacterSize(25);
        clkT.setFillColor(sf::Color::White);
        clkT.setOutlineColor(sf::Color::Black);
        clkT.setPosition(130.f, 190.f);

        ringCount.setFont(font);
        ringCount.setString(": 0");
        ringCount.setCharacterSize(25);
        ringCount.setFillColor(sf::Color::White);
        ringCount.setOutlineColor(sf::Color::Black);
        ringCount.setPosition(130.f, 130.f);

        height = h;
        width = w;

        totalRings = RingsCount();

        LvlClock.restart();

        backgroundTexture.loadFromFile(bgPath);
        backgroundTexture.setRepeated(true);
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setTextureRect(IntRect(0, 0, width * cellSize, height * cellSize));

        spikeT.loadFromFile("Data/spike.png");
        spikeSprite.setTexture(spikeT);

        characters = new PlayableCharacters * [playerCount];
        characters[0] = playerFactory.createPlayer("sonic", acceleration);
        characters[1] = playerFactory.createPlayer("knuckles", acceleration);
        characters[2] = playerFactory.createPlayer("tails", acceleration);
        for (int i = 0; i < playerCount; i++)
            characters[i]->setSelected(i == selectedIndex);

        brickTexture.loadFromFile("Data/brick1.png");
        brickSprite.setTexture(brickTexture);
        ringTexture.loadFromFile("Data/Singlering.png");
        ringSprite.setTexture(ringTexture);
        ringSprite.setScale(0.06f, 0.06f);

        collectibles = new Collectibles * [3];
        collectibles[0] = collectibleFactory.createCollectible("Ring", "Data/Singlering.png");
        collectibles[1] = collectibleFactory.createCollectible("ExtraLife", "Data/ExtraLife.png");
        collectibles[2] = collectibleFactory.createCollectible("SpecialBoost", "Data/SpecialBoost.png");

        eCrabCount = enemyCrabCount();
        Crab = new Enemies * [eCrabCount + 1];
        int crabIdx = 0;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (grid[i][j] == 'M') {
                    Crab[crabIdx] = enemyFactory.createEnemy("CrabMeat");
                    Crab[crabIdx]->setPosX(j * cellSize);
                    Crab[crabIdx]->setPosY(i * cellSize);
                    crabIdx++;
                }
            }
        }
        Crab[eCrabCount] = nullptr;

        eBeeCount = enemyBeeCount();
        Bee = new Enemies * [eBeeCount + 1];
        int beeIdx = 0;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (grid[i][j] == 'B') {
                    Bee[beeIdx] = enemyFactory.createEnemy("BeeBot");
                    Bee[beeIdx]->setPosX(j * cellSize);
                    Bee[beeIdx]->setPosY(i * cellSize);
                    beeIdx++;
                }
            }
        }
        Bee[eBeeCount] = nullptr;

        eBatCount = enemyBatCount();
        Bat = new Enemies * [eBatCount + 1];
        int batIdx = 0;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (grid[i][j] == 'E') {
                    Bat[batIdx] = enemyFactory.createEnemy("BatBrain");
                    Bat[batIdx]->setPosX(j * cellSize);
                    Bat[batIdx]->setPosY(i * cellSize);
                    Bat[batIdx]->setTarget(characters[selectedIndex]);
                    batIdx++;
                }
            }
        }
        Bat[eBatCount] = nullptr;

        eMotoCount = enemyMotoCount();
        Moto = new Enemies * [eMotoCount + 1];
        int MotoIdx = 0;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (grid[i][j] == 'X') {
                    Moto[MotoIdx] = enemyFactory.createEnemy("Motobug");
                    Moto[MotoIdx]->setPosX(j * cellSize);
                    Moto[MotoIdx]->setPosY(i * cellSize);
                    Moto[MotoIdx]->setTarget(characters[selectedIndex]);
                    MotoIdx++;
                }
            }
        }
        Moto[eMotoCount] = nullptr;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (grid[i][j] == 'Y') {
                    boss = new EggStinger();
                    boss->setPosX(j * cellSize);
                    boss->setPosY(i * cellSize);
                    boss->setTarget(characters[selectedIndex]);
                    boss->setBounds(j * cellSize - 2 * cellSize, 5); 
                    break;
                }
            }
            if (boss) break; 
        }

        collision.setSonic(characters[0]);
        collision.setKnuckles(characters[1]);
        collision.setTails(characters[2]);
        collision.setSelectedCharacter(characters[selectedIndex]);
    }

    ~Level() {
        for (int i = 0; i < playerCount; i++) delete characters[i];
        delete[] characters;

        for (int i = 0; i < eCrabCount; i++) delete Crab[i];
        delete[] Crab;

        for (int i = 0; i < eBeeCount; i++) delete Bee[i];
        delete[] Bee;

        for (int i = 0; i < eBatCount; i++) delete Bat[i];
        delete[] Bat;

        for (int i = 0; i < eMotoCount; i++) delete Moto[i];
        delete[] Moto;

        for (int i = 0; i < 3; i++) delete collectibles[i];
        delete[] collectibles;

        
    }

    void handleInput(Keyboard::Key key) {
        if (key == Keyboard::Space) for (int i = 0; i < playerCount; i++) characters[i]->move(key);
        if (key == Keyboard::Z) {
            selectedIndex = (selectedIndex + 1) % playerCount;
            for (int i = 0; i < playerCount; i++) characters[i]->setSelected(i == selectedIndex);
            collision.setSelectedCharacter(characters[selectedIndex]);
            for (int i = 0; i < eBatCount; i++) {
                if (Bat[i]) Bat[i]->setTarget(characters[selectedIndex]);
            }
            for (int i = 0; i < eMotoCount; i++) {
                if (Moto[i]) Moto[i]->setTarget(characters[selectedIndex]);
            }
            if (boss) boss->setTarget(characters[selectedIndex]); 
        }
    }

    void update() {
        int t = LvlClock.getElapsedTime().asSeconds();
        clkT.setString(": " + to_string(150 - t));

        if (LvlClock.getElapsedTime().asSeconds() >= 150) {
            characters[0]->setHP(0);
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) characters[selectedIndex]->move(Keyboard::Left);
        if (Keyboard::isKeyPressed(Keyboard::Right)) characters[selectedIndex]->move(Keyboard::Right);

        PlayableCharacters* sel = characters[selectedIndex];
        bool isTailsFlying = (sel->getName() == "Tails" && sel->getIsFlying());

        for (int i = 0; i < playerCount; i++) {
            if (i != selectedIndex) {
                if (isTailsFlying) {
                    float dx = sel->getPosX() - characters[i]->getPosX();
                    float dy = sel->getPosY() - characters[i]->getPosY();
                    float followSpeed = 0.1f;

                    characters[i]->setPosX(characters[i]->getPosX() + dx * followSpeed - i * 2);
                    characters[i]->setPosY(characters[i]->getPosY() + dy * followSpeed);
                    characters[i]->getPhysics().stopFalling();
                    characters[i]->setFacingRight(sel->getFacingRight());
                }
                else {
                    float dx = sel->getPosX() - characters[i]->getPosX();
                    if (dx > 10) {
                        characters[i]->move(Keyboard::Right);
                        characters[i]->setFacingRight(true);
                    }
                    else if (dx < -10) {
                        characters[i]->move(Keyboard::Left);
                        characters[i]->setFacingRight(false);
                    }
                }
            }
        }

        for (int i = 0; i < playerCount; i++) {
            characters[i]->updatePhysics();
            characters[i]->updateAnimation();
        }

        for (int i = 0; i < 3; i++) {
            collectibles[i]->updateAnimation();
        }
        collision.checkEnemyCollision(Crab);
        collision.checkEnemyCollision(Bee);
        collision.checkEnemyCollision(Bat);
        collision.checkEnemyCollision(Moto);
        if (boss && boss->getIsAlive()) {
            Enemies* bossArray[2] = { boss, nullptr }; 
            collision.checkEnemyCollision(bossArray);
        }
        collision.checkPlatformCollision(grid, width);
        collision.checkObstacleCollision(grid, width);
        collision.checkCollectiblesCollision(grid, width);

        const float fallThreshold = height * cellSize;
        for (int i = 0; i < playerCount; i++) {
            if (characters[i]->getPosY() > fallThreshold) {
                characters[i]->setPosX(sel->getPosX());
                characters[i]->setPosY(sel->getPosY());
                characters[i]->getPhysics().stopFalling();
                characters[i]->getPhysics().isGrounded();
            }
        }

        targetOffsetX = sel->getPosX() - 600;
        offsetX += (targetOffsetX - offsetX) * scrollSpeed;
        if (offsetX < 0) {
            offsetX = 0;
        }
        else if (offsetX > width * cellSize - 1200) {
            offsetX = width * cellSize - 1200;
        }

        for (int i = 0; i < eCrabCount; i++) if (Crab[i]) Crab[i]->move(6);
        for (int i = 0; i < eBeeCount; i++) if (Bee[i]) Bee[i]->move(26);
        for (int i = 0; i < eBatCount; i++) if (Bat[i]) Bat[i]->move(15);
        for (int i = 0; i < eMotoCount; i++) if (Moto[i]) Moto[i]->move(15);
        if (boss && boss->getIsAlive()) boss->move(8); 

        backgroundSprite.setPosition(-offsetX, 0);

        Hpcount.setString(": " + to_string(getHP()));
        ringCount.setString(": " + to_string(getScore()));
    }

    int getScore() const { return characters[0]->getScore(); }
    int getTotalScore() const { return totalRings; }
    int getHP() const { return characters[0]->getHP(); }

    void draw(RenderWindow& window) {
        window.draw(backgroundSprite);
        window.draw(clkSprite);
        window.draw(clkT);
        window.draw(Hpcount);
        window.draw(heartSprite);
        window.draw(ringCount);
        ringSprite.setPosition(72, 120);
        window.draw(ringSprite);
        for (int i = 0; i < playerCount; i++) {
            if (!characters[i]->getSelected() && characters[i]->shouldDraw())
                characters[i]->draw(window, offsetX);
        }

        if (characters[selectedIndex]->shouldDraw())
            characters[selectedIndex]->draw(window, offsetX);
        for (int i = 0; i < height; i++) for (int j = 0; j < width; j++) {
            if (grid[i][j] == 'b' || grid[i][j] == 'p' || grid[i][j] == 'w') {
                brickSprite.setPosition(j * cellSize - offsetX, i * cellSize);
                window.draw(brickSprite);
            }
            else if (grid[i][j] == 'R') collectibles[0]->draw(window, j * cellSize - offsetX + 7, i * cellSize);
            else if (grid[i][j] == 'L') collectibles[1]->draw(window, j * cellSize - offsetX - 7, i * cellSize - 7);
            else if (grid[i][j] == 'S') collectibles[2]->draw(window, j * cellSize - offsetX + 7, i * cellSize);
            else if (grid[i][j] == 's') {
                spikeSprite.setPosition(j * cellSize - offsetX, i * cellSize);
                window.draw(spikeSprite);
            }
        }
        for (int i = 0; i < eCrabCount; i++) {
            if (Crab[i] && Crab[i]->getIsAlive()) {
                Crab[i]->draw(window, offsetX);
            }
        }
        for (int i = 0; i < eBeeCount; i++) {
            if (Bee[i] && Bee[i]->getIsAlive()) {
                Bee[i]->draw(window, offsetX);
            }
        }
        for (int i = 0; i < eBatCount; i++) {
            if (Bat[i] && Bat[i]->getIsAlive()) {
                Bat[i]->draw(window, offsetX);
            }
        }
        for (int i = 0; i < eMotoCount; i++) {
            if (Moto[i] && Moto[i]->getIsAlive()) {
                Moto[i]->draw(window, offsetX);
            }
        }
        if (boss && boss->getIsAlive()) boss->draw(window, offsetX); 
    }

    int enemyCrabCount() {
        int count = 0;
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                if (grid[i][j] == 'M')
                    count++;
        return count;
    }
    int enemyBeeCount() {
        int count = 0;
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                if (grid[i][j] == 'B')
                    count++;
        return count;
    }
    int enemyBatCount() {
        int count = 0;
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                if (grid[i][j] == 'E')
                    count++;
        return count;
    }
    int enemyMotoCount() {
        int count = 0;
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                if (grid[i][j] == 'X')
                    count++;
        return count;
    }

    int RingsCount(){
        int count = 0;
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                if (grid[i][j] == 'R')
                    count++;
        return count;
    }

    int getWidth() const { return width; }

    float getSelectedCharacterPosX() const { return characters[selectedIndex]->getPosX(); }

    void resetPlayerPositions() {
        for (int i = 0; i < playerCount; i++) {
            characters[i]->setPosX(100.0f);
            characters[i]->setPosY((height - 2) * cellSize);
            characters[i]->getPhysics().stopFalling();
            characters[i]->getPhysics().isGrounded();
        }
        offsetX = 0;
        targetOffsetX = 0;
    }

    void resetPlayerPositions(float startX, float startY = -1.0f) {
        for (int i = 0; i < playerCount; i++) {
            characters[i]->setPosX(startX);
            characters[i]->setPosY(startY >= 0 ? startY : (height - 2) * cellSize);
            characters[i]->getPhysics().stopFalling();
            characters[i]->getPhysics().isGrounded();
        }
        offsetX = 0;
        targetOffsetX = 0;
    }

    EggStinger* getEggStinger() {
        return boss;
    }

    void setHP(int hp) { characters[0]->setHP(hp); }

    bool checkDeath() {
        if (collision.checkDeadlyPitCollision(grid, width) || getHP() <= 0 ) return true;
        else return false;
    }

    void OFFSoundEffects() {
        for (int i = 0;i < playerCount;i++) {
            characters[i]->getPhysics().setJumpAudio(0);
            characters[i]->setJabAudio(0);
        }
        collision.OFFCollisionEffects();
    }

    void ONNSoundEffects() {
        for (int i = 0;i < playerCount;i++) {
            characters[i]->getPhysics().setJumpAudio(70);
            characters[i]->setJabAudio(70);
        }
            
        collision.ONCollisionEffects();
    }

    void setEffects(int x){
        collision.SetCollisionEffects(x);
        for (int i = 0;i < playerCount;i++) {
            characters[i]->getPhysics().setJumpAudio(x);
            characters[i]->setJabAudio(x);
        }
    }

    void setScore(int x) {
        characters[0]->ScoreSetting(x);
    }

   
};