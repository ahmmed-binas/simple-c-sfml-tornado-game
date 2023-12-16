#include "PrimitiveRenderer.hpp"

class Point2D {
public:
    float x, y;

    Point2D(float x, float y) : x(x), y(y) {}
};


class LineSegment {
private:
    Point2D start;
    Point2D end;

public:
    LineSegment(const Point2D& start, const Point2D& end) : start(start), end(end) {}

    
    Point2D getStart() const {
        return start;
    }

    Point2D getEnd() const {
        return end;
    }

   
    void setStart(const Point2D& newStart) {
        start = newStart;
    }

    void setEnd(const Point2D& newEnd) {
        end = newEnd;
    }

    
    void draw(sf::RenderWindow& window) const {
       
        int x0 = static_cast<int>(start.x);
        int y0 = static_cast<int>(start.y);
        int x1 = static_cast<int>(end.x);
        int y1 = static_cast<int>(end.y);

        
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x0, y0)),
            sf::Vertex(sf::Vector2f(x1, y1))
        };
        PrimitiveRenderer renderer;
        renderer.drawLine(window, x0, y0, x1, y1, sf::Color::White); 
    }


    
    static void drawZigzagLine(sf::RenderWindow& window, const Point2D& start, const Point2D& end, int numSegments, float amplitude) {
       
        float dx = (end.x - start.x) / (numSegments - 1);
        float dy = (end.y - start.y) / (numSegments - 1);

       
        for (int i = 0; i < numSegments - 1; ++i) {
            Point2D zigzagStart(start.x + i * dx, start.y + i * dy);
            Point2D zigzagEnd(start.x + (i + 1) * dx, start.y + (i + 1) * dy + (i % 2 == 0 ? amplitude : -amplitude));

          
            LineSegment(zigzagStart, zigzagEnd).draw(window);
        }
    }
};
