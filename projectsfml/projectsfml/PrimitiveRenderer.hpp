#pragma once



#include <SFML/Graphics.hpp>
#include <cmath> 
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class PrimitiveRenderer {
private:
    sf::Vector2f getCenter() {
        sf::Vector2f center(0, 0);
        for (int i = 0; i < 8; ++i) {
            center += rectangle[i].position;
        }
        center /= 8.0f;
        return center;
    }

    sf::VertexArray rectangle;

public:

    PrimitiveRenderer() {

        rectangle = sf::VertexArray(sf::Lines, 8);
        rectangle[0].position = sf::Vector2f(100, 100);
        rectangle[1].position = sf::Vector2f(400, 100);
        rectangle[2].position = sf::Vector2f(400, 100);
        rectangle[3].position = sf::Vector2f(400, 400);
        rectangle[4].position = sf::Vector2f(400, 400);
        rectangle[5].position = sf::Vector2f(100, 400);
        rectangle[6].position = sf::Vector2f(100, 400);
        rectangle[7].position = sf::Vector2f(100, 100);

        // Set initial vertex colors for each side
        rectangle[0].color = sf::Color::Red;
        rectangle[1].color = sf::Color::Green;
        rectangle[2].color = sf::Color::Blue;
        rectangle[3].color = sf::Color::Yellow;
        rectangle[4].color = sf::Color::Magenta;
        rectangle[5].color = sf::Color::Cyan;
        rectangle[6].color = sf::Color::White;
        rectangle[7].color = sf::Color::Black; // Adjust color for the closing side
    }

    void drawRectangle(sf::RenderWindow& window) {
        window.draw(rectangle);
    }

    // Translate the rectangle
    void translate(float dx, float dy) {
        for (int i = 0; i < 8; ++i) {
            rectangle[i].position.x += dx;
            rectangle[i].position.y += dy;
        }
    }

    // Rotate the rectangle (angle in degrees)
    void rotate(float angle) {
        sf::Vector2f center = getCenter();
        float radianAngle = angle * 3.14159 / 180.0;

        for (int i = 0; i < 8; ++i) {
            sf::Vector2f oldPos = rectangle[i].position - center;
            rectangle[i].position.x = center.x + oldPos.x * cos(radianAngle) - oldPos.y * sin(radianAngle);
            rectangle[i].position.y = center.y + oldPos.x * sin(radianAngle) + oldPos.y * cos(radianAngle);
        }
    }

    // Scale the rectangle
    void scale(float factor) {
        sf::Vector2f center = getCenter();

        for (int i = 0; i < 8; ++i) {
            rectangle[i].position = center + (rectangle[i].position - center) * factor;
        }
    }










    void drawLineAlgorithm(sf::RenderWindow& window, int x0, int y0, int x1, int y1) {
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
    }







    //drawing cirle and filling///using borderfill meathod
    void drawCircle(sf::RenderWindow& window, int centerX, int centerY, int radius, sf::Color outlineColor, sf::Color fillColor) {
        drawCircleOutline(window, centerX, centerY, radius, outlineColor);
        fillCircle(window, centerX, centerY, radius, fillColor);
    }

    void drawCircleOutline(sf::RenderWindow& window, int centerX, int centerY, int radius, sf::Color outlineColor) {
        for (int angle = 0; angle <= 360; ++angle) {
            int x = static_cast<int>(radius * std::cos(angle * M_PI / 180.0));
            int y = static_cast<int>(radius * std::sin(angle * M_PI / 180.0));

            drawPixel(window, centerX + x, centerY + y, outlineColor);
        }
    }

    void fillCircle(sf::RenderWindow& window, int centerX, int centerY, int radius, sf::Color fillColor) {
        for (int y = -radius; y <= radius; ++y) {
            for (int x = -radius; x <= radius; ++x) {
                if (x * x + y * y <= radius * radius) {
                    drawPixel(window, centerX + x, centerY + y, fillColor);
                }
            }
        }
    }






    /// drawing eclipse using algorifthm

    void drawEllipseAlgorithm(sf::RenderWindow& window, int centerX, int centerY, int a, int b, sf::Color color) {
        float angleIncrement = 2 * M_PI / 360.0;

        for (int i = 0; i < 360; i++) {
            float angle = i * angleIncrement;
            int x = static_cast<int>(centerX + a * std::cos(angle));
            int y = static_cast<int>(centerY + b * std::sin(angle));
            drawPixel(window, x, y, color);
        }
    }
    void drawPixel(sf::RenderWindow& window, int x, int y, sf::Color color) {
        sf::Vertex pixel;
        pixel.position = sf::Vector2f(x, y);
        pixel.color = color;
        window.draw(&pixel, 1, sf::Points);
    }






    static void drawLine(sf::RenderWindow& window, int x0, int y0, int x1, int y1, sf::Color color) {
        int deltaX = std::abs(x1 - x0);
        int deltaY = std::abs(y1 - y0);
        int xStep = (x0 < x1) ? 1 : -1;
        int yStep = (y0 < y1) ? 1 : -1;
        int error = deltaX - deltaY;
        PrimitiveRenderer renderer;
        while (x0 != x1 || y0 != y1) {
            // Draw a pixel at (x0, y0)
            renderer.drawPixel(window, x0, y0, color);

            int doubleError = error * 2;
            if (doubleError > -deltaY) {
                error -= deltaY;
                x0 += xStep;
            }
            if (doubleError < deltaX) {
                error += deltaX;
                y0 += yStep;
            }
        }
    }





};

