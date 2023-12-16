#include "Engine.hpp"
#include "PrimitiveRenderer.hpp"
#include "Player.hpp" 
#include "LineSegment.cpp" 
#include "GameObject.hpp"
#include "BitmapHandler.hpp" 

Engine::Engine(int screenWidth, int screenHeight, bool fullscreen, int bufferCount)
    : window(sf::VideoMode(screenWidth, screenHeight), "SFML 2D Engine", fullscreen ? sf::Style::Fullscreen : sf::Style::Default),
    bufferCount(bufferCount) {
  
    initGraphics();


    sf::VideoMode videoMode(screenWidth, screenHeight);

    if (fullscreen) {
        videoMode = sf::VideoMode::getFullscreenModes()[0];
    }

    window.create(videoMode, "SFML 2D Engine", fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
}

void Engine::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();

        processEvents();
        update(elapsed);
        render();
    }
}

bool Engine::initGraphics() {
    return true;
}

void Engine::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

       
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
    }
}

void Engine::update(sf::Time elapsed) {
    float moveSpeed = 100.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sprite.move(-moveSpeed * elapsed.asSeconds(), 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sprite.move(moveSpeed * elapsed.asSeconds(), 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        sprite.move(0, -moveSpeed * elapsed.asSeconds());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        sprite.move(0, moveSpeed * elapsed.asSeconds());
    }


}





void Engine::render() {

    PrimitiveRenderer renderer;

    int nextBufferIndex = (currentFrameBuffer - renderTextures + 1) % bufferCount;
    currentFrameBuffer = &renderTextures[nextBufferIndex];

    // Clear the window

    // Uncomment and use the rendering code you need
    window.clear();
     //renderer.drawRectangle(window);

    // int x0 = 50, y0 = 10;
    // int x1 = 500, y1 = 300;
    // renderer.drawLineAlgorithm(window, x0, y0, x1, y1);

    //int circleX = 500;
     //int circleY = 200;
      //int circleRadius = 50;
     //renderer.drawCircle(window, circleX, circleY, circleRadius, sf::Color::Red, sf::Color::Green);

 //  BitmapHandler game;
   //game.loadTextures();
   //srand(static_cast<unsigned>(time(nullptr)));

   //game.animate(window, 5, 0.2f);
   //diamond.draw(window);




       //player--------
   //BitmapHandler bitmapHandler;



   // Player player(sf::Vector2f(100.0f, 100.0f), 200.0f, bitmapHandler);

     //   player.handleInput();
       //player.update();  // Pass the elapsed time if needed
        //player.draw(window);






    // int ellipseX = 500;
    // int ellipseY = 200;
    // int ellipseA = 80;
    // int ellipseB = 40;
    // renderer.drawEllipseAlgorithm(window, ellipseX, ellipseY, ellipseA, ellipseB, sf::Color::Magenta);

    //Point2D zigzagStartPoint(400.0f, 100.0f);
     //Point2D zigzagEndPoint(200.0f, 100.0f);
     //LineSegment::drawZigzagLine(window, zigzagStartPoint, zigzagEndPoint, 5, 1.0f);

    // GameObject gameObject;
   //  gameObject.translate(100.0f, 100.0f);
    // gameObject.rotate(100.0f);
    // gameObject.scale(0.222f);
    // gameObject.draw(window);

    // Player player(sf::Vector2f(100.0f, 100.0f), 200.0f);
    // float deltaTime = 0.0f;
    // player.update(deltaTime);
    // player.draw(window);

 //BitmapHandler bitmapHandler;
  //   bitmapHandler.loadTextures();
    // bitmapHandler.setInitialScale(0.111f);
  //bitmapHandler.animate(window, 5, 0.2f);



  // BitmapHandler game;
   //game.loadTextures();
   //srand(static_cast<unsigned>(time(nullptr)));
   //game.animate(window, 5, 0.2f);

 /////----------Tornado----GAME------------------///////////
    BitmapHandler bitmapHandler;
   bitmapHandler.loadTextures();
   
    srand(static_cast<unsigned>(time(nullptr)));;
    bitmapHandler.animate(window, 5, 0.2f);
    
    

 


window.display();









}
