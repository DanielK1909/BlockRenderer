#include "Input.h"

std::vector<Input*> Input::input_instances_;

Input::Input() {
	input_instances_.push_back(this);

	keys_ = std::vector<bool>(349, false);
	buttons_ = std::vector<bool>(8, false);

	mouse_x_ = 0.f;
	mouse_y_ = 0.f;
}

void Input::setGLFWWindow(GLFWwindow* window) {
	window_ = window;

	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetScrollCallback(window, scrollCallback);
}

Input* Input::findInstanceByWindow(GLFWwindow* window) {
	for (Input* i : input_instances_) {
		if (i->getGLFWWindow() == window) {
			return i;
		}
	}

	return nullptr;
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	findInstanceByWindow(window)->setKeyDown(key, action != GLFW_RELEASE);
}

void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	findInstanceByWindow(window)->setButtonDown(button, action != GLFW_RELEASE);
}

void Input::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
	findInstanceByWindow(window)->setMousePosition(xpos, ypos);
}

void Input::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	findInstanceByWindow(window)->scroll(yoffset);
}
