#include<core/window.hpp>


Window::Window(uint16_t width, uint16_t height, char* title)
{
    this->width = width;
    this->height = height;
    this->title = title;
}
bool Window::init() {
    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
     return m_window != nullptr;
   
}

Window::~Window() {
    if (m_window) {
        glfwDestroyWindow(static_cast<GLFWwindow*>(m_window));
    }
}