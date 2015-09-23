#include <iostream>
#include "window.h"
#include "../input/input.h"

namespace jinx { namespace graphics {

    using namespace jinx::input;

    Window::Window(const char *name, int width, int height) {
        m_Name = name;
        m_Width = width;
        m_Height = height;

        if (!init()) {
            glfwTerminate();
        }
    }

    Window::~Window() {
        glfwTerminate();
    }

    bool Window::init() {
        if (!glfwInit()) {
            std::cout << "GLFW Failed To Init" << std::endl;
            return false;
        }

        m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, NULL, NULL);

        if (!m_Window) {
            std::cout << "Failed to create GLFW Window." << std::endl;
            return false;
        }

        Input::init();

        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, this);

        glfwSetKeyCallback(m_Window, Input::keyCallback);
        glfwSetMouseButtonCallback(m_Window, Input::mouseButtonCallback);
        glfwSetCursorPosCallback(m_Window, Input::cursorPositionCallback);
        glfwSetWindowSizeCallback(m_Window, Window::windowResize);

        // We have to init GLEW after setting the window's context, as above
        // or else GLEW will not be able to be initialized.
        if (glewInit() != GLEW_OK) {
            std::cout << "Could not intialize GLEW." << std::endl;
            return false;
        }

        std::cout << "OPENGL " << glGetString(GL_VERSION) << std::endl;

        return true;
    }

    void Window::clear() const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::update() {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    bool Window::closed() const {
        if (glfwWindowShouldClose(m_Window)) {
            glfwTerminate();
            return true;
        }

        return false;
    }

    void Window::windowResize(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

} }