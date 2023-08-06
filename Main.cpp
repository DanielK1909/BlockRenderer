#include "RenderWindow.h"
#include "Model.h"

#include <iostream>

int main() {

	RenderWindow window("Block Game");

	Texture texture;
	Sprite sprite;
	Model model;

	model.open("teapot");
	model.scale(0.1f, 0.1f, 0.1f);

	texture.loadPNG("test.png");

	sprite.scale(100, 100, 1);
	sprite.setTexture(texture);

	while (window.beginFrame()) {

		//window.drawSprite(&sprite);
		window.renderObject(&model);

		if (window.getInput().isKeyDown(GLFW_KEY_ESCAPE)) {
			break;
		}
		if (window.getInput().isKeyDown(GLFW_KEY_W)) {
			window.getCamera().moveInDirection(DIRECTION_FORWARD, 0.01f);
		}
		if (window.getInput().isKeyDown(GLFW_KEY_S)) {
			window.getCamera().moveInDirection(DIRECTION_BACK, 0.01f);
		}
		if (window.getInput().isKeyDown(GLFW_KEY_A)) {
			window.getCamera().moveInDirection(DIRECTION_LEFT, 0.01f);
		}
		if (window.getInput().isKeyDown(GLFW_KEY_D)) {
			window.getCamera().moveInDirection(DIRECTION_RIGHT, 0.01f);
		}

		window.getCamera().rotate((window.getInput().getMouseY() - window.getConfig().window_height_ / 2) * -1,
			(window.getInput().getMouseX() - window.getConfig().window_width_ / 2), 
			0.f);
		window.getInput().setMousePosition(window.getConfig().window_width_ / 2, window.getConfig().window_height_ / 2);

		window.endFrame();
	}

}