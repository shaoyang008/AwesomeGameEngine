#include "Material.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


Material::Material(): _diffuse(vec3(0, 0, 0)), _specular(vec3(1, 1, 1)), _ambient(vec3(0, 0, 0)), _shininess(1.0f), _hasTexture(false)
{
}


Material::~Material()
{
}

void Material::LoadMap(std::string path)
{
	glGenTextures(1, &_textureId);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture " << path << std::endl;
	}
	stbi_image_free(data);

	_hasTexture = true;
}

void Material::Use(GLuint programId)
{
	GLuint loc;
	loc = glGetUniformLocation(programId, "diffuse");
	glUniform3fv(loc, 1, &_diffuse[0]);

	loc = glGetUniformLocation(programId, "specular");
	glUniform3fv(loc, 1, &_specular[0]);

	loc = glGetUniformLocation(programId, "shininess");
	glUniform1f(loc, _shininess +1);

	loc = glGetUniformLocation(programId, "hasTexture");
	glUniform1i(loc, _hasTexture);

	glBindTexture(GL_TEXTURE_2D, _textureId);
}

void Material::Unuse()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}