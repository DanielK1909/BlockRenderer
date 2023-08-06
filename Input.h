#pragma once

#include <vector>
#include "GLFW/glfw3.h"

class Input {
public:

	static std::vector<Input*> input_instances_;

	Input();
	void setGLFWWindow(GLFWwindow* window);
	inline GLFWwindow* getGLFWWindow() { return window_; }

	inline bool isKeyDown(unsigned int key) { return keys_[key]; };
	inline void setKeyDown(unsigned int key, bool down) { keys_[key] = down; }

	inline bool isButtonDown(unsigned int button) { return buttons_[button]; }
	inline void setButtonDown(unsigned int button, bool down) { buttons_[button] = down; }

	inline void setMousePosition(float x, float y) { mouse_x_ = x; mouse_y_ = y; glfwSetCursorPos(window_, x, y); }
	inline float getMouseX() { return mouse_x_; }
	inline float getMouseY() { return mouse_y_; }

	inline void setMouseScroll(double scroll) { mouse_scroll_ = scroll; }
	inline void scroll(double offset) { mouse_scroll_ += offset; }
	inline double getMouseScroll() { return mouse_scroll_; }

	static Input* findInstanceByWindow(GLFWwindow* window);

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

protected:

	GLFWwindow* window_;
	std::vector<bool> keys_;
	std::vector<bool> buttons_;

	double mouse_x_, mouse_y_;

	double mouse_scroll_;

};