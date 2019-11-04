#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glad/glad.h>

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	std::string ReadFile(const char*);
	void CompileShader(const char*, GLenum);
	void LinkShader();

	GLuint _programId;
};

