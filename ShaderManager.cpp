#include "ShaderManager.h"

#include "Log.h"

#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>

ShaderProgram* ShaderManager::loadShaderProgram(const char* vert_path, const char* frag_path) {
    std::string vert_source = "";
    std::string frag_source = "";

    std::string line;
    std::ifstream vert_file(vert_path);
    while (std::getline(vert_file, line)) {
        vert_source += line + "\n";
    }
    std::ifstream frag_file(frag_path);
    while (std::getline(frag_file, line)) {
        frag_source += line + "\n";
    }

    vert_file.close();
    frag_file.close();

    ShaderProgram sp;
    sp.gl_id_ = glCreateProgram();

    sp.shaders_[GL_VERTEX_SHADER] = compileShader(GL_VERTEX_SHADER, vert_source.c_str());
    sp.shaders_[GL_FRAGMENT_SHADER] = compileShader(GL_FRAGMENT_SHADER, frag_source.c_str());

    for (auto& s : sp.shaders_) {
        glAttachShader(sp.gl_id_, s.second.gl_id_);
    }

    glLinkProgram(sp.gl_id_);

	int success;
	char info[512];

	glGetProgramiv(sp.gl_id_, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(sp.gl_id_, 512, NULL, info);
        Log::error(info);
	}

    glUseProgram(sp.gl_id_);

    programs_.push_back(sp);

	return &programs_.back();
}

void ShaderManager::useShaderProgram(int index) {
    glUseProgram(programs_[index].gl_id_);
}

void ShaderManager::setUniformInt(int index, const char* param, int value) {
    GLID program_id = programs_[index].gl_id_;

    glUseProgram(program_id);
    int loc = glGetUniformLocation(program_id, param);
    glUniform1i(loc, value);
}

void ShaderManager::setUniformFloat(int index, const char* param, float value) {
    GLID program_id = programs_[index].gl_id_;

    glUseProgram(program_id);
    int loc = glGetUniformLocation(program_id, param);
    glUniform1f(loc, value);
}

void ShaderManager::setUniformBool(int index, const char* param, bool value) {
    GLID program_id = programs_[index].gl_id_;

    glUseProgram(program_id);
    int loc = glGetUniformLocation(program_id, param);
    glUniform1i(loc, value);
}

void ShaderManager::setUniformMat4(int index, const char* param, glm::mat4& value) {
    GLID program_id = programs_[index].gl_id_;

    float* mat_ptr = glm::value_ptr(value);

    glUseProgram(program_id);
    int loc = glGetUniformLocation(program_id, param);
    glUniformMatrix4fv(loc, 1, GL_FALSE, mat_ptr);
}

Shader ShaderManager::compileShader(GLuint type, const char* source) {
    Shader shader;
    shader.gl_id_ = glCreateShader(type);
    glShaderSource(shader.gl_id_, 1, &source, NULL);
    glCompileShader(shader.gl_id_);
    
    int success;
    char info[512];

    glGetShaderiv(shader.gl_id_, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader.gl_id_, 512, NULL, info);
        Log::error(info);
    }

    return shader;
}
