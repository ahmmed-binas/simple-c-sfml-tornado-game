#pragma once

#include <SFML/Graphics.hpp>
#include "bitmaphandler.hpp"  /

class Player {
public:
    Player(sf::Vector2f initialPosition, float speed, BitmapHandler& bitmapHandler);
    void move(const sf::Vector2f& offset);
    void handleInput();
    void update();
    void draw(sf::RenderWindow& window) const;

private:
    BitmapHandler sprite;
    sf::Vector2f position;
    float speed;
    BitmapHandler& bitmapHandler;
    sf::RectangleShape playerShape;
};

