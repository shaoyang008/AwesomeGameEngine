/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Material.h
Purpose: Read and save lighting information and textures
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

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
	bool _hasTexture;
};

