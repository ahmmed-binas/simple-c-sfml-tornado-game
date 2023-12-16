#pragma once
#include "PrimitiveRenderer.hpp"
#include <SFML/Graphics.hpp>
#include "Engine.hpp"

class GameObject {
private:
    PrimitiveRenderer renderer;
    sf::Sprite sprite;
public:

    void draww(sf::RenderWindow& window) {
      
        window.draw(sprite);
    }
    void setTexture(const sf::Texture& texture) {
        sprite.setTexture(texture);
    }
    void draw(sf::RenderWindow& window) {
        renderer.drawRectangle(window);
    }

    void translate(float dx, float dy) {
        renderer.translate(dx, dy);
    }

    void rotate(float angle) {
        renderer.rotate(angle);
    }

    void scale(float factor) {
        renderer.scale(factor);
    }



};
