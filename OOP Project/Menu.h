#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class Menu {
private:
    Texture backgroundTexture;
    Sprite backgroundSprite;
    Font titleFont;
    Text titleText;
    Text leaderBoardTitleText;
    Text levelSelectTitleText;
    RectangleShape leaderBoardRect;
    static const int mainMenuCount = 5; // Increased to include level select
    static const int optionsMenuCount = 3;
    static const int levelSelectCount = 4; // For levels 1 to 4
    Text mainMenuItems[mainMenuCount];
    Text optionsMenuItems[optionsMenuCount];
    Text levelSelectItems[levelSelectCount];
    int mainSelectedIndex;
    int optionsSelectedIndex;
    int levelSelectIndex;
    bool inOptionsMenu;
    bool inLeaderBoard;
    bool inLevelSelect;
    bool soundEffectsOn;
    bool musicOn;
    int volumeLevel;

public:
    Menu() : mainSelectedIndex(0), optionsSelectedIndex(0), levelSelectIndex(0),
        inOptionsMenu(false), inLeaderBoard(false), inLevelSelect(false),
        soundEffectsOn(true), musicOn(true), volumeLevel(70) {
        if (!backgroundTexture.loadFromFile("Sprites/Sonic_BG.png")) {
            cout << "FILE NOT FOUND!!" << endl;
        }
        backgroundSprite.setTexture(backgroundTexture);

        if (!titleFont.loadFromFile("fonts/SegaSonic.TTF")) {
            cout << "FILE NOT FOUND!!" << endl;
        }

        titleText.setFont(titleFont);
        titleText.setString("sonic game");
        titleText.setCharacterSize(75);
        titleText.setFillColor(Color::Yellow);
        titleText.setPosition(50.f, 200.f);
        titleText.setOutlineColor(sf::Color::Black);

        leaderBoardTitleText.setFont(titleFont);
        leaderBoardTitleText.setString("leaderboard");
        leaderBoardTitleText.setCharacterSize(75);
        leaderBoardTitleText.setFillColor(Color::Yellow);
        leaderBoardTitleText.setPosition(50.f, 150.f);
        leaderBoardTitleText.setOutlineColor(sf::Color::Black);

        levelSelectTitleText.setFont(titleFont);
        levelSelectTitleText.setString("level select");
        levelSelectTitleText.setCharacterSize(75);
        levelSelectTitleText.setFillColor(Color::Yellow);
        levelSelectTitleText.setPosition(50.f, 150.f);
        levelSelectTitleText.setOutlineColor(sf::Color::Black);

        leaderBoardRect.setSize(Vector2f(690.f, 500.f));
        leaderBoardRect.setFillColor(Color::White);
        leaderBoardRect.setPosition(50.f, 300.f);

        string mainOptions[mainMenuCount] = { "continue", "play game", "settings", "leader board", "level select" };
        for (int i = 0; i < mainMenuCount; i++) {
            mainMenuItems[i].setFont(titleFont);
            mainMenuItems[i].setString(mainOptions[i]);
            mainMenuItems[i].setCharacterSize(46);
            mainMenuItems[i].setPosition(50.f, 350.f + i * 90.f);
            mainMenuItems[i].setFillColor(i == mainSelectedIndex ? Color::Yellow : Color::Black);
            mainMenuItems[i].setOutlineColor(sf::Color::Black);
        }

        optionsMenuItems[0].setFont(titleFont);
        optionsMenuItems[0].setString("sound effects: on");
        optionsMenuItems[0].setCharacterSize(46);
        optionsMenuItems[0].setPosition(50.f, 350.f);
        optionsMenuItems[0].setOutlineColor(sf::Color::Black);

        optionsMenuItems[1].setFont(titleFont);
        optionsMenuItems[1].setString("volume: 70");
        optionsMenuItems[1].setCharacterSize(46);
        optionsMenuItems[1].setPosition(50.f, 440.f);
        optionsMenuItems[1].setOutlineColor(sf::Color::Black);

        optionsMenuItems[2].setFont(titleFont);
        optionsMenuItems[2].setString("music: on");
        optionsMenuItems[2].setCharacterSize(46);
        optionsMenuItems[2].setPosition(50.f, 530.f);
        optionsMenuItems[2].setOutlineColor(sf::Color::Black);

        for (int i = 0; i < optionsMenuCount; i++) {
            optionsMenuItems[i].setFillColor(i == optionsSelectedIndex ? Color::Yellow : Color::Black);
        }

        string levelOptions[levelSelectCount] = { "level 1", "level 2", "level 3", "BOSS LEVEL" };
        for (int i = 0; i < levelSelectCount; i++) {
            levelSelectItems[i].setFont(titleFont);
            levelSelectItems[i].setString(levelOptions[i]);
            levelSelectItems[i].setCharacterSize(46);
            levelSelectItems[i].setPosition(50.f, 350.f + i * 90.f);
            levelSelectItems[i].setFillColor(i == levelSelectIndex ? Color::Yellow : Color::Black);
            levelSelectItems[i].setOutlineColor(sf::Color::Black);
        }
    }

    void draw(RenderWindow& window) {
        window.draw(backgroundSprite);
        if (inLeaderBoard) {
            window.draw(leaderBoardTitleText);
            window.draw(leaderBoardRect);
        }
        else if (inOptionsMenu) {
            window.draw(titleText);
            for (int i = 0; i < optionsMenuCount; i++) {
                window.draw(optionsMenuItems[i]);
            }
        }
        else if (inLevelSelect) {
            window.draw(levelSelectTitleText);
            for (int i = 0; i < levelSelectCount; i++) {
                window.draw(levelSelectItems[i]);
            }
        }
        else {
            window.draw(titleText);
            for (int i = 0; i < mainMenuCount; i++) {
                window.draw(mainMenuItems[i]);
            }
        }
    }

    void MoveUp() {
        if (inOptionsMenu) {
            if (optionsSelectedIndex > 0) {
                optionsMenuItems[optionsSelectedIndex].setFillColor(Color::Black);
                optionsSelectedIndex--;
                optionsMenuItems[optionsSelectedIndex].setFillColor(Color::Yellow);
            }
        }
        else if (inLevelSelect) {
            if (levelSelectIndex > 0) {
                levelSelectItems[levelSelectIndex].setFillColor(Color::Black);
                levelSelectIndex--;
                levelSelectItems[levelSelectIndex].setFillColor(Color::Yellow);
            }
        }
        else if (!inLeaderBoard) {
            if (mainSelectedIndex > 0) {
                mainMenuItems[mainSelectedIndex].setFillColor(Color::Black);
                mainSelectedIndex--;
                mainMenuItems[mainSelectedIndex].setFillColor(Color::Yellow);
            }
        }
    }

    void MoveDown() {
        if (inOptionsMenu) {
            if (optionsSelectedIndex < optionsMenuCount - 1) {
                optionsMenuItems[optionsSelectedIndex].setFillColor(Color::Black);
                optionsSelectedIndex++;
                optionsMenuItems[optionsSelectedIndex].setFillColor(Color::Yellow);
            }
        }
        else if (inLevelSelect) {
            if (levelSelectIndex < levelSelectCount - 1) {
                levelSelectItems[levelSelectIndex].setFillColor(Color::Black);
                levelSelectIndex++;
                levelSelectItems[levelSelectIndex].setFillColor(Color::Yellow);
            }
        }
        else if (!inLeaderBoard) {
            if (mainSelectedIndex < mainMenuCount - 1) {
                mainMenuItems[mainSelectedIndex].setFillColor(Color::Black);
                mainSelectedIndex++;
                mainMenuItems[mainSelectedIndex].setFillColor(Color::Yellow);
            }
        }
    }

    void MoveLeft() {
        if (inOptionsMenu && optionsSelectedIndex == 1) {
            if (volumeLevel > 0) {
                volumeLevel--;
                optionsMenuItems[1].setString("volume: " + to_string(volumeLevel));
            }
        }
    }

    void MoveRight() {
        if (inOptionsMenu && optionsSelectedIndex == 1) {
            if (volumeLevel < 100) {
                volumeLevel++;
                optionsMenuItems[1].setString("volume: " + to_string(volumeLevel));
            }
        }
    }

    int GetSelectedIndex() const {
        if (inLevelSelect) return levelSelectIndex;
        return inOptionsMenu ? optionsSelectedIndex : mainSelectedIndex;
    }

    bool IsInOptionsMenu() const {
        return inOptionsMenu;
    }

    bool IsInLeaderBoard() const {
        return inLeaderBoard;
    }

    bool IsInLevelSelect() const {
        return inLevelSelect;
    }

    void EnterSelection() {
        if (inOptionsMenu) {
            if (optionsSelectedIndex == 0) {
                soundEffectsOn = !soundEffectsOn;
                optionsMenuItems[0].setString("sound effects: " + string(soundEffectsOn ? "on" : "off"));
            }
            else if (optionsSelectedIndex == 2) {
                musicOn = !musicOn;
                optionsMenuItems[2].setString("music: " + string(musicOn ? "on" : "off"));
            }
        }
        else if (inLevelSelect) {
            // Selection handled in Game class
        }
        else if (!inLeaderBoard) {
            if (mainSelectedIndex == 2) {
                inOptionsMenu = true;
                mainMenuItems[mainSelectedIndex].setFillColor(Color::Black);
                optionsSelectedIndex = 0;
                optionsMenuItems[0].setFillColor(Color::Yellow);
            }
            else if (mainSelectedIndex == 3) {
                inLeaderBoard = true;
                mainMenuItems[mainSelectedIndex].setFillColor(Color::Black);
            }
            else if (mainSelectedIndex == 4) {
                inLevelSelect = true;
                mainMenuItems[mainSelectedIndex].setFillColor(Color::Black);
                levelSelectIndex = 0;
                levelSelectItems[0].setFillColor(Color::Yellow);
            }
        }
    }

    void ExitLeaderBoard() {
        if (inLeaderBoard) {
            inLeaderBoard = false;
            mainSelectedIndex = 3;
            mainMenuItems[mainSelectedIndex].setFillColor(Color::Yellow);
        }
    }

    void ExitOptionsMenu() {
        if (inOptionsMenu) {
            inOptionsMenu = false;
            optionsMenuItems[optionsSelectedIndex].setFillColor(Color::Black);
            mainSelectedIndex = 2;
            mainMenuItems[mainSelectedIndex].setFillColor(Color::Yellow);
        }
    }

    void ExitLevelSelect() {
        if (inLevelSelect) {
            inLevelSelect = false;
            levelSelectItems[levelSelectIndex].setFillColor(Color::Black);
            mainSelectedIndex = 4;
            mainMenuItems[mainSelectedIndex].setFillColor(Color::Yellow);
        }
    }

    bool GetSoundEffectsState() const {
        return soundEffectsOn;
    }

    bool GetMusicState() const {
        return musicOn;
    }

    int GetVolumeLevel() const {
        return volumeLevel;
    }
};