#pragma once
#include "ShaderProgram.h"
#include "ObjectModel.h"
#include "GameObject.h"
#include <SDL_render.h>
#include <iostream>

class RenderManager
{
public:
	RenderManager();
	~RenderManager();

	void Initialize(SDL_Window*);
	void Draw();

	bool SetCamera(std::string);
	/*
	static void error_callback(int error, const char* description)
	{
		fprintf(stderr, "Error: %s\n", description);
	}
	*/
	void SwitchMode();

private:
	SDL_Window *_window;
	SDL_Renderer *_renderer;
	SDL_GLContext _glcontext;
	ShaderProgram *_shader;

	float _lightPos[3], _light[3], _ambient[3];
	int _width, _height;

	GameObject * _viewer;

	int _renderMode;
};

