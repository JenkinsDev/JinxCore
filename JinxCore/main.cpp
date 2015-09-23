#include <iostream>
#include "src/graphics/window.h"
#include "src/input/input.h"

int main() {
	using namespace jinx::graphics;
	using namespace jinx::input;

	Window window("Jinx Game Engine!", 800, 600);

	glClearColor(0.2f, 0.3f, 1.0f, 1.0f);

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

		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();

		window.update();
	}

	return 0;
}