#include "App.h"

int main() {
    ball_sim::App app(800, 800, "Ball Sim");
    
    // Optionally add extra test balls:
    // app.addRandomBall();
    
    app.run();
    return 0;
}