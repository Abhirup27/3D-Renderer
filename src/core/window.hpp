#pragma once

#include<glfw/glfw3.h>

class Window {
public:
  Window(uint16_t width, uint16_t height, char* title);
  ~Window();
    
    bool init();
    void update();
  
private:
    uint16_t width, height;
    char* title;
    GLFWwindow* m_window;
};
