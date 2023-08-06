#pragma once

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

enum Direction {
	DIRECTION_FORWARD,
	DIRECTION_BACK,
	DIRECTION_RIGHT,
	DIRECTION_LEFT,
	DIRECTION_UP,
	DIRECTION_DOWN
};

class Camera {
public:

	Camera();

	// Update this every frame to recalculate matrices
	void update();

	void move(float x, float y, float z);
	void moveInDirection(Direction direction, float magnitude);
	void rotate(float pitch, float yaw, float roll);

	void setPosition(float x, float y, float z);
	void setRotation(float pitch, float yaw, float roll);

	inline glm::mat4& getLookAtMatrix() { return look_at_matrix_; }

protected:

	glm::vec3 position_;
	glm::vec3 look_at_;
	glm::vec3 forward_;
	glm::vec3 up_;
	glm::vec3 left_;

	float pitch_;
	float yaw_;
	float roll_;

	float fov_;

	glm::mat4 look_at_matrix_;

};