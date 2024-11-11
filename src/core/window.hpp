#pragma once
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include<glfw/glfw3.h>
#include<utils/logger.hpp>
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
    static void errorCallback(int error, const char* desc);
};
