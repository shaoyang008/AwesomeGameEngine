/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Main.cpp
Purpose: Initialize each managers and run game loops
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/14/2019

---------------------------------------------------------*/

#include <SDL.h>
#include <stdio.h>
#include <string>
#include "GameStateManager.h"
#include "ShaderProgram.h"

#include "Model.h"

#define MOVEMENT_SPEED 5
#define MAX_FRAME_RATE 60

#define USING_OPENGL 1

GameStateManager *pMgr = new GameStateManager;
FILE _iob[] = { *stdin, *stdout, *stderr };

#if USING_OPENGL
void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}
#endif

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

#pragma comment(lib, "legacy_stdio_definitions.lib")

int main(int argc, char* args[])
{
	SDL_Window *window;
	int error = 0;
	bool appIsRunning = true;

	// Initialize SDL
	if ((error = SDL_Init(SDL_INIT_VIDEO)) < 0)
	{
		printf("Couldn't initialize SDL, error %i\n", error);
		return 1;
	}

	window = SDL_CreateWindow("SDL2 window",		// window title
		SDL_WINDOWPOS_UNDEFINED,					// initial x position
		SDL_WINDOWPOS_UNDEFINED,					// initial y position
		800,										// width, in pixels
		600,										// height, in pixels
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	// Check that the window was successfully made
	if (NULL == window)
	{
		// In the event that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

#if USING_OPENGL
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cerr << "SDL2 Renderer couldn't be created. Error: "
			<< SDL_GetError()
			<< std::endl;
		exit(1);
	}

	// Create a OpenGL context on SDL2
	SDL_GLContext gl_context = SDL_GL_CreateContext(window);

	// Load GL extensions using glad
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		std::cerr << "Failed to initialize the OpenGL context." << std::endl;
		exit(1);
	}

	// Loaded OpenGL successfully.
	std::cout << "OpenGL version loaded: " << GLVersion.major << "." << GLVersion.minor << std::endl;

	// Shader program
	ShaderProgram *shader = new ShaderProgram;

	shader->CompileShader("Shaders/lighting_vert.glsl", GL_VERTEX_SHADER);
	shader->CompileShader("Shaders/lighting_frag.glsl", GL_FRAGMENT_SHADER);

	glBindAttribLocation(shader->_programId, 0, "vertex");
	glBindAttribLocation(shader->_programId, 1, "texcoord");
	glBindAttribLocation(shader->_programId, 2, "normal");
	shader->LinkShader();
	
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
#else
	// Setup Manager
	pMgr->SetWindow(window);
	if (!pMgr->Load()) {
		std::cout << "Something wrong." << std::endl;
		return 1;
	}
#endif

	// ReadModel("Resources/box.obj");
	Model *m = new Model;
	m->Initialize();

	// Game loop
	while(true == appIsRunning)
	{
#if USING_OPENGL
		glViewport(0, 0, 800, 600);

		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shader->_programId);

		m->Draw();

		glUseProgram(0);

		// Swap buffers
		SDL_GL_SwapWindow(window);
#else
		pMgr->RunGame();
#endif
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				appIsRunning = false;
			}
		}
	}
	
#if USING_OPENGL
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyRenderer(renderer);
#else
	delete pMgr;
#endif
	// Close and destroy SDLs
	SDL_Quit();

	return 0;
}