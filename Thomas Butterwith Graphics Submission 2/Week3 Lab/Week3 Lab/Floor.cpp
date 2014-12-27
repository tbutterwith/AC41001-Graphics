#include "Floor.h"

Floor::Floor(){}
Floor::~Floor(){}

void Floor::createFloor(GLfloat roomLength, GLfloat roomHeight) {
	GLfloat vertexPositions[] = {
		-roomLength, 0.0f, roomLength,
		roomLength, 0.0f, -roomLength,
		-roomLength, 0.0f, -roomLength,
		-roomLength, 0.0f, roomLength,
		roomLength, 0.0f, roomLength,
		roomLength, 0.0f, -roomLength
	};

	GLfloat normalsArray[] =
	{
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	GLfloat texturePositions[] = {
		0.0f, 0.0f, 0.0f,
		40.0f, 40.0f, 0.0f,
		0.0f, 40.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		40.0f, 0.0f, 0.0f,
		40.0f, 40.0f, 0.0f
	};

	GLfloat emissiveColoursArray[] = {
		0.0f, 0.0f, 0.0f
	};

	GLfloat tangentArray[] = {
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f
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

	/* Create the normals  buffer for the cube */
	glGenBuffers(1, &tangents);
	glBindBuffer(GL_ARRAY_BUFFER, tangents);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tangentArray), tangentArray, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void Floor::setTexture(GLuint tex) {
	texID = tex;
}

void Floor::setNormalsMap(GLuint tex) {
	normalsMap = tex;
}

void Floor::drawFloor() {
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

	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, tangents);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normalsMap);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
}