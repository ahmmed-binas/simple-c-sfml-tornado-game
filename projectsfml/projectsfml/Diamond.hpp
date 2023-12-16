// Diamond.hpp
#ifndef DIAMOND_HPP
#define DIAMOND_HPP

#include <SFML/Graphics.hpp>

class Diamond {
public:
    Diamond();

    void setPosition(const sf::Vector2f& position);
    void draw(sf::RenderWindow& window) const;
    bool isCollected(const sf::FloatRect& playerBounds);
   
    void update(float elapsedTime, float speedFactor);
    void setCollected(bool value);

private:
    sf::ConvexShape diamond;
    sf::Vector2f velocity;
    bool collected;
};

#endif 
