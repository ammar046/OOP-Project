#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "Menu.h"
#include "Levels.h"
#include "LevelFactory.h"
using namespace std;
using namespace sf;

class Game {
private:
    RenderWindow window;
    Menu menu;
    Level** level;
    LevelFactory Lfactory;
    int levelIndex;
    int size;
    int state;
    Music lvlMus;
    int HP;
    int score;
    bool death;

public:
    Game() : window(VideoMode(1200, 900), "Sonic the Hedgehog-OOP", Style::Close),
        menu(), level(nullptr), levelIndex(0), size(4), state(0), HP(3), score(0), death(true) {
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(60);
        level = new Level * [size];
        for (int i = 0; i < size; ++i) level[i] = nullptr;
    }

    ~Game() {
        for (int i = 0; i < size; ++i)
            if (level[i]) delete level[i];
        delete[] level;
    }

    void run() {
        while (window.isOpen() && state != -1) {
            processEvents();
            update();
            render();
        }
    }

    void processEvents() {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                state = -1;
                window.close();
            }
            else if (event.type == Event::KeyReleased) {
                if (state == 0) handleMenuInput(event.key.code);
                else if (state == 1) {
                    if (event.key.code == Keyboard::Escape) {
                        lvlMus.stop();
                        state = 0;
                    }
                    else level[levelIndex]->handleInput(event.key.code);
                }
            }
        }
    }

    void handleMenuInput(Keyboard::Key key) {
        if (key == Keyboard::Up) menu.MoveUp();
        else if (key == Keyboard::Down) menu.MoveDown();
        else if (key == Keyboard::Left) menu.MoveLeft();
        else if (key == Keyboard::Right) menu.MoveRight();
        else if (key == Keyboard::Enter) {
            if (!menu.IsInOptionsMenu() && !menu.IsInLeaderBoard() && !menu.IsInLevelSelect()) {
                int choice = menu.GetSelectedIndex();
                if (choice == 0 && !death) {
                    state = 1;
                    if (!level[levelIndex]) {
                        level[levelIndex] = Lfactory.createLevel(levelIndex);
                        HP = level[levelIndex]->getHP();
                        score = level[levelIndex]->getScore();
                        lvlMus.openFromFile("Data/labrynth.wav");
                        lvlMus.setVolume(30);
                        lvlMus.setLoop(true);
                        lvlMus.play();
                    }
                    else {
                        lvlMus.play();
                    }
                }
                else if (choice == 1 || (choice == 0 && death)) {
                    for (int i = 0; i < size; ++i) {
                        if (level[i]) {
                            delete level[i];
                            level[i] = nullptr;
                        }
                    }
                    levelIndex = 0;
                    level[levelIndex] = Lfactory.createLevel(levelIndex);
                    level[levelIndex]->setHP(3);
                    level[levelIndex]->setScore(0);
                    lvlMus.openFromFile("Data/labrynth.wav");
                    lvlMus.setVolume(30);
                    lvlMus.setLoop(true);
                    lvlMus.play();
                    state = 1;
                    death = false;
                }
                else if (choice == 2) menu.EnterSelection();
                else if (choice == 3) menu.EnterSelection();
                else if (choice == 4) menu.EnterSelection();
            }
            else if (menu.IsInOptionsMenu()) {
                menu.EnterSelection();
            }
            else if (menu.IsInLeaderBoard()) {
                menu.EnterSelection();
            }
            else if (menu.IsInLevelSelect()) {
                int selectedLevel = menu.GetSelectedIndex();
                for (int i = 0; i < size; ++i) {
                    if (level[i]) {
                        delete level[i];
                        level[i] = nullptr;
                    }
                }
                levelIndex = selectedLevel;
                level[levelIndex] = Lfactory.createLevel(levelIndex);
                level[levelIndex]->setHP(3);
                level[levelIndex]->setScore(0);
                lvlMus.openFromFile("Data/labrynth.wav");
                lvlMus.setVolume(30);
                lvlMus.setLoop(true);
                lvlMus.play();
                state = 1;
                death = false;
                menu.ExitLevelSelect();
            }
        }
        else if (key == Keyboard::Escape) {
            if (menu.IsInOptionsMenu()) menu.ExitOptionsMenu();
            else if (menu.IsInLeaderBoard()) menu.ExitLeaderBoard();
            else if (menu.IsInLevelSelect()) menu.ExitLevelSelect();
        }
    }

    void update() {
        if (state != 1) return;
        level[levelIndex]->update();
        death = level[levelIndex]->checkDeath();

        float px = level[levelIndex]->getSelectedCharacterPosX();
        int levelWidth = level[levelIndex]->getWidth() * 64;
        if (px >= levelWidth - 128 && level[levelIndex]->getScore() >= level[levelIndex]->getTotalScore() - 5) {
            lvlMus.stop();
            delete level[levelIndex];
            level[levelIndex] = nullptr;
            levelIndex++;
            if (levelIndex < size) {
                level[levelIndex] = Lfactory.createLevel(levelIndex);
                if (levelIndex == 3) {
                    EggStinger* boss = level[levelIndex]->getEggStinger();
                    if (boss) boss->startAttackTimer();
                    level[levelIndex]->resetPlayerPositions(640.0f, 600.0f);
                }
                else level[levelIndex]->resetPlayerPositions();
                HP = level[levelIndex]->getHP();
                score = level[levelIndex]->getScore();
                lvlMus.openFromFile("Data/labrynth.wav");
                lvlMus.setVolume(30);
                lvlMus.setLoop(true);
                lvlMus.play();
            }
            else {
                state = 0;
                death = true;
            }
            return;
        }

        HP = level[levelIndex]->getHP();
        score = level[levelIndex]->getScore();
        if (level[levelIndex]->checkDeath()) {
            lvlMus.stop();
            level[levelIndex]->setHP(3);
            level[levelIndex]->setScore(0);
            state = 0;
            death = true;
        }

        if (!menu.GetMusicState()) {
            lvlMus.stop();
        }
        if (!menu.GetSoundEffectsState()) {
            level[levelIndex]->OFFSoundEffects();
        }
        else {
            if (level[levelIndex]) {
                level[levelIndex]->setEffects(menu.GetVolumeLevel());
                lvlMus.setVolume(menu.GetVolumeLevel());
            }
            level[levelIndex]->ONNSoundEffects();
        }
    }

    void render() {
        window.clear();
        if (state == 0) menu.draw(window);
        else if (state == 1) level[levelIndex]->draw(window);
        window.display();
    }
};