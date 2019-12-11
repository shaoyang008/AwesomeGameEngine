/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: ShaderProgram.cpp
Purpose: Compile and link shader programs
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
	_programId = glCreateProgram();
}


ShaderProgram::~ShaderProgram()
{
}

std::string ShaderProgram::ReadFile(const char* file_name)
{
	std::ifstream shader_file(file_name, std::ios::in);
	if (!shader_file.is_open()) {
		return NULL;
	}
	std::string shader_text((std::istreambuf_iterator<char>(shader_file)), std::istreambuf_iterator<char>());
	shader_file.close();

	return shader_text;
}

void ShaderProgram::CompileShader(const char* file_name, GLenum type)
{
	std::string shader_text = ReadFile(file_name);
	const char * shader_ptr = shader_text.c_str();

	GLint result = GL_FALSE;
	int info_log_length;

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &shader_ptr, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
	if (info_log_length > 0) {
		std::vector<char> shader_error_message(info_log_length + 1);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_error_message[0]);
		printf("%s\n", &shader_error_message[0]);
	}

	glAttachShader(_programId, shader);
}

void ShaderProgram::LinkShader()
{
	// Link program and check the status
	glLinkProgram(_programId);
	int status;
	glGetProgramiv(_programId, GL_LINK_STATUS, &status);

	// If link failed, get and print log
	if (status != 1) {
		int length;
		glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &length);
		char* buffer = new char[length];
		glGetProgramInfoLog(_programId, length, NULL, buffer);
		printf("Link log:\n%s\n", buffer);
		delete buffer;
	}
}
