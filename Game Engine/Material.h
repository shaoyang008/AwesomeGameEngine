#pragma once
#include <string>
#include <iostream>
#include <fstream>

#include <glad/glad.h>
#include <glm/glm.hpp>
using namespace glm;

class Material
{
public:
	Material();
	~Material();

	void LoadMap(std::string);

	void Use(GLuint);
	void Unuse();

	vec3 _diffuse, _specular, _ambient;
	float _shininess;
	GLuint _textureId;
};

