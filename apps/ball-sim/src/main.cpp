#include "App.h"
#include "core/utils/Logger.h"
#include <iostream>

int main() {
    core::util::Logger::init();

    LOG_INFO("========================================");
    LOG_INFO("Starting Physics Lab - Ball Sim");
    LOG_INFO("========================================");

    // TODO: Add a config parser into this, research differen formats but leanign towards JSON
    // LOG_INFO("Initializing Application ({}x{}) Title: '{}'", 
    //          config.window_width, config.window_height, config.window_title);

    ball_sim::App app(800, 800, "Ball Sim");

    LOG_INFO("Application initialized successfully. Entering main loop.");
    
    app.run();

    LOG_INFO("Application shut down cleanly.");
    core::util::Logger::shutdown(); 
    return 0;
}