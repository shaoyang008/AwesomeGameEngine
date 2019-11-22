#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>
using namespace glm;

#include "Material.h"

class ObjectModel
{
public:
	ObjectModel();
	~ObjectModel();

	void DrawChildren(GLuint, bool);
	void Draw(GLuint, bool);
	void Initialize();

	void ReadModel(std::string);
	void ReadMtl(std::string, std::map<std::string, Material*>&);

	std::vector<ObjectModel*> _children;

private:
	GLuint _VAOid;
	std::vector<vec3> _vertex, _normal;
	std::vector<vec2> _texture;
	std::vector<ivec3> _vertexIndex;
	Material * _material;
};
