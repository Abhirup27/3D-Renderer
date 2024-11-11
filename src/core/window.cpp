#include<core/window.hpp>


Window::Window(uint16_t width, uint16_t height, char* title)
{
    this->width = width;
    this->height = height;
    this->title = title;
}
bool Window::init() {
    glfwSetErrorCallback(errorCallback);

	if (!glfwInit())
        log_fatal("GLFW FAILED TO INITIALIZE");
		//exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#endif
    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!m_window)
	{
        log_fatal("Failed to create GLFW window");
		glfwTerminate();
        return -1;
		//exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
        log_fatal("Failed to initialize GLAD");
		glfwTerminate();
		//exit(EXIT_FAILURE);
	}

    glViewport(0,0,width,height);
     return m_window != nullptr;
   
}

void Window::update()
{
    while(!glfwWindowShouldClose(m_window))
    {
        glfwSwapBuffers(m_window);
        glfwPollEvents();    
        // call render update here
    }

}

Window::~Window() {
    if (m_window) {
        glfwDestroyWindow(static_cast<GLFWwindow*>(m_window));
    }
}

void Window::errorCallback(int error, const char* desc)
{
    log_error(desc);

}