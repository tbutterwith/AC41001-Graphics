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

class Floor 
{
public:
	Floor();
	~Floor();

	void createFloor(GLfloat, GLfloat);
	void drawFloor();

	void setTexture(GLuint);
	void setNormalsMap(GLuint);

	GLuint vertices;
	GLuint normals;
	GLuint textures;
	GLuint emissiveColours;
	GLuint tangents;

	GLuint texID;
	GLuint normalsMap;
};