#include "wrapper_glfw.h"
#include <vector>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

#include <lib3ds/types.h>
#include <lib3ds/file.h>
#include <lib3ds/mesh.h>
class Object_3DS{
public:
	Object_3DS(char*);
	virtual ~Object_3DS();

	virtual void draw() const;
	virtual void createObject();

protected:
	void getFaces();
	unsigned int m_TotalFaces;
	Lib3dsFile * m_model;
	GLuint m_VertexVBO, m_NormalVBO, textures;
};