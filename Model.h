#pragma once

#include "GameObject.h"

struct Face {

};

class Model : public GameObject {
public:

	void loadOBJ(const char* path);
	void save(const char* name);
	void open(const char* name);

};