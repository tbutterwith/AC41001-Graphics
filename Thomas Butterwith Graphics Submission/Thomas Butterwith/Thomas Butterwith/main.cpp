/*
	Main.cpp
	Main entry point to the program. Uses GLFW to create a window in which 4 gears and a crank arm
	are displayed. Accepts user input to manipulate model and adjust rotation speed.

	Thomas Butterwith
	Nov. 2014
*/

/* Link to static libraries */
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glloadD.lib")
#pragma comment(lib, "opengl32.lib")

/* Include the header to the GLFW wrapper class which
   also includes the OpenGL extension initialisation*/
#include "wrapper_glfw.h"
#include <iostream>
#include "Gear.h"
#include "Crank.h"

/* GLM core */
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

CONST float pi = 3.14159265358979323846264338327950288f;

/* Buffers */
GLuint positionBufferGearOne, positionBufferGearTwo, positionBufferGearThree, positionBufferCrank, colourObject;
GLuint positionBufferGearFour;
GLuint gearOneNormals, gearTwoNormals, gearThreeNormals, crankNormals;
GLuint gearFourNormals;
GLuint program;
GLuint vao;

/* Position and view globals */
float angle_x, angle_x_inc;
GLfloat angle_z, angle_z_inc, angle_y, angle_y_inc;
GLfloat scale_val;
GLfloat move_model_x, move_model_y, move_model_z, look_x, look_y, look_z;

/* Uniforms*/
GLuint modelID, viewID, projectionID;

/* Gear One */
int sides = 16;
int teeth = 8;
float radius = 0.5f;


GLfloat aspect_ratio;

/* Prints instructions to the console window */
static void printInstructions() {
	std::cout << "|Thomas Butterwith Graphics Assignment 1: Gears|" << std::endl;
	std::cout << "|----------------------------------------------|" << std::endl;
	std::cout << "|Move View:                                    |" << std::endl;
	std::cout << "|W      - up                                   |" << std::endl;
	std::cout << "|S      - down                                 |" << std::endl;
	std::cout << "|A      - left                                 |" << std::endl;
	std::cout << "|D      - right                                |" << std::endl;
	std::cout << "|Q      - zoom out                             |" << std::endl;
	std::cout << "|E      - zoom in                              |" << std::endl;
	std::cout << "|                                              |" << std::endl;
	std::cout << "|Gear Movement                                 |" << std::endl;
	std::cout << "|Z      - rotate slower                        |" << std::endl;
	std::cout << "|X      - rotate faster                        |" << std::endl;
	std::cout << "|                                              |" << std::endl;
	std::cout << "|Rotate Model                                  |" << std::endl;
	std::cout << "|Up     - anticlockwise on x-axis              |" << std::endl;
	std::cout << "|Down   - clockwise on x-axis                  |" << std::endl;
	std::cout << "|Left   - clockwise on y-axis                  |" << std::endl;
	std::cout << "|Right  - anticlockwise on y-axis              |" << std::endl;
	std::cout << "|______________________________________________|" << std::endl;
	std::cout << "" << std::endl;

}

/*
	Initial function, called before display
*/
void init(GLWrapper *glw)
{
	printInstructions();
	angle_x = 0.0f;
	angle_x_inc = 0.0f;
	angle_y = 0.0f;
	angle_y_inc = 0.0f;
	angle_z = 0.0f;
	angle_z_inc = 0.1f;
	scale_val = 1.0;
	move_model_x = 0;
	move_model_y = 0;
	move_model_z = 0;
	look_x = 0;
	look_y = 0;
	look_z = 0;

	aspect_ratio = 1.3333f;

	// Generate index (name) for one vertex array object
	glGenVertexArrays(1, &vao);

	// Create the vertex array object and make it current
	glBindVertexArray(vao);


	/* Define an array of colours */
	float vertexColours[] = {
		0.627f, 0.627f, 0.627f, 1.0f
	};
	
	/* Create vec4 arrays for each object and vec3 arrays to contain normals*/
	Gear gear;
	glm::vec4 * gearTest = gear.createGear(radius, sides, teeth, 0.195f, 0.0f);
	glm::vec3 * gearOneNormal = gear.calculateNormals(gearTest, sides, teeth);
	glm::vec4 * gearTwo = gear.createGear(0.3, 10, 5, 0.180f, 35.0f);
	glm::vec3 * gearTwoNormal = gear.calculateNormals(gearTwo, 10, 5);
	glm::vec4 * gearThree = gear.createGear(radius, sides, teeth, 0.195f, 24.0f);
	glm::vec3 * gearThreeNormal = gear.calculateNormals(gearThree, sides, teeth);
	glm::vec4 * gearFour = gear.createGear(1.0, 26, 16, 0.195f, 10.0f);
	glm::vec3 * gearFourNormal = gear.calculateNormals(gearFour, 26, 20);
	Crank crankClass;
	glm::vec4 * crank = crankClass.buildCrank();
	glm::vec3 * crankNormal = crankClass.calculateNormals(crank);
	
	/* Create a vertex buffer object to store vertices */
	glGenBuffers(1, &positionBufferGearOne);
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferGearOne);
	glBufferData(GL_ARRAY_BUFFER, (368 * sizeof(glm::vec4)), gearTest, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	/* Create a vertex buffer object to store normals */
	glGenBuffers(1, &gearOneNormals);
	glBindBuffer(GL_ARRAY_BUFFER, gearOneNormals);
	glBufferData(GL_ARRAY_BUFFER, (368 * sizeof(glm::vec3)), gearOneNormal, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Create a vertex buffer object to store vertices */
	glGenBuffers(1, &positionBufferGearTwo);
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferGearTwo);
	glBufferData(GL_ARRAY_BUFFER, (368 * sizeof(glm::vec4)), gearTwo, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	/* Create a vertex buffer object to store normals */
	glGenBuffers(1, &gearTwoNormals);
	glBindBuffer(GL_ARRAY_BUFFER, gearTwoNormals);
	glBufferData(GL_ARRAY_BUFFER, (368 * sizeof(glm::vec3)), gearTwoNormal, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Create a vertex buffer object to store vertices */
	glGenBuffers(1, &positionBufferGearThree);
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferGearThree);
	glBufferData(GL_ARRAY_BUFFER, (368 * sizeof(glm::vec4)), gearThree, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	/* Create a vertex buffer object to store normals */
	glGenBuffers(1, &gearThreeNormals);
	glBindBuffer(GL_ARRAY_BUFFER, gearThreeNormals);
	glBufferData(GL_ARRAY_BUFFER, (368 * sizeof(glm::vec3)), gearThreeNormal, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Create a vertex buffer object to store vertices */
	glGenBuffers(1, &positionBufferGearFour);
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferGearFour);
	glBufferData(GL_ARRAY_BUFFER, (700 * sizeof(glm::vec4)), gearFour, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	/* Create a vertex buffer object to store normals */
	glGenBuffers(1, &gearFourNormals);
	glBindBuffer(GL_ARRAY_BUFFER, gearFourNormals);
	glBufferData(GL_ARRAY_BUFFER, (700 * sizeof(glm::vec3)), gearFourNormal, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Create a vertex buffer object to store vertices */
	glGenBuffers(1, &positionBufferCrank);
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferCrank);
	glBufferData(GL_ARRAY_BUFFER, (72 * sizeof(glm::vec4)), crank, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	/* Create a vertex buffer object to store normals */
	glGenBuffers(1, &crankNormals);
	glBindBuffer(GL_ARRAY_BUFFER, crankNormals);
	glBufferData(GL_ARRAY_BUFFER, (72 * sizeof(glm::vec3)), crankNormal, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	/* Create a vertex buffer object to store vertex colours */
	glGenBuffers(1, &colourObject);
	glBindBuffer(GL_ARRAY_BUFFER, colourObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColours), vertexColours, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	try
	{
		program = glw->LoadShader("lab2.vert", "lab2.frag");
	}
	catch (std::exception &e)
	{
		std::cout << "Caught exception: " << e.what() << std::endl;
		std::cin.ignore();
		exit(0);
	}

	/* Define uniforms to send to vertex shader */
	modelID = glGetUniformLocation(program, "model");
	viewID = glGetUniformLocation(program, "view");
	projectionID = glGetUniformLocation(program, "projection");
}

//Called to update the display.
void display()
{
	
	glEnable(GL_DEPTH_TEST);

	/* Define the background colour */
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/* Clear the colour and frame buffers */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program);

	/* Bind colourObject*/
	glBindBuffer(GL_ARRAY_BUFFER, colourObject);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	

	/* Gear One */
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferGearOne);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, gearOneNormals);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(move_model_x, move_model_y, move_model_z));
	model = glm::rotate(model, -angle_x, glm::vec3(1, 0, 0));
	model = glm::rotate(model, -angle_y, glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.91f, 0, 0));
	model = glm::rotate(model, -angle_z, glm::vec3(0, 0, 1));

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(30.0f, aspect_ratio, 0.1f, 100.0f);

	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(0, 0, 9), 
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0) 
		);

	//// Send our transformations to the currently bound shader,
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &View[0][0]);
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, &Projection[0][0]);

	int sidesDraw = (17) * 6;
	int teethDraw = sidesDraw + (8 * 30);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, sidesDraw);
	glDrawArrays(GL_TRIANGLES, sidesDraw, teethDraw);

	/* Gear Two */
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferGearTwo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, gearTwoNormals);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glm::mat4 model2 = glm::mat4(1.0f);
	
	model2 = glm::translate(model2, glm::vec3(move_model_x, move_model_y, move_model_z));
	model2 = glm::rotate(model2, -angle_x, glm::vec3(1, 0, 0));
	model2 = glm::rotate(model2, -angle_y, glm::vec3(0, 1, 0));
	model2 = glm::rotate(model2, (1.6f*angle_z), glm::vec3(0, 0, 1));
	

	//// Send our transformations to the currently bound shader,
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model2[0][0]);

	sidesDraw = (11) * 6;
	teethDraw = sidesDraw + (3 * 30);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, sidesDraw);
	glDrawArrays(GL_TRIANGLES, sidesDraw, teethDraw);

	/* Gear Three */
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferGearThree);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, gearThreeNormals);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 model3 = glm::mat4(1.0f);
	
	model3 = glm::translate(model3, glm::vec3(move_model_x, move_model_y, move_model_z));
	model3 = glm::rotate(model3, -angle_x, glm::vec3(1, 0, 0));
	model3 = glm::rotate(model3, -angle_y, glm::vec3(0, 1, 0));
	model3 = glm::translate(model3, glm::vec3(0.91f, 0, 0));
	model3 = glm::rotate(model3, -angle_z, glm::vec3(0, 0, 1));
	
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model3[0][0]);

	sidesDraw = (17) * 6;
	teethDraw = sidesDraw + (8 * 30);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, sidesDraw);
	glDrawArrays(GL_TRIANGLES, sidesDraw, teethDraw);

	/* Gear Four */
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferGearFour);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, gearFourNormals);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 model4 = glm::mat4(1.0f);

	model4 = glm::translate(model4, glm::vec3(move_model_x, move_model_y, move_model_z));
	model4 = glm::rotate(model4, -angle_x, glm::vec3(1, 0, 0));
	model4 = glm::rotate(model4, -angle_y, glm::vec3(0, 1, 0));
	model4 = glm::translate(model4, glm::vec3(2.51f, 0, 0));
	model4 = glm::rotate(model4, 0.50f*angle_z, glm::vec3(0, 0, 1));

	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model4[0][0]);

	sidesDraw = (27) * 6;
	teethDraw = sidesDraw + (26 * 30);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, sidesDraw);
	glDrawArrays(GL_TRIANGLES, sidesDraw, teethDraw);

	/* Crank */
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferCrank);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, crankNormals);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glm::mat4 crankModel = glm::mat4(1.0f);
	crankModel = glm::translate(crankModel, glm::vec3(move_model_x, move_model_y, move_model_z));
	crankModel = glm::rotate(crankModel, -angle_x, glm::vec3(1, 0, 0));
	crankModel = glm::rotate(crankModel, -angle_y, glm::vec3(0, 1, 0));
	crankModel = glm::translate(crankModel, glm::vec3(-0.91f, 0, 0));
	crankModel = glm::rotate(crankModel, -angle_z, glm::vec3(0, 0, 1));

	//// Send our transformations to the currently bound shader,
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &crankModel[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDrawArrays(GL_TRIANGLES, 36, 72);

	glDisableVertexAttribArray(0);
	glUseProgram(0);


	/* Modify our animation variables */
	angle_z += angle_z_inc;
	angle_x += angle_x_inc;
	angle_y += angle_y_inc;

}


/* Called whenever the window is resized. The new window size is given, in pixels. */
static void reshape(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

/* change view angle, exit upon ESC */
static void keyCallback(GLFWwindow* window, int k, int s, int action, int mods)
{
	if (action != GLFW_PRESS) return;

	if (k == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (k == 'W') move_model_y -= 0.1f; //Move model down (view up)
	if (k == 'S') move_model_y += 0.1f; //Move model up (view down)
	if (k == 'A') move_model_x += 0.1f; //Move model right (view left)
	if (k == 'D') move_model_x -= 0.1f; //Mode model left (view right)
	if (k == 'Q') move_model_z -= 0.3f; //Zoom out
	if (k == 'E') move_model_z += 0.3f; //Zoom in
	if (k == 'Z') angle_z_inc -= 0.1f;  //Decrease gear speed
	if (k == 'X') angle_z_inc += 0.1f;  //Increase gear speed
	/* Rotations round the x and y axis */
	if (k == GLFW_KEY_LEFT) angle_y_inc = angle_y_inc == -0.1f ? 0.0 : 0.1;
	if (k == GLFW_KEY_RIGHT) angle_y_inc = angle_y_inc == 0.1f ? 0.0 : -0.1;
	if (k == GLFW_KEY_UP) angle_x_inc = angle_x_inc == -0.1f ? 0.0 : 0.1;
	if (k == GLFW_KEY_DOWN) angle_x_inc = angle_x_inc == 0.1f ? 0.0 : -0.1;


}



/* An error callback function to output GLFW errors*/
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}





/* Entry point of program */
int main(int argc, char* argv[])
{
	GLWrapper *glw = new GLWrapper(1024, 768, "Tom Butterwith: Gears");;

	if (!ogl_LoadFunctions())
	{
		fprintf(stderr, "ogl_LoadFunctions() failed. Exiting\n");
		return 0;
	}

	/* Note it you might want to move this call to the wrapper class */
	glw->setErrorCallback(error_callback);

	glw->setRenderer(display);
	glw->setKeyCallback(keyCallback);
	glw->setReshapeCallback(reshape);

	init(glw);

	glw->eventLoop();

	delete(glw);
	return 0;
}



