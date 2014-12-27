#include "Sky.h"

Sky::Sky(){}

Sky::~Sky(){}

void Sky::createSky() {
	GLfloat vertexPositions[] = {
		-2000.0f, 12.0f, -2000.0f,
		2000.0f, 12.0f, 2000.0f,
		-2000.0f, 12.0f, 2000.0f,
		-2000.0f, 12.0f, -2000.0f,
		2000.0f, 12.0f, -2000.0f,
		2000.0f, 12.0f, 2000.0f,
	};

	GLfloat normalsArray[] =
	{
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
	};

	GLfloat texturePositions[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 
		0.0f, 0.0f, 0.0f
	};

	GLfloat emissiveColoursArray[] = {
		0.25f, 0.7f, 1.0f,
		0.25f, 0.7f, 1.0f,
		0.25f, 0.7f, 1.0f,
		0.25f, 0.7f, 1.0f,
		0.25f, 0.7f, 1.0f,
		0.25f, 0.7f, 1.0f
	};



	/* Create the vertex buffer for the cube */
	glGenBuffers(1, &vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	/* Create the normals  buffer for the cube */
	glGenBuffers(1, &normals);
	glBindBuffer(GL_ARRAY_BUFFER, normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normalsArray), normalsArray, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Create the normals  buffer for the cube */
	glGenBuffers(1, &textures);
	glBindBuffer(GL_ARRAY_BUFFER, textures);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texturePositions), texturePositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Create the normals  buffer for the cube */
	glGenBuffers(1, &emissiveColours);
	glBindBuffer(GL_ARRAY_BUFFER, emissiveColours);
	glBufferData(GL_ARRAY_BUFFER, sizeof(emissiveColoursArray), emissiveColoursArray, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sky::drawSky() {
	glBindBuffer(GL_ARRAY_BUFFER, vertices);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, normals);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, textures);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, emissiveColours);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}