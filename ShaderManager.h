#pragma once

#include <map>
#include <vector>

#include "glad/glad.h"
#include "glm/mat4x4.hpp"

#include "Types.h"

struct Shader {
	GLID gl_id_;
	GLuint type_;
};

struct ShaderProgram {
	GLID gl_id_;
	std::map<GLuint, Shader> shaders_;
};

class ShaderManager {
public:

	ShaderProgram* loadShaderProgram(const char* vert_path, const char* frag_path);
	void useShaderProgram(int index);

	void setUniformInt(int index, const char* param, int value);
	void setUniformFloat(int index, const char* param, float value);
	void setUniformBool(int index, const char* param, bool value);
	void setUniformMat4(int index, const char* param, glm::mat4& value);

protected:

	Shader compileShader(GLuint type, const char* source);

	std::vector<ShaderProgram> programs_;

};