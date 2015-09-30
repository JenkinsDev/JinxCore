#include "main.h"

int main() {
    using namespace jinx::graphics;
    using namespace jinx::input;
    using namespace jinx::utils;

    // Create Our Game Window
    Window window("Jinx Game Engine!", 800, 600);

    // Initialize the Shader Class.
    Shader::init();

    // Create and store our vertices within the newly created
    // vertex buffer object.
    GLfloat vertices[] = {
         0.0f,  0.5f,
         0.5f, -0.5f,
        -0.5f, -0.5f
    };
    Shader::drawTriangle(vertices, sizeof(vertices));
    
    // Load up, read source code and compile, our vertex and
    // fragment shaders.
    GLint vertexShader = Shader::createShaderFromFile(GL_VERTEX_SHADER, "./vertex-shader.vert");
    GLint fragmentShader = Shader::createShaderFromFile(GL_FRAGMENT_SHADER, "./fragment-shader.frag");

    if (vertexShader == -1 || fragmentShader == -1) {
        return -1;
    }

    // Link vertex and fragment shader into a single shader program.
    GLuint shaderProgram = Shader::createProgramFromShaders(vertexShader, fragmentShader);
    
    // Specify the layout of the vertex data.
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    while (!window.closed()) {
        window.clear();

        if (Input::isKeyPressed(GLFW_KEY_W)) {
            Logging::info("Move Forward");
        }
        else if (Input::isKeyPressed(GLFW_KEY_S)) {
            Logging::info("Move Backwards");
        }

        if (Input::isKeyPressed(GLFW_KEY_A)) {
            Logging::info("Move Left");
        }
        else if (Input::isKeyPressed(GLFW_KEY_D)) {
            Logging::info("Move Right");
        }

        if (Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_1)) {
            Logging::info("Mouse Button 1 Pressed");
        }
        else if (Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_2)) {
            Logging::info("Mouse Button 2 Pressed");
        }

        // Change the background to black and draw our triangle based on our current
        // OpenGL shader program.
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.update();
    }

    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    return 0;
}
