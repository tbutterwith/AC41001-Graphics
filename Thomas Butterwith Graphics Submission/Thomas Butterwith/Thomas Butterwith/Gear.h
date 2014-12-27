/* Link to static libraries, could define these as linker inputs in the project settings instead
if you prefer */
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glloadD.lib")
#pragma comment(lib, "opengl32.lib")

/* Include the header to the GLFW wrapper class which
also includes the OpenGL extension initialisation*/
#include "wrapper_glfw.h"
#include <iostream>

/* GLM core */
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

class Gear {
public:
	Gear();
	glm::vec4 * createGear(float, int, int, float, float);
	glm::vec3 * calculateNormals(glm::vec4 *, int, int);

private:
	CONST float pi = 3.14159265358979323846264338327950288f;
	GLfloat toothLength = 0.12f;
	GLfloat toothDepth = 0.1f;

	
};