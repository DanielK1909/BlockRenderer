#pragma once

#include "Types.h"

class Texture {
public:

	Texture();

	bool loadPNG(const char* path);
	void apply();

protected:

	GLID gl_id_;
	int width_, height_, channels_;
	bool loaded_;

};