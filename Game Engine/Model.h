#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
using namespace glm;

class Model
{
public:
	Model();
	~Model();

	void Draw();
	void Initialize();
	void ReadModel(std::string);

private:
	GLuint _VAOid;
	std::vector<vec3> _vertex, _normal;
	std::vector<vec2> _texcoord;
	std::vector<ivec3> _vertexIndex, _normalIndex, _textureIndex;
};
