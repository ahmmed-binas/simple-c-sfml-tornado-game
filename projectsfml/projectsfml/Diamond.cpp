// Diamond.cpp
#include "Diamond.hpp"
#include <iostream>

Diamond::Diamond() : collected(false) {
    diamond.setPointCount(4);
    diamond.setPoint(0, sf::Vector2f(0, -20));
    diamond.setPoint(1, sf::Vector2f(20, 0));
    diamond.setPoint(2, sf::Vector2f(0, 20));
    diamond.setPoint(3, sf::Vector2f(-20, 0));

    diamond.setFillColor(sf::Color::Cyan);

    
    velocity.x = static_cast<float>(rand() % 100 - 10); 
    velocity.y = static_cast<float>(rand() % 100 - 80); 
}

void Diamond::setPosition(const sf::Vector2f& position) {
    diamond.setPosition(position);
}

void Diamond::draw(sf::RenderWindow& window) const {
    if (!collected) {
        window.draw(diamond);
    }
}

bool Diamond::isCollected(const sf::FloatRect& playerBounds) {
    if (!collected && diamond.getGlobalBounds().intersects(playerBounds)) {
        collected = true;
        return true;
    }
    return false;
}
void Diamond::update(float elapsedTime, float speedFactor) {
    
    diamond.move(velocity * (elapsedTime * speedFactor));

    
    std::cout << "Diamond Position: (" << diamond.getPosition().x << ", " << diamond.getPosition().y << ")\n";

 
    sf::Vector2f diamondPosition = diamond.getPosition();
    sf::Vector2f diamondSize = diamond.getTransform().transformRect(diamond.getLocalBounds()).getSize();

    if (diamondPosition.x < 0 || diamondPosition.x + diamondSize.x > 800) {
        velocity.x = -velocity.x;
    }

    if (diamondPosition.y < 0 || diamondPosition.y + diamondSize.y > 600) {
        velocity.y = -velocity.y;
    }
}

void Diamond::setCollected(bool value) {
    collected = value;
}
