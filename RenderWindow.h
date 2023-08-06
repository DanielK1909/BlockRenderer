#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "ShaderManager.h"
#include "Sprite.h"
#include "GameObject.h"
#include "FrameworkOptions.h"
#include "Camera.h"
#include "Input.h"

#include <vector>

class RenderWindow {
public:

	// Vector to keep track of all window instances for static callbacks
	static std::vector<RenderWindow*> window_instances_;

	RenderWindow(const char* title);
	~RenderWindow();

	bool beginFrame();
	bool endFrame();

	inline void setConfig(FrameworkOptions& config) { config_ = config; }
	inline FrameworkOptions& getConfig() { return config_; }

	inline GLFWwindow* getGLFWWindow() { return glfw_window_; }

	void renderObject(GameObject* object);
	void drawSprite(Sprite* sprite);

	static void windowSizeCallback(GLFWwindow* window, int width, int height);

	inline void setCamera(Camera& camera) { camera_ = camera; }
	inline Camera& getCamera() { return camera_; }

	inline Input& getInput() { return input_; }
 
protected:

	GLFWwindow* glfw_window_;

	void drawSprites();
	void render3d();

	FrameworkOptions config_;

	GLID vao_, vbo_, ebo_;

	ShaderManager sm_;

	Camera camera_;

	Input input_;

	std::vector<Sprite*> sprites_;
	std::vector<GameObject*> game_objects_;

};