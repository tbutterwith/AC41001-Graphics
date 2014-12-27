#pragma once
/* floor.h
Creates and draws the floor for the walled garden
*/

#pragma once

#include "wrapper_glfw.h"
#include <vector>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

class Sky {
public:
	Sky();
	~Sky();

	void createSky();
	void drawSky();

	GLuint vertices;
	GLuint normals;
	GLuint textures;
	GLuint emissiveColours;
};