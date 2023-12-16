#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>

class Engine {
public:
    Engine(int screenWidth, int screenHeight, bool fullscreen, int bufferCount);

    void run();

private:

    sf::RenderWindow window;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RenderTexture renderTextures[3];
    sf::RenderTexture* currentFrameBuffer;
    sf::CircleShape circle;



    int bufferCount;

    bool initGraphics();

    void processEvents();

    void update(sf::Time elapsed);

    void render();
};
