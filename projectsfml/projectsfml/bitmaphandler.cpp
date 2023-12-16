// BitmapHandler.cpp
#include "bitmaphandler.hpp"
#include <iostream>
#include <SFML/System/Clock.hpp>

BitmapHandler::BitmapHandler()
    : currentFrame(0), initialScale(1.0f), diamondCount(0) {
    sprite.setPosition(300.0f, 100.0f);

    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    diamondCountText.setFont(font);
    diamondCountText.setCharacterSize(20);
    diamondCountText.setFillColor(sf::Color::White);
    diamondCountText.setPosition(10.0f, 10.0f);
}

void BitmapHandler::loadTextures() {
    for (int i = 1; i <= 16; ++i) {
        std::string filename = (i < 10 ? "0" : "") + std::to_string(i) + ".bmp";
        if (!textures[i - 1].loadFromFile(filename)) {
            std::cerr << "Error loading image: " << filename << std::endl;
        }
    }
}

void BitmapHandler::update() {
    static sf::Clock clock;
    float moveSpeed = 100.0f;
    float elapsedSeconds = clock.restart().asSeconds();

    // Movement code...
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sprite.move(-moveSpeed * elapsedSeconds, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sprite.move(moveSpeed * elapsedSeconds, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        sprite.move(0, -moveSpeed * elapsedSeconds);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        sprite.move(0, moveSpeed * elapsedSeconds);
    }

    // Check for collisions with diamonds
    sf::FloatRect playerBounds = sprite.getGlobalBounds();
    for (auto& diamond : diamonds) {
        if (diamond.isCollected(playerBounds)) {
            diamondCount++;
        }
    }
}

void BitmapHandler::draw(sf::RenderWindow& window)const {
    for (int i = 0; i <= 16; ++i) {
        sf::Sprite sprite(textures[i]);

        // Adjust the scale as needed
        sprite.setScale(0.6f, 0.7f); // Set your desired scale

        // Draw the sprite
        window.draw(sprite);
    }
}

void BitmapHandler::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);
}

void BitmapHandler::move(const sf::Vector2f& offset) {
    sf::Vector2f currentPosition = sprite.getPosition();
    sprite.setPosition(currentPosition + offset);
}

void BitmapHandler::setInitialScale(float scale) {
    initialScale = scale;
    sprite.setScale(initialScale, initialScale);
}

void BitmapHandler::spawnDiamond() {
    Diamond diamond;
    diamonds.push_back(diamond);
}

void BitmapHandler::drawDiamondCount(sf::RenderWindow& window) const {
    const_cast<sf::Text&>(diamondCountText).setString("Diamonds: " + std::to_string(diamondCount));
    window.draw(diamondCountText);
}

bool BitmapHandler::checkCollisions(Diamond& diamond) {
    sf::FloatRect playerBounds = sprite.getGlobalBounds();
    if (diamond.isCollected(playerBounds)) {
        diamondCount++;
        diamond.setCollected(true);
        return true;
    }
    return false;
}

void BitmapHandler::animate(sf::RenderWindow& window, int frameCount, float animationSpeed) {
    sf::Clock animationClock;
    sf::Clock elapsedClock;  // Add this line to measure elapsed time

    // Create and position diamonds
    const int numberOfDiamonds = 7; // Set the desired number of diamonds
    std::vector<Diamond> diamonds;

    for (int i = 0; i < numberOfDiamonds; ++i) {
        Diamond diamond;
        float x = static_cast<float>(rand() % 700 + 50);
        float y = static_cast<float>(rand() % 800 + 50);
        diamond.setPosition(sf::Vector2f(x, y));
        diamonds.push_back(diamond);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

       
        float elapsedTime = elapsedClock.restart().asSeconds();

       
        float speedFactor = 0.1f; 
        for (auto& diamond : diamonds) {
            diamond.update(elapsedTime, speedFactor);
            diamond.draw(window);

            if (checkCollisions(diamond)) {
                
                diamond.setCollected(true);
            }
        }

        update();

        if (animationClock.getElapsedTime().asSeconds() >= animationSpeed) {
            currentFrame = (currentFrame + 1) % frameCount;
            sprite.setTexture(textures[currentFrame]);
            animationClock.restart();
        }

        window.clear();

        
        for (const auto& diamond : diamonds) {
            diamond.draw(window);
        }

       
        window.draw(sprite);

        drawDiamondCount(window);
        window.display();
    }
}
