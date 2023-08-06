#pragma once

typedef unsigned int GLID;

struct Colour {
	float r_, g_, b_, a_;

	Colour() { r_ = 0.f; g_ = 0.f; b_ = 0.f; a_ = 1.f; }
	Colour(float r, float g, float b, float a) { r_ = r; g_ = g; b_ = b; a_ = a; }
};