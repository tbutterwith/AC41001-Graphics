/*
	Crank.cpp
	Creates a crank of fixed size, including normals

	Thomas Butterwith
	Nov. 2014
*/
#include "Crank.h"

Crank::Crank(){};

glm::vec4 * Crank::buildCrank() {
	int sides = 50;
	int radius = 0.05f;
	const int arraySize = 72;
	glm::vec4 * crank = new glm::vec4[arraySize];

	/* Draw Crank Arm*/

	//front
	crank[0] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	crank[1] = glm::vec4(0.0f, 0.7f, 0.0f, 1.0f);
	crank[2] = glm::vec4(0.1f, 0.7f, 0.0f, 1.0f);
	crank[3] = glm::vec4(0.1f, 0.7f, 0.0f, 1.0f);
	crank[4] = glm::vec4(0.1f, 0.0f, 0.0f, 1.0f);
	crank[5] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	//left
	crank[6] = glm::vec4(0.0f, 0.0f, 0.1f, 1.0f);
	crank[7] = glm::vec4(0.0f, 0.7f, 0.1f, 1.0f);
	crank[8] = glm::vec4(0.0f, 0.7f, 0.0f, 1.0f);
	crank[9] = glm::vec4(0.0f, 0.7f, 0.0f, 1.0f);
	crank[10] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	crank[11] = glm::vec4(0.0f, 0.0f, 0.1f, 1.0f);

	//back
	crank[12] = glm::vec4(0.1f, 0.0f, 0.1f, 1.0f);
	crank[13] = glm::vec4(0.1f, 0.7f, 0.1f, 1.0f);
	crank[14] = glm::vec4(0.0f, 0.7f, 0.1f, 1.0f);
	crank[15] = glm::vec4(0.0f, 0.7f, 0.1f, 1.0f);
	crank[16] = glm::vec4(0.0f, 0.0f, 0.1f, 1.0f);
	crank[17] = glm::vec4(0.1f, 0.0f, 0.1f, 1.0f);

	//right
	crank[18] = glm::vec4(0.1f, 0.0f, 0.0f, 1.0f);
	crank[19] = glm::vec4(0.1f, 0.7f, 0.0f, 1.0f);
	crank[20] = glm::vec4(0.1f, 0.7f, 0.1f, 1.0f);
	crank[21] = glm::vec4(0.1f, 0.7f, 0.1f, 1.0f);
	crank[22] = glm::vec4(0.1f, 0.0f, 0.1f, 1.0f);
	crank[23] = glm::vec4(0.1f, 0.0f, 0.0f, 1.0f);
	
	//top
	crank[24] = glm::vec4(0.0f, 0.7f, 0.0f, 1.0f);
	crank[25] = glm::vec4(0.0f, 0.7f, 0.1f, 1.0f);
	crank[26] = glm::vec4(0.1f, 0.7f, 0.1f, 1.0f);
	crank[27] = glm::vec4(0.1f, 0.7f, 0.1f, 1.0f);
	crank[28] = glm::vec4(0.1f, 0.7f, 0.0f, 1.0f);
	crank[29] = glm::vec4(0.0f, 0.7f, 0.0f, 1.0f);

	//bottom
	crank[30] = glm::vec4(0.0f, 0.0f, 0.1f, 1.0f);
	crank[31] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	crank[32] = glm::vec4(0.1f, 0.0f, 0.0f, 1.0f);
	crank[33] = glm::vec4(0.1f, 0.0f, 0.0f, 1.0f);
	crank[34] = glm::vec4(0.1f, 0.0f, 0.1f, 1.0f);
	crank[35] = glm::vec4(0.0f, 0.0f, 0.1f, 1.0f);

	/* crank handle*/
	//front
	crank[36] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	crank[37] = glm::vec4(0.0f, 0.3f, 0.0f, 1.0f);
	crank[38] = glm::vec4(0.05f, 0.3f, 0.0f, 1.0f);
	crank[39] = glm::vec4(0.05f, 0.3f, 0.0f, 1.0f);
	crank[40] = glm::vec4(0.05f, 0.0f, 0.0f, 1.0f);
	crank[41] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	//left
	crank[42] = glm::vec4(0.0f, 0.0f, 0.05f, 1.0f);
	crank[43] = glm::vec4(0.0f, 0.3f, 0.05f, 1.0f);
	crank[44] = glm::vec4(0.0f, 0.3f, 0.0f, 1.0f);
	crank[45] = glm::vec4(0.0f, 0.3f, 0.0f, 1.0f);
	crank[46] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	crank[47] = glm::vec4(0.0f, 0.0f, 0.05f, 1.0f);

	//back
	crank[48] = glm::vec4(0.05f, 0.0f, 0.05f, 1.0f);
	crank[49] = glm::vec4(0.05f, 0.3f, 0.05f, 1.0f);
	crank[50] = glm::vec4(0.0f, 0.3f, 0.05f, 1.0f);
	crank[51] = glm::vec4(0.0f, 0.3f, 0.05f, 1.0f);
	crank[52] = glm::vec4(0.0f, 0.0f, 0.05f, 1.0f);
	crank[53] = glm::vec4(0.05f, 0.0f, 0.05f, 1.0f);

	//right
	crank[54] = glm::vec4(0.05f, 0.0f, 0.0f, 1.0f);
	crank[55] = glm::vec4(0.05f, 0.3f, 0.0f, 1.0f);
	crank[56] = glm::vec4(0.05f, 0.3f, 0.05f, 1.0f);
	crank[57] = glm::vec4(0.05f, 0.3f, 0.05f, 1.0f);
	crank[58] = glm::vec4(0.05f, 0.0f, 0.05f, 1.0f);
	crank[59] = glm::vec4(0.05f, 0.0f, 0.0f, 1.0f);

	//top
	crank[60] = glm::vec4(0.0f, 0.3f, 0.0f, 1.0f);
	crank[61] = glm::vec4(0.0f, 0.3f, 0.05f, 1.0f);
	crank[62] = glm::vec4(0.05f, 0.3f, 0.05f, 1.0f);
	crank[63] = glm::vec4(0.05f, 0.3f, 0.05f, 1.0f);
	crank[64] = glm::vec4(0.05f, 0.3f, 0.0f, 1.0f);
	crank[65] = glm::vec4(0.0f, 0.3f, 0.0f, 1.0f);

	//bottom
	crank[66] = glm::vec4(0.0f, 0.0f, 0.05f, 1.0f);
	crank[67] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	crank[68] = glm::vec4(0.05f, 0.0f, 0.0f, 1.0f);
	crank[69] = glm::vec4(0.05f, 0.0f, 0.0f, 1.0f);
	crank[70] = glm::vec4(0.05f, 0.0f, 0.05f, 1.0f);
	crank[71] = glm::vec4(0.0f, 0.0f, 0.05f, 1.0f);

	glm::mat4 rotateZ = glm::mat4(1.0f);
	rotateZ = glm::translate(rotateZ, glm::vec3(0.025f, 0.65f, 0.0f));
	rotateZ = glm::rotate(rotateZ, 90.0f, glm::vec3(1, 0, 0));

	for (int b = 36; b < 72; b++) {
		crank[b] = rotateZ * crank[b];
	}
	
	/* move arm into place*/
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(-0.05f, -0.1f, 0.0f));

	for (int a = 0; a < 72; a++) {
		crank[a] = transform * crank[a];
	}

	return crank;
}

glm::vec3 * Crank::calculateNormals(glm::vec4 * crank) {
	glm::vec3 * crankNormals = new glm::vec3[72];

	for (int a = 0; a < 72; a+=6) {
		glm::vec4 pointOne = crank[a];
		glm::vec4 pointTwo = crank[a + 1];
		glm::vec4 pointThree = crank[a + 2];

		glm::vec4 vectorOne = pointTwo - pointOne;
		glm::vec4 vectorTwo = pointThree - pointOne;

		glm::vec3 normal = glm::cross(glm::vec3(vectorOne.x, vectorOne.y, vectorOne.z), glm::vec3(vectorTwo.x, vectorTwo.y, vectorTwo.z));

		crankNormals[a] = normal;
		crankNormals[a + 1] = normal;
		crankNormals[a + 2] = normal;
		crankNormals[a + 3] = normal;
		crankNormals[a + 4] = normal;
		crankNormals[a + 5] = normal;
	}

	return crankNormals;
}

