#include "App.h"

int main() {
    ball_sim::App app(800, 800, "Ball Sim");
    
    // Optionally add extra test balls:
    for(int i = 0; i < 15; ++i) {
        app.addRandomBall();
    }
    
    app.run();

    return 0;
}