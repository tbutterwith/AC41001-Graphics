#pragma once
/* SquarePlanter.h
Creates and draws the rectangular planters for the walled garden
*/

#pragma once

#include "wrapper_glfw.h"
#include <vector>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

class SquarePlanter {
public:
	SquarePlanter();
	~SquarePlanter();

	void createSquarePlanter(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	void drawSquarePlanter();

	GLuint vertices;
	GLuint normals;
	GLuint textures;
	GLuint emissiveColours;

	void setInnerTex(GLuint);
	void setInnerNormals(GLuint);
	void setOuterTex(GLuint);
	void setOuterNormals(GLuint);

	GLuint outerTex;
	GLuint outerNormals;
	GLuint innerTex;
	GLuint innerNormals;
};