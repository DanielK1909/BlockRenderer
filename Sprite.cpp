#include "Sprite.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>

Sprite::Sprite() {
	transform_ = glm::mat4(1.f);
}

void Sprite::scale(float x, float y, float z) {
	transform_ = glm::scale(transform_, glm::vec3(x, y, z));
}
