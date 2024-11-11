#include "application.hpp"
#include "window.hpp"

#include<iostream>
Application::Application() {
    // Initialize your application
}

Application::~Application() {
    // Cleanup
}

int Application::run() {
    // Your main application loop
    Window *w1 = new Window(800,600,"renderer");
    bool res = w1->init();
    std::cout<<res;
    return 0;
}