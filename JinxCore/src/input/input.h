#ifndef __JINX_INPUT_INPUT_H
#define __JINX_INPUT_INPUT_H

#include <GLFW\glfw3.h>
#include "../utils/logging.h"

namespace jinx { namespace input {

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

    class Input {
    private:
        static bool m_Keys[MAX_KEYS];
        static bool m_MouseButtons[MAX_BUTTONS];
        static double m_MouseX, m_MouseY;
    public:
        static void init();
        
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
        
        static bool isMouseButtonPressed(unsigned int button);
        static bool isKeyPressed(unsigned int key);

        static inline double getMouseX() { return m_MouseX; };
        static inline double getMouseY() { return m_MouseY; };
    };

} }

#endif