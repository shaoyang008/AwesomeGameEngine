/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: ShaderProgram.h
Purpose: Compile and link shader programs
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

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

