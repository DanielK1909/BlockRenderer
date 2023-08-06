#include "Camera.h"

#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
	position_ = glm::vec3(0, 0, 0);
	pitch_ = 0.f;
	yaw_ = 0.f;
	roll_ = 0.f;

	update();

	fov_ = 80.f;
}

void Camera::update() {
	forward_.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	forward_.y = sin(glm::radians(pitch_));
	forward_.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	forward_ = glm::normalize(forward_);

	left_ = glm::normalize(glm::cross(glm::vec3(0.f, 1.f, 0.f), forward_));
	up_ = glm::normalize(glm::cross(forward_, left_));
	look_at_ = position_ + forward_;

	look_at_matrix_ = glm::lookAt(position_, look_at_, up_);
}

void Camera::move(float x, float y, float z) {
	position_ += glm::vec3(x, y, z);
}

void Camera::moveInDirection(Direction direction, float magnitude) {
	switch (direction) {
	case DIRECTION_FORWARD:
		position_ += forward_ * magnitude;
		break;
	case DIRECTION_BACK:
		position_ -= forward_ * magnitude;
		break;
	case DIRECTION_LEFT:
		position_ += left_ * magnitude;
		break;
	case DIRECTION_RIGHT:
		position_ -= left_ * magnitude;
		break;
	case DIRECTION_UP:
		position_ += up_ * magnitude;
		break;
	case DIRECTION_DOWN:
		position_ -= up_ * magnitude;
	}
}

void Camera::rotate(float pitch, float yaw, float roll) {
	pitch_ += pitch;
	yaw_ += yaw;
	roll_ += roll;
}

void Camera::setPosition(float x, float y, float z) {
	position_ = glm::vec3(x, y, z);
}

void Camera::setRotation(float pitch, float yaw, float roll) {
	pitch_ = pitch;
	yaw_ = yaw;
	roll_ = roll;
}
