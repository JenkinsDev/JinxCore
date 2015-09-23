#include "../graphics/window.h"
#include <GLFW\glfw3.h>
#include <iostream>
#include "input.h"

namespace jinx { namespace input {

    using namespace jinx::graphics;

    bool Input::m_Keys[MAX_KEYS];
    bool Input::m_MouseButtons[MAX_BUTTONS];

    double Input::m_MouseX = 0;
    double Input::m_MouseY = 0;

    void Input::init() {
        for (int i = 0; i < MAX_KEYS; i++) {
            m_Keys[i] = false;
        }

        for (int j = 0; j < MAX_BUTTONS; j++) {
            m_MouseButtons[j] = false;
        }
    }

    bool Input::isKeyPressed(unsigned int key) {
        // TODO: LOG THIS!
        if (key >= MAX_KEYS) {
            return false;
        }

        return m_Keys[key];
    }

    bool Input::isMouseButtonPressed(unsigned int button) {
        // TODO: LOG THIS!
        if (button >= MAX_BUTTONS) {
            return false;
        }

        return m_MouseButtons[button];
    }

    void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (!(key >= MAX_KEYS)) {
            m_Keys[key] = action != GLFW_RELEASE;
        }
    }

    void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        if (!(button >= MAX_BUTTONS)) {
            m_MouseButtons[button] = action != GLFW_RELEASE;
        }
    }

    void Input::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
        m_MouseX = xpos;
        m_MouseY = ypos;
    }

} }
