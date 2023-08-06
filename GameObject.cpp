#include "GameObject.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>

GameObject::GameObject() {
	transform_ = glm::mat4(1.f);
}

void GameObject::scale(float x, float y, float z) {
	transform_ = glm::scale(transform_, glm::vec3(x, y, z));
}
