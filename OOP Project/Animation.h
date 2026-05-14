#pragma once
#include <SFML/Graphics.hpp>
#include <string>


using namespace sf;
using namespace std;

class Animation {
private:
    Texture texture;
    int frameWidth;
    int frameHeight;
    int totalFrames;

public:
    Animation(const string& filepath, int frameW, int frameH, int frames): frameWidth(frameW), frameHeight(frameH), totalFrames(frames) {
        texture.loadFromFile(filepath);
    }

    void applyFrame(Sprite& sprite, int frameIndex) {
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(frameIndex % totalFrames * frameWidth, 0, frameWidth, frameHeight));
    }

    const Texture& getTexture() const {
        return texture;
    }
};