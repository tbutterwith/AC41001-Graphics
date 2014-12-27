#include "SquarePlanter.h"

SquarePlanter::SquarePlanter(){}

SquarePlanter::~SquarePlanter(){}

void SquarePlanter::createSquarePlanter(GLfloat length, GLfloat depth, GLfloat height, GLfloat x, GLfloat z) {
	GLfloat lid = 0.3f;
	GLfloat lip = 0.1f;

	GLfloat vertexPositions[] = {
		/* Outer walls */
		0.0f + x, 0.0f, 0.0f + z,
		length + x, height, 0.0f + z,
		0.0f + x, height, 0.0f + z,
		0.0f + x, 0.0f, 0.0f + z,
		length + x, 0.0f, 0.0f + z,
		length + x, height, 0.0f + z,

		length + x, 0.0f, 0.0f + z,
		length + x, height, -depth + z,
		length + x, height, 0.0f + z,
		length + x, 0.0f, 0.0f + z,
		length + x, 0.0f, -depth + z,
		length + x, height, -depth + z,

		length + x, 0.0f, -depth + z,
		0.0f + x, height, -depth + z,
		length + x, height, -depth + z,
		length + x, 0.0f, -depth + z,
		0.0f + x, 0.0f, -depth + z,
		0.0f + x, height, -depth + z,

		0.0f + x, 0.0f, -depth + z,
		0.0f + x, height, 0.0f + z,
		0.0f + x, height, -depth + z,
		0.0f + x, 0.0f, -depth + z,
		0.0f + x, 0.0f, 0.0f + z,
		0.0f + x, height, 0.0f + z,

		/* Lid */
		0.0f + x, height, 0.0f + z,
		length - lid + x, height, -lid + z,
		lid + x, height, -lid + z,
		0.0f + x, height, 0.0f + z,
		length + x, height, 0.0f + z,
		length - lid + x, height, -lid + z,

		length + x, height, 0.0f + z,
		length - lid + x, height, -(depth - lid) + z,
		length - lid + x, height, -lid + z,
		length + x, height, 0.0f + z,
		length + x, height, -depth + z,
		length - lid + x, height, -(depth - lid) + z,

		length + x, height, -depth + z,
		lid + x, height, -(depth - lid) + z,
		length - lid + x, height, -(depth - lid) + z,
		length + x, height, -depth + z,
		0.0f + x, height, -depth + z,
		lid + x, height, -(depth - lid) + z,

		0.0f + x, height, -depth + z,
		lid + x, height, -lid + z,
		lid + x, height, -(depth - lid) + z,
		0.0f + x, height, -depth + z,
		0.0f + x, height, 0.0f + z,
		lid + x, height, -lid + z,

		/* Inner walls */
		length - lid + x, height - lip, -lid + z,
		lid + x, height, -lid + z,
		length - lid + x, height, -lid + z,
		length - lid + x, height - lip, -lid + z,
		lid + x, height - lip, -lid + z,
		lid + x, height, -lid + z,

		length - lid + x, height - lip, -(depth - lid) + z,
		length - lid + x, height, -lid + z,
		length - lid + x, height, -(depth - lid) + z,
		length - lid + x, height - lip, -(depth - lid) + z,
		length - lid + x, height - lip, -lid + z,
		length - lid + x, height, -lid + z,

		lid + x, height - lip, -(depth - lid) + z,
		length - lid + x, height, -(depth - lid) + z,
		lid + x, height, -(depth - lid) + z,
		lid + x, height - lip, -(depth - lid) + z,
		length - lid + x, height - lip, -(depth - lid) + z,
		length - lid + x, height, -(depth - lid) + z,

		lid + x, height - lip, -lid + z,
		lid + x, height, -(depth - lid) + z,
		lid + x, height, -lid + z,
		lid + x, height - lip, -lid + z,
		lid + x, height - lip, -(depth - lid) + z,
		lid + x, height, -(depth - lid) + z,

		/* Inner lid */
		lid + x, height - lip, -lid + z,
		length - lid + x, height - lip, -(depth - lid) + z,
		lid + x, height - lip, -(depth - lid) + z,
		lid + x, height - lip, -lid + z,
		length - lid + x, height - lip, -lid + z,
		length - lid + x, height - lip, -(depth - lid) + z,
	};

	GLfloat normalsArray[] =
	{
		/* Outer walls */
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,

		/* lid */
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		/* Inner Walls */
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		/* Inner lid */
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	GLfloat texturePositions[] = {
		/* Outer walls */
		0.0f, 0.0f, 0.0f,
		4.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		4.0f, 0.0f, 0.0f,
		4.0f, 1.0f, 0.0f,

		0.0f, 0.0f, 0.0f,
		4.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		4.0f, 0.0f, 0.0f,
		4.0f, 1.0f, 0.0f,

		0.0f, 0.0f, 0.0f,
		4.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		4.0f, 0.0f, 0.0f,
		4.0f, 1.0f, 0.0f,

		0.0f, 0.0f, 0.0f,
		4.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		4.0f, 0.0f, 0.0f,
		4.0f, 1.0f, 0.0f,

		/* Lid */
		0.0f, 0.0f, 0.0f,
		4.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		4.0f, 0.0f, 0.0f,
		4.0f, 1.0f, 0.0f,

		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,

		0.0f, 0.0f, 0.0f,
		4.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		4.0f, 0.0f, 0.0f,
		4.0f, 1.0f, 0.0f,

		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,

		/* Inner walls */
		0.0f, 0.0f, 0.0f,
		4.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		4.0f, 0.0f, 0.0f,
		4.0f, 1.0f, 0.0f,

		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,

		0.0f, 0.0f, 0.0f,
		4.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		4.0f, 0.0f, 0.0f,
		4.0f, 1.0f, 0.0f,

		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,

		/* Inner lid */
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};

	GLfloat emissiveColoursArray[] = {
		0.0f, 0.0f, 0.0f,
		
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

void SquarePlanter::drawSquarePlanter() {
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

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, outerTex);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, outerNormals);
	glDrawArrays(GL_TRIANGLES, 0, 72);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, innerTex);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, innerNormals);
	glDrawArrays(GL_TRIANGLES, 72, 78);

	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
}

void SquarePlanter::setInnerTex(GLuint tex) {
	innerTex = tex;
}

void SquarePlanter::setInnerNormals(GLuint tex) {
	innerNormals = tex;
}

void SquarePlanter::setOuterTex(GLuint tex) {
	outerTex = tex;
}

void SquarePlanter::setOuterNormals(GLuint tex) {
	outerNormals = tex;
}