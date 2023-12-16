// BitmapHandler.hpp
#ifndef BITMAP_HANDLER_HPP
#define BITMAP_HANDLER_HPP

#include <SFML/Graphics.hpp>
#include "Diamond.hpp"

class BitmapHandler {
public:
    BitmapHandler();
    const std::vector<Diamond>& getDiamonds() const;
    void loadTextures();
    void update();
    void draw(sf::RenderWindow& window) const;
    void setPosition(const sf::Vector2f& position);
    void move(const sf::Vector2f& offset);
    void setInitialScale(float scale);
    void spawnDiamond();
    bool checkCollisions(Diamond& diamond);
    void animate(sf::RenderWindow& window, int frameCount, float animationSpeed);
    void drawDiamondCount(sf::RenderWindow& window) const;

private:
    sf::Sprite sprite;
    sf::Texture textures[16];
    std::vector<Diamond> diamonds;
    int currentFrame;
    float initialScale;
    int diamondCount;
    sf::Font font;
    sf::Text diamondCountText;
};

#endif // BITMAP_HANDLER_HPP
