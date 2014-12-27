#include "Object_3DS.h"

Object_3DS::Object_3DS(char* filename){
	m_TotalFaces = 0;

	m_model = lib3ds_file_load(filename);

	if (!m_model) {
		printf("Error loading libs3ds file\n");
	}
}

Object_3DS::~Object_3DS(){}

void Object_3DS::getFaces()
{
	assert(m_model != NULL);

	m_TotalFaces = 0;
	Lib3dsMesh * mesh;
	// Loop through every mesh
	for (mesh = m_model->meshes; mesh != NULL; mesh = mesh->next)
	{
		// Add the number of faces this mesh has to the total faces
		m_TotalFaces += mesh->faces;
	}
}

void Object_3DS::createObject()
{
	assert(m_model != NULL);

	// Calculate the number of faces we have in total
	getFaces();

	// Allocate memory for our vertices and normals
	Lib3dsVector * vertices = new Lib3dsVector[m_TotalFaces * 3];
	Lib3dsVector * normals = new Lib3dsVector[m_TotalFaces * 3];

	Lib3dsMesh * mesh;
	unsigned int FinishedFaces = 0;
	// Loop through all the meshes
	for (mesh = m_model->meshes; mesh != NULL; mesh = mesh->next)
	{
		lib3ds_mesh_calculate_normals(mesh, &normals[FinishedFaces * 3]);
		// Loop through every face
		for (unsigned int cur_face = 0; cur_face < mesh->faces; cur_face++)
		{
			Lib3dsFace * face = &mesh->faceL[cur_face];
			for (unsigned int i = 0; i < 3; i++)
			{
				memcpy(&vertices[FinishedFaces * 3 + i], mesh->pointL[face->points[i]].pos, sizeof(Lib3dsVector));
			}
			FinishedFaces++;
		}
	}

	// Generate a Vertex Buffer Object and store it with our vertices
	glGenBuffers(1, &m_VertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Lib3dsVector)* 3 * m_TotalFaces, vertices, GL_STATIC_DRAW);

	// Generate another Vertex Buffer Object and store the normals in it
	glGenBuffers(1, &m_NormalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_NormalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Lib3dsVector)* 3 * m_TotalFaces, normals, GL_STATIC_DRAW);

	// Clean up our allocated memory
	delete[] vertices;
	delete[] normals;

	// We no longer need lib3ds
	lib3ds_file_free(m_model);
	m_model = NULL;
}

// Render the model using Vertex Buffer Objects
void Object_3DS::draw() const
{
	assert(m_TotalFaces != 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexVBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_NormalVBO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	/*glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, textures);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	*/

}