#include "application.hpp"
#include "window.hpp"

Application::Application() {
    // Initialize your application
}

Application::~Application() {
    // Cleanup
}

int Application::run() {
    // Your main application loop
    log_info("GLFW window init start.");
    Window *w1 = new Window(800,600,"renderer");
    bool res = w1->init();
    if(res ==1)
    {
    log_info("GLFW window succesfully initialized.");
    }
    w1->update();
    
    return 0;
}