#pragma once

#include "glm/mat4x4.hpp"

#include "Texture.h"

#include <vector>

// yes 2d sprites have normals, i couldnt be bothered having 2 vao configs
const float SPRITE_BOX[32] = {
		0.f, 0.f, 0.f,
		0.f, 0.f,
		0.f, 0.f, 1.f,

		1.f, 0.f, 0.f,
		1.f, 0.f,
		0.f, 0.f, 1.f,

		1.f, 1.f, 0.f,
		1.f, 1.f,
		0.f, 0.f, 1.f,

		0.f, 1.f, 0.f,
		0.f, 1.f,
		0.f, 0.f, 1.f
};

const unsigned int SPRITE_INDEX[6] = {
	0, 1, 2,
	0, 2, 3
};

class Sprite {
public:

	Sprite();

	Texture* getTexture() { return &texture_; }
	void setTexture(const Texture& texture) { texture_ = texture; }

	inline glm::mat4& getTransform() { return transform_; }
	Colour* getColour() { return &colour_; }

	void scale(float x, float y, float z);

protected:

	Texture texture_;
	Colour colour_;
	glm::mat4 transform_;

};