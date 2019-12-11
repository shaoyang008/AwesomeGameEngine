/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: RenderManager.h
Purpose: Initialize and use OpenGL
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#pragma once
#include "ShaderProgram.h"
#include "ObjectModel.h"
#include "GameObject.h"
#include "Components/Base.h"
#include <SDL_render.h>
#include <iostream>

class RenderManager
{
public:
	RenderManager();
	~RenderManager();

	void Initialize(SDL_Window*);
	void Draw();
	void Draw2D();
	void DrawDebug();

	void ResizeWindow();
	bool SetCamera(std::string);
	/*
	static void error_callback(int error, const char* description)
	{
		fprintf(stderr, "Error: %s\n", description);
	}
	*/
	void SwitchMode(int mode);

	// 2D drawing
	void Init2D();


private:
	SDL_Window *_window;
	SDL_Renderer *_renderer;
	SDL_GLContext _glcontext;
	ShaderProgram *_shader;
	ShaderProgram *_shader2d;

	int _width, _height;

	GameObject * _viewer;
	Camera * _camera;
	Light * _light;

	int _renderMode;
	GLuint quadVAO;
};

