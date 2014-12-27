/*
	Gear.cpp
	Creates a gear of a given size, including normals

	Thomas Butterwith
	Nov. 2014
*/

#include "Gear.h"


Gear::Gear(){

	}

	glm::vec4 * Gear::createGear(float radius, int sides, int teeth, float toothHeight, float startingRotate) {
		glm::vec4 gearOneToothPoints[] = {

			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
			glm::vec4(toothLength, toothHeight, 0.0f, 1.0f),
			glm::vec4(0.0f, toothHeight, 0.0f, 1.0f),
			glm::vec4(toothLength, toothHeight, 0.0f, 1.0f),
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
			glm::vec4(toothLength, 0.0f, 0.0f, 1.0f),
			

			glm::vec4(toothLength, 0.0f, 0.0f, 1.0f),
			glm::vec4(toothLength, toothHeight, -toothDepth, 1.0f),
			glm::vec4(toothLength, toothHeight, 0.0f, 1.0f),
			glm::vec4(toothLength, toothHeight, -toothDepth, 1.0f),
			glm::vec4(toothLength, 0.0f, 0.0f, 1.0f),
			glm::vec4(toothLength, 0.0f, -toothDepth, 1.0f),
			

			glm::vec4(0.0f, 0.0f, -toothDepth, 1.0f),
			glm::vec4(0.0f, toothHeight, -toothDepth, 1.0f),
			glm::vec4(toothLength, toothHeight, -toothDepth, 1.0f),
			glm::vec4(toothLength, toothHeight, -toothDepth, 1.0f),
			glm::vec4(toothLength, 0.0f, -toothDepth, 1.0f),
			glm::vec4(0.0f, 0.0f, -toothDepth, 1.0f),

			glm::vec4(0.0f, toothHeight, 0.0f, 1.0f),
			glm::vec4(toothLength, toothHeight, -toothDepth, 1.0f),
			glm::vec4(0.0f, toothHeight, -toothDepth, 1.0f),
			glm::vec4(toothLength, toothHeight, -toothDepth, 1.0f),
			glm::vec4(0.0f, toothHeight, 0.0f, 1.0f),
			glm::vec4(toothLength, toothHeight, 0.0f, 1.0f),
			

			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
			glm::vec4(0.0f, 0.0f, -toothDepth, 1.0f),
			glm::vec4(toothLength, 0.0f, -toothDepth, 1.0f),
			glm::vec4(toothLength, 0.0f, -toothDepth, 1.0f),
			glm::vec4(toothLength, 0.0f, 0.0f, 1.0f),
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),

		};
		int arraySize = ((sides + 1) * 8) + (teeth * 30);
		glm::vec4 * gear = new glm::vec4[arraySize];
		int j = 0;
		for (int i = 0; i < sides + 1; i++) {
			float theta = 2.0f * pi * float(i) / float(sides);//get the current angle 

			float x = radius * cosf(theta);//calculate the x component 
			float y = radius * sinf(theta);//calculate the y component 



			gear[j] = glm::vec4(x, y, 0.0, 1.0f);
			j++;


			x = 0.05f * cosf(theta);//calculate the x component 
			y = 0.05f * sinf(theta);//calculate the y component 

			gear[j] = glm::vec4(x, y, 0.0, 1.0f);
			j++;


		}
		for (int i = 0; i < sides + 1; i++) {
			float theta = 2.0f * pi * float(i) / float(sides);//get the current angle 

			float x = radius * cosf(theta);//calculate the x component 
			float y = radius * sinf(theta);//calculate the y component 

			gear[j] = glm::vec4(x, y, 0.0, 1.0f);
			j++;

			gear[j] = glm::vec4(x, y, -0.1f, 1.0f);
			j++;

		}
		for (int i = 0; i < sides + 1; i++) {
			float theta = 2.0f * pi * float(i) / float(sides);//get the current angle 

			float x = radius * cosf(theta);//calculate the x component 
			float y = radius * sinf(theta);//calculate the y component 

			gear[j] = glm::vec4(x, y, -0.1f, 1.0f);
			j++;

			x = 0.05f * cosf(theta);//calculate the x component 
			y = 0.05f * sinf(theta);//calculate the y component 

			gear[j] = glm::vec4(x, y, -0.1f, 1.0f);
			j++;

		}

		

		for (int i = 0; i < teeth ; i ++) {
			float theta = 2.0f * pi * float(i) / float(teeth); //get the current angle 
			float rotate = (360.0f / teeth) * (i);
			rotate += (360.0f / (sides)) / 2;

			radius -= 0.001f;

			float moveX = radius * cosf(theta);//calculate the x component 
			float moveY = radius * sinf(theta);//calculate the y component 



			glm::mat4 transformation = glm::mat4(1.0f);
			transformation = glm::translate(transformation, glm::vec3(moveX, moveY, 0.0));
			transformation = glm::rotate(transformation, rotate, glm::vec3(0.0, 0.0, 1.0));

			//std::cout << "tooth number : " << (i) << " at x: " << moveX << " and y: " << moveY << std::endl;

			for (int i = 0; i < 30; i++) {
				glm::vec4 newPoint = transformation * gearOneToothPoints[i];
				gear[j] = newPoint;
				j++;
			}
		}

		//Rotate Gear to starting position
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, startingRotate, glm::vec3(0, 0, 1.0f));

		for (int a = 0; a < arraySize; a++) {
			gear[a] = model*gear[a];
		}

		return gear;
	}

	glm::vec3 * Gear::calculateNormals(glm::vec4 * vertices, int sides, int teeth) {

		int arraySize = ((sides + 1) * 8) + (teeth * 30);
		glm::vec3 * normals = new glm::vec3[arraySize];


		/* Face 1 */
		glm::vec4 pointOne = vertices[1];
		glm::vec4 pointTwo = vertices[2];
		glm::vec4 pointThree = vertices[3];

		glm::vec4 vectorOne = pointTwo - pointOne;
		glm::vec4 vectorTwo = pointThree - pointOne;

		glm::vec3 normal = glm::cross(glm::vec3(vectorOne.x, vectorOne.y, vectorOne.z), glm::vec3(vectorTwo.x, vectorTwo.y, vectorTwo.z));

		int stop = ((sides+1) * 2);
		for (int a = 0; a < stop; a++){
			normals[a] = normal;
		}

		/* End */
		int start = stop;
		stop += ((sides + 1) * 2);
		for (int b = start; b < stop; b+=2) {
			pointOne = vertices[b];
			pointTwo = vertices[b+1];
			pointThree = vertices[b+2];

			vectorOne = pointTwo - pointOne;
			vectorTwo = pointThree - pointOne;

			normal = glm::cross(glm::vec3(vectorOne.x, vectorOne.y, vectorOne.z), glm::vec3(vectorTwo.x, vectorTwo.y, vectorTwo.z));

			normals[b] = normal;
			normals[b + 1] = normal;
		}

		/* face two */
		start = stop;
		stop += ((sides + 1) * 2);

		pointOne = vertices[start];
		pointTwo = vertices[start + 1];
		pointThree = vertices[start + 2];

		vectorOne = pointTwo - pointOne;
		vectorTwo = pointThree - pointOne;

		normal = glm::cross(glm::vec3(vectorOne.x, vectorOne.y, vectorOne.z), glm::vec3(vectorTwo.x, vectorTwo.y, vectorTwo.z));

		for (int a = start; a < stop; a++) {
			normals[a] = normal;
		}

		/* teeth */

		start = stop;
		stop = arraySize;

		for (int i = start; i < stop; i += 6) {
			pointOne = vertices[i];
			pointTwo = vertices[i + 1];
			pointThree = vertices[i + 2];

			vectorOne = pointTwo - pointOne;
			vectorTwo = pointThree - pointOne;

			normal = glm::cross(glm::vec3(vectorOne.x, vectorOne.y, vectorOne.z), glm::vec3(vectorTwo.x, vectorTwo.y, vectorTwo.z));

			normals[i] = normal;
			normals[i + 1] = normal;
			normals[i + 2] = normal;
			normals[i + 3] = normal;
			normals[i + 4] = normal;
			normals[i + 5] = normal;
		}


		return normals;

	}


