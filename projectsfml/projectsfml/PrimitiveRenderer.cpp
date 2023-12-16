#include "Engine.hpp"

void Engine::render() {
  

    int x0 = 50, y0 = 100;
    int x1 = 400, y1 = 300;

    int deltaX = x1 - x0;
    int deltaY = y1 - y0;


    bool isSteep = std::abs(deltaY) > std::abs(deltaX);

    if (isSteep) {
        std::swap(x0, y0);

        std::swap(x1, y1);
    }


    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    deltaX = x1 - x0;
    deltaY = y1 - y0;

    int yStep = (y0 < y1) ? 1 : -1;


    int decisionParameter = 2 * std::abs(deltaY) - deltaX;

    sf::Vertex pixel;
    pixel.position = isSteep ? sf::Vector2f(y0, x0) : sf::Vector2f(x0, y0);
    pixel.color = sf::Color::White;
    window.draw(&pixel, 1, sf::Points);

    for (int x = x0 + 1, y = y0; x <= x1; ++x) {
        
        decisionParameter += 2 * std::abs(deltaY);

        
        if (decisionParameter > 0) {
            y += yStep;
            decisionParameter -= 2 * deltaX;
        }

       
        pixel.position = isSteep ? sf::Vector2f(y, x) : sf::Vector2f(x, y);
        pixel.color = sf::Color::White;
        window.draw(&pixel, 1, sf::Points);
    }


    sf::VertexArray rectangle(sf::Lines, 8);
    rectangle[0].position = sf::Vector2f(100, 100);
    rectangle[0].color = sf::Color::Red;

    rectangle[1].position = sf::Vector2f(400, 100);
    rectangle[1].color = sf::Color::Blue;

    rectangle[2].position = sf::Vector2f(400, 100);
    rectangle[2].color = sf::Color::Green;

    rectangle[3].position = sf::Vector2f(400, 400);
    rectangle[3].color = sf::Color::Yellow;

    rectangle[4].position = sf::Vector2f(400, 400);
    rectangle[4].color = sf::Color::Magenta;

    rectangle[5].position = sf::Vector2f(100, 400);
    rectangle[5].color = sf::Color::Cyan;

    rectangle[6].position = sf::Vector2f(100, 400);
    rectangle[6].color = sf::Color::White;

    rectangle[7].position = sf::Vector2f(100, 100);
    rectangle[7].color = sf::Color::Red;

    currentFrameBuffer->draw(rectangle);
    window.draw(rectangle);

    
    currentFrameBuffer->clear();

    
    currentFrameBuffer->draw(rectangle);

    currentFrameBuffer->display();



  

    sf::VertexArray line(sf::Lines, 2);
    line[0].position = isSteep ? sf::Vector2f(y0, x0) : sf::Vector2f(x0, y0);
    line[0].color = sf::Color::White;
    line[1].position = isSteep ? sf::Vector2f(y1, x1) : sf::Vector2f(x1, y1);
    line[1].color = sf::Color::White;

   


   
    int nextBufferIndex = (currentFrameBuffer - renderTextures + 1) % bufferCount;
    currentFrameBuffer = &renderTextures[nextBufferIndex];

  
    std::cout << "Current Frame Buffer: " << nextBufferIndex << std::endl;

   
    window.clear();
    window.draw(sf::Sprite(currentFrameBuffer->getTexture()));
    window.draw(line);
    
    window.draw(sprite);

    window.display();
}