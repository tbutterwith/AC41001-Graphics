#include "textureLoader.h"

textureLoader::textureLoader(){

}

textureLoader::~textureLoader(){

}

GLuint textureLoader::loadTexture(char* fileName, GLuint program){
	GLuint texID;
	try
	{
		/* Not actually needed if using one texture at a time */
		glActiveTexture(GL_TEXTURE0);

		/* load an image file directly as a new OpenGL texture */
		texID = SOIL_load_OGL_texture(fileName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

		/* check for an error during the load process */
		if (texID == 0)
		{
			printf("TexID SOIL loading error: '%s'\n", SOIL_last_result());
		}

		/* Standard bit of code to enable a uniform sampler for our texture */
		int loc = glGetUniformLocation(program, "tex1");
		//if (loc >= 0) glUniform1i(loc, 0);
	}
	catch (std::exception &e)
	{
		printf("\nImage file loading failed.");
	}

	return texID;
}

GLuint textureLoader::loadNormals(char* fileName, GLuint program){
	GLuint texID;
	try
	{
		/* Not actually needed if using one texture at a time */
		glActiveTexture(GL_TEXTURE1);

		/* load an image file directly as a new OpenGL texture */
		texID = SOIL_load_OGL_texture(fileName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

		/* check for an error during the load process */
		if (texID == 0)
		{
			printf("TexID SOIL loading error: '%s'\n", SOIL_last_result());
		}

		/* Standard bit of code to enable a uniform sampler for our texture */
		int loc = glGetUniformLocation(program, "norm1");
		//if (loc >= 0) glUniform1i(loc, 0);
	}
	catch (std::exception &e)
	{
		printf("\nImage file loading failed.");
	}

	return texID;
}