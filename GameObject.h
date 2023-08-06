#pragma once

#include <vector>

#include "glm/mat4x4.hpp"

class GameObject {
public:

	GameObject();

	inline glm::mat4& getTransform() { return transform_; }

	inline float* getData() { return gl_data_.data(); }
	inline unsigned int getDataSize() { return gl_data_.size(); }
	inline unsigned int* getIndex() { return index_.data(); }
	inline unsigned int getIndexSize() { return index_.size(); }

	void scale(float x, float y, float z);

protected:

	glm::mat4 transform_;
	std::vector<float> gl_data_;
	std::vector<unsigned int> index_;

};