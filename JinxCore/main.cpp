#include <iostream>
#include <fstream>
#include <string>
#include "src/graphics/window.h"
#include "src/input/input.h"

std::string loadShaderFile(std::string fileName) {
    using namespace std;

    ifstream ifs(fileName);
    string content(
            (istreambuf_iterator<char>(ifs)),
            (istreambuf_iterator<char>())
        );

    return content;
}

GLboolean didShaderCompile(GLuint shader) {
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    return status == GL_TRUE;
}

GLint createShader(GLuint shaderType, GLchar shaderFile[]) {
    GLuint shader = glCreateShader(shaderType);
    std::string shaderSourceString = loadShaderFile(shaderFile);
    const GLchar* shaderSource = shaderSourceString.c_str();

    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    if (!didShaderCompile(shader)) {
        char compileBuffer[512];
        glGetShaderInfoLog(shader, 512, NULL, compileBuffer);

        std::cout << "Shader (" << shader << ") Failed To Compile.  Error:" << std::endl;
        std::cout << compileBuffer << std::endl;

        system("PAUSE");
        return -1;
    }

    return shader;
}

int main() {
    using namespace jinx::graphics;
    using namespace jinx::input;

    // Create Our Game Window
    Window window("Jinx Game Engine!", 800, 600);

    // Create OpenGL Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create OpenGL Vertex Buffer Object
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // Create and store our vertices within the newly created
    // vertex buffer object.
    GLfloat vertices[] = {
         0.0f,  0.5f,
         0.5f, -0.5f,
        -0.5f, -0.5f
    };
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Load up, read source code and compile, our vertex and
    // fragment shaders.
    GLint vertexShader = createShader(GL_VERTEX_SHADER, "./vertex-shader.vert");
    GLint fragmentShader = createShader(GL_FRAGMENT_SHADER, "./fragment-shader.frag");

    if (vertexShader == -1 || fragmentShader == -1) {
        return -1;
    }
    
    // Link vertex and fragment shader into a single shader program.
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    
    // Specify the layout of the vertex data.
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    while (!window.closed()) {
        window.clear();

        if (Input::isKeyPressed(GLFW_KEY_W)) {
            std::cout << "Move forward" << std::endl;
        }
        else if (Input::isKeyPressed(GLFW_KEY_S)) {
            std::cout << "Move Backward" << std::endl;
        }

        if (Input::isKeyPressed(GLFW_KEY_A)) {
            std::cout << "Move Left" << std::endl;
        }
        else if (Input::isKeyPressed(GLFW_KEY_D)) {
            std::cout << "Move Right" << std::endl;
        }

        if (Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_1)) {
            std::cout << "Mouse Button 1 Pressed" << std::endl;
        }
        else if (Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_2)) {
            std::cout << "Mouse Button 2 Pressed" << std::endl;
        }

        std::cout << "Mouse Position: " << Input::getMouseX() << ", " << Input::getMouseY() << std::endl;

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