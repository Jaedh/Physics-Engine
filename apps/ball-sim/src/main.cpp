#include "App.h"
#include <iostream>

int main() {
    ball_sim::App app(
        800, 
        800, 
        "Ball Sim"
    );

    std::cout << "Application started." << std::endl;
    
    app.run();

    std::cout << "Application exited successfully."<<std::endl;

    return 0;
}