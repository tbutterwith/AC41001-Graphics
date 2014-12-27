#pragma once
/* room.h
 Creates and draws the bounding room for the walled garden
*/

#pragma once

#include "wrapper_glfw.h"
#include <vector>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

class room
{
public:
	room();
	~room();

	void drawRoom();
	void createRoom(GLfloat, GLfloat);
	void setTexture(GLuint);
	void setNormalsMap(GLuint);


	GLuint vertices;
	GLuint normals;
	GLuint textures;
	GLuint tangents;

	GLuint emissiveColours;
	GLuint texID;
	GLuint normalsMap;
};