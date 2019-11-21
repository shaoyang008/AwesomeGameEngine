#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
using namespace glm;

class ObjectModel
{
public:
	ObjectModel();
	~ObjectModel();

	void Draw();
	void Initialize(std::string);
	void ReadModel(std::string);

private:
	GLuint _VAOid;
	std::vector<vec3> _vertex, _normal;
	std::vector<vec2> _texcoord;
	std::vector<ivec3> _vertexIndex, _normalIndex, _textureIndex;
};
