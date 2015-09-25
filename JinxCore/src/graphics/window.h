#ifndef __JINX_GRAPHICS_WINDOW_H
#define __JINX_GRAPHICS_WINDOW_H

#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "../input/input.h"

namespace jinx { namespace graphics {

    class Window
    {
    private:
        const char *m_Name;
        int m_Width, m_Height;
        GLFWwindow *m_Window;
        bool m_Closed;
    public:
        Window(const char *name, int width, int height);
        ~Window();
        bool closed() const;
        void update();
        void clear() const;

        inline int getWidth() const { return m_Width; }
        inline int getHeight() const { return m_Height; }

        static void windowResize(GLFWwindow* window, int width, int height);
    private:
        bool init();
    };

} }

#endif