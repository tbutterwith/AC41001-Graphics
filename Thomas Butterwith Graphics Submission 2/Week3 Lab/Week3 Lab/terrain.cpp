/*
 Terrain example
 Creates a class to define a terrain with an array of vertices and calculates vertex normalsd
 Iain Martin October 2014
*/


/* Link to static libraries, could define these as linker inputs in the project settings instead
if you prefer */
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glloadD.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "soil.lib")

/* Include the header to the GLFW wrapper class which
   also includes the OpenGL extension initialisation*/
#include "wrapper_glfw.h"
#include <iostream>

/* Include GLM core and matrix extensions*/
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "object_ldr.h"
#include "terrain_object.h"
#include "room.h"
#include "Floor.h"
#include "textureLoader.h"
#include "Sky.h"
#include "SquarePlanter.h"
#include "particle_object.h"
/* Include the hacked version of SOIL */
#include "soil.h"

/* Define buffer object indices */
GLuint positionBufferObject, colourObject, normalsBufferObject;
GLuint elementbuffer;

GLuint program, particle_program;		/* Identifier for the shader prgoram */
GLuint vao;			/* Vertex array (Containor) object. This is the index of the VAO that will be the container for
					   our buffer objects */

GLuint colourmode;	/* Index of a uniform to switch the colour mode in the vertex shader
					  I've included this to show you how to pass in an unsigned integer into
					  your vertex shader. */

/* Position and view globals */
GLfloat angle_x, angle_inc_x, x, scale, z, y;
GLfloat angle_y, angle_inc_y, angle_z, angle_inc_z;
GLuint drawmode;			// Defines drawing mode of sphere as points, lines or filled polygons

/* Uniforms*/
GLuint modelID, viewID, projectionID;
GLuint colourmodeID, weather;
/* Define textureID*/
GLuint texID, normalID;

GLfloat px, py, pz;
particle_object particleObject;

GLfloat aspect_ratio;		/* Aspect ratio of the window defined in the reshape callback*/

object_ldr birchTree, tree2, tree3, tree4, tree5, tree6, tree7, tree8, tree9;
room walls;
Floor flooring;
Sky sky;
textureLoader textureLoad;
std::vector<SquarePlanter> planters;
terrain_object *snow;

GLfloat octaves, perlin_scale, perlin_frequency, land_size;

GLfloat roomLength = 20.0f;
GLfloat roomHeight = 5.0f;

void createPlanters() {
	GLuint innerTexture = textureLoad.loadTexture("images/dirt.png", program);
	GLuint outerTexture = textureLoad.loadTexture("images/oak.png", program);
	GLuint outerNormals = textureLoad.loadNormals("images/oak_bump.png", program);
	SquarePlanter planter1;
	planter1.createSquarePlanter(20.0f, 2.0f, 1.4f, -20.0f, -18.0f);
	planter1.setInnerTex(innerTexture);
	planter1.setOuterTex(outerTexture);
	planter1.setOuterNormals(outerNormals);
	planters.push_back(planter1);
	SquarePlanter planter2;
	planter2.createSquarePlanter(20.0f, 2.0f, 1.4f, 0.0f, -18.0f);
	planter2.setInnerTex(innerTexture);
	planter2.setOuterTex(outerTexture);
	planter2.setOuterNormals(outerNormals);
	planters.push_back(planter2);
	SquarePlanter planter3;
	planter3.createSquarePlanter(2.0f, 20.0f, 1.4f, -20.0f, 0.0f);
	planter3.setInnerTex(innerTexture);
	planter3.setOuterTex(outerTexture);
	planter3.setOuterNormals(outerNormals);
	planters.push_back(planter3);
	SquarePlanter planter4;
	planter4.createSquarePlanter(2.0f, 20.0f, 1.4f, 18.0f, 0.0f);
	planter4.setInnerTex(innerTexture);
	planter4.setOuterTex(outerTexture);
	planter4.setOuterNormals(outerNormals);
	planters.push_back(planter4);

	SquarePlanter planter5;
	planter5.createSquarePlanter(2.0f, 14.0f, 0.7f, -1.0f, -4.0f);
	planter5.setInnerTex(innerTexture);
	planter5.setOuterTex(outerTexture);
	planter5.setOuterNormals(outerNormals);
	planters.push_back(planter5);
}

void printInstructions(){
	std::cout << "---------------------------------------------------" << std::endl;
	std::cout << "|  CONTROLS                                       |" << std::endl;
	std::cout << "|-------------------------------------------------|" << std::endl;
	std::cout << "|  E  -  Rotate around Y                          |" << std::endl;
	std::cout << "|  R  -  Rotate around Y                          |" << std::endl;
	std::cout << "|  M  -  Change Weather                           |" << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
}
/*
This function is called before entering the main rendering loop.
Use it for all your initialisation stuff
*/
void init(GLWrapper *glw)
{
	printInstructions();
	textureLoad = textureLoader();
	/* Set the object transformation controls to their initial values */
	x = 0;
	y = 0;
	z = 0;
	angle_x = 0;
	angle_y = angle_z = 0;
	angle_inc_x = angle_inc_y = angle_inc_z = 0;
	scale = 0.33f;
	aspect_ratio = 1.3333f;
	colourmode = 0;
	weather = 0;

	px, py, pz = 0;

	// Generate index (name) for one vertex array object
	glGenVertexArrays(1, &vao);

	// Create the vertex array object and make it current
	glBindVertexArray(vao);

	/* Define the Blending function */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLfloat vertexColours[] =
	{
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f
	};

	/* Create the colours buffer for the cube */
	glGenBuffers(1, &colourObject);
	glBindBuffer(GL_ARRAY_BUFFER, colourObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColours), vertexColours, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	/* Load and create our monkey object*/
	birchTree.load_obj("birch_tree.obj");
	walls.createRoom(roomLength, roomHeight);
	walls.setTexture(textureLoad.loadTexture("images/brickwork_texture.png", program));
	walls.setNormalsMap(textureLoad.loadNormals("images/brickwork_normal_map.png", program));

	flooring.createFloor(roomLength, roomHeight);
	flooring.setTexture(textureLoad.loadTexture("images/masonry_wall_texture.png", program));
	flooring.setNormalsMap(textureLoad.loadNormals("images/masonry_wall_normal_map.png", program));

	//sky.createSky();
	createPlanters();


	/* Calculate vertex normals using cross products from the surrounding faces*/
	/* A better way to do this would be to generate the vertex normals in Blender and
	/* then extract the vertex normals from the face definitions and use that to create an
	/* accurate array of veretx normals */
	birchTree.smoothNormals();
	birchTree.createObject();


	tree2 = tree3 = tree4 = tree5 = tree6 = tree6 = tree8 = tree9 = birchTree;
	
	/* Load and build the vertex and fragment shaders */
	try
	{
		particle_program = glw->LoadShader("particle_object.vert", "particle_object.frag");
		program = glw->LoadShader("terrain.vert", "terrain.frag");
	}
	catch (std::exception &e)
	{
		std::cout << "Caught exception: " << e.what() << std::endl;
		std::cin.ignore();
		exit(0);
	}

	/* Define uniforms to send to vertex shader */
	modelID = glGetUniformLocation(program, "model");
	colourmodeID = glGetUniformLocation(particle_program, "weather");
	viewID = glGetUniformLocation(program, "view");
	projectionID = glGetUniformLocation(program, "projection");

	

	/* Define the texture behaviour parameters */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	particleObject.create(particle_program);
	/* Create the heightfield object */
	
	octaves = 1;
	perlin_scale = 1.0f;
	perlin_frequency = 50.0f;
	land_size = 15.0f;
	snow = new terrain_object(octaves, perlin_frequency, perlin_scale);
	snow->createTerrain(1000, 1000, land_size, land_size);
	snow->createObject();
	snow->setTexture(textureLoad.loadTexture("images/snow.png", program));
}

/* Called to update the display. Note that this function is called in the event loop in the wrapper
   class because we registered display as a callback function */
void display()
{
	/* Define the background colour */
	if (weather == 0)
		glClearColor(0.25f, 0.7f, 1.0f, 1.0f);
	else 
		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

	/* Clear the colour and frame buffers */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Enable depth test  */
	glEnable(GL_DEPTH_TEST);

	/* Make the compiled shader program current */
	glUseProgram(program);


	/* Bind cube colours. Note that this is in attribute index 1 */
	glBindBuffer(GL_ARRAY_BUFFER, colourObject);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);


	// Define the model transformations for the cube
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, y, z));
	model = glm::scale(model, glm::vec3(scale, scale, scale));//scale equally in all axis
	model = glm::rotate(model, -angle_x, glm::vec3(1, 0, 0)); //rotating in clockwise direction around x-axis
	model = glm::rotate(model, -angle_y, glm::vec3(0, 1, 0)); //rotating in clockwise direction around y-axis
	model = glm::rotate(model, -angle_z, glm::vec3(0, 0, 1)); //rotating in clockwise direction around z-axis

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(30.0f, aspect_ratio, 0.1f, 100.0f);

	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(0, 0.8, 6), // Camera is at (0,0,4), in World Space
		glm::vec3(0, 0.8, 0), // and looks at 1 on the y
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);

	// Send our uniforms variables to the currently bound shader,
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
	glUniform1ui(colourmodeID, weather);
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &View[0][0]);
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, &Projection[0][0]);

	flooring.drawFloor();
	walls.drawRoom();
	//sky.drawSky();

	for (int i = 0; i < planters.size(); i++) {
		SquarePlanter planter = planters[i];
		planter.drawSquarePlanter();
	}

	glm::mat4 model2 = model;
	model2 = glm::scale(model2, glm::vec3(3.0f, 3.0f, 3.0f));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model2[0][0]);

	birchTree.drawObject();

	glm::mat4 model3 = glm::translate(model2, glm::vec3(1.0f, 0.0f, -0.5f));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model3[0][0]);
	tree2.drawObject();

	glm::mat4 model4 = glm::translate(model2, glm::vec3(-0.6f, 0.0f, -0.5f));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model4[0][0]);
	tree3.drawObject();

	glm::mat4 model5 = glm::translate(model2, glm::vec3(0.4f, 0.0f, 0.2f));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model5[0][0]);
	tree4.drawObject();

	glm::mat4 model6 = glm::translate(model2, glm::vec3(-0.4f, 0.0f, -0.2f));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model6[0][0]);
	tree5.drawObject();

	glm::mat4 model7 = glm::translate(model2, glm::vec3(0.1f, 0.0f, 0.8f));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model7[0][0]);
	tree6.drawObject();

	glm::mat4 model8 = glm::translate(model2, glm::vec3(0.0f, 0.0f, -0.5f));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model8[0][0]);
	tree7.drawObject();

	glm::mat4 model9 = glm::translate(model2, glm::vec3(-1.0f, 0.0f, 0.2f));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model9[0][0]);
	tree8.drawObject();

	glm::mat4 model10 = glm::translate(model2, glm::vec3(0.5f, 0.0f, -0.4f));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model10[0][0]);
	tree9.drawObject();

	if (weather == 2)
		snow->drawObject(0);

	/* Modify our animation variables */
	angle_x += angle_inc_x;
	angle_y += angle_inc_y;
	angle_z += angle_inc_z;

	glm::mat4 ParticleView = glm::lookAt(
		glm::vec3(0, 0, 4),
		glm::vec3(-px, -py, -pz),
		glm::vec3(0, 1, 0)
		);
	/* Update and draw our particle animation */
	if (weather != 0)
		particleObject.drawParticles(Projection, ParticleView, colourmodeID, weather);


}

/* Called whenever the window is resized. The new window size is given, in pixels. */
static void reshape(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	aspect_ratio = ((float)w / 640.f*4.f) / ((float)h / 480.f*3.f);
}

/* change view angle, exit upon ESC */
static void keyCallback(GLFWwindow* window, int key, int s, int action, int mods)
{
	bool recreate_terrain = false;		// Set to true if we want to recreate the terrain
	/* Enable this call if you want to disable key responses to a held down key*/
	//if (action != GLFW_PRESS) return;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	//if (key == 'Q') angle_inc_x -= 0.05f;
	//if (key == 'W') angle_inc_x += 0.05f;
	if (key == 'E') angle_inc_y -= 0.05f;
	if (key == 'R') angle_inc_y += 0.05f;
	//if (key == 'T') angle_inc_z -= 0.05f;
	//if (key == 'Y') angle_inc_z += 0.05f;
	//if (key == 'A') scale -= 0.02f;
	//if (key == 'S') scale += 0.02f;
	//if (key == 'Z') x -= 0.05f;
	//if (key == 'X') x += 0.05f;
	//if (key == 'C') y -= 0.05f;
	//if (key == 'V') y += 0.05f;
	//if (key == 'B') z -= 0.05f;
	//if (key == 'N') z += 0.05f;

	if (key == 'M' && action != GLFW_PRESS)
	{
		weather++;
		if (weather > 2) { weather = 0; }

	}


	
}



/* Entry point of program */
int main(int argc, char* argv[])
{
	GLWrapper *glw = new GLWrapper(1024, 768, "Colourful Noise");;

	if (!ogl_LoadFunctions())
	{
		fprintf(stderr, "ogl_LoadFunctions() failed. Exiting\n");
		return 0;
	}

	glw->setRenderer(display);
	glw->setKeyCallback(keyCallback);
	glw->setReshapeCallback(reshape);

	init(glw);

	glw->eventLoop();

	delete(glw);
	return 0;
}





