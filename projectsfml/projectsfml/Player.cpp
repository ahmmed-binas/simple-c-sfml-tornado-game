// Player.cpp
#include "Player.hpp"

Player::Player(sf::Vector2f initialPosition, float speed, BitmapHandler& bitmapHandler)
    : position(initialPosition), speed(speed), bitmapHandler(bitmapHandler) {

    playerShape.setSize(sf::Vector2f(50.0f, 50.0f));
    playerShape.setFillColor(sf::Color::Green);
    playerShape.setPosition(position);
}

void Player::move(const sf::Vector2f& offset) {
    position += offset;
    playerShape.setPosition(position);
   bitmapHandler.move(offset);
}

void Player::handleInput() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        move(sf::Vector2f(-speed, 0.0f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        move(sf::Vector2f(speed, 0.0f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        move(sf::Vector2f(0.0f, -speed));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        move(sf::Vector2f(0.0f, speed));
    }
}

void Player::update() {
    float moveSpeed = 100.0f;


    bitmapHandler.update();
}

void Player::draw(sf::RenderWindow& window) const {

    window.draw(playerShape);


    bitmapHandler.draw(window);
}
