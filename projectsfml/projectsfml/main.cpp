#include "Engine.hpp";
int main() {
    int screenWidth = 800;
    int screenHeight = 600;
    bool fullscreen = false;
    int bufferCount = 3;

    Engine engine(screenWidth, screenHeight, fullscreen, bufferCount);
    engine.run();

    return 0;
}