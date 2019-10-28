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
#include "stdio.h"
#include "GameStateManager.h"
#include <string>
#include <GLFW/glfw3.h>

#define MOVEMENT_SPEED 5
#define MAX_FRAME_RATE 60

GameStateManager *pMgr = new GameStateManager;
FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

#pragma comment(lib, "legacy_stdio_definitions.lib")

int main(int argc, char* args[])
{
	SDL_Window *pWindow;
	int error = 0;
	bool appIsRunning = true;

	// Initialize SDL
	if((error = SDL_Init( SDL_INIT_VIDEO )) < 0 )
	{
		printf("Couldn't initialize SDL, error %i\n", error);
		return 1;
	}


	pWindow = SDL_CreateWindow("SDL2 window",		// window title
		SDL_WINDOWPOS_UNDEFINED,					// initial x position
		SDL_WINDOWPOS_UNDEFINED,					// initial y position
		800,										// width, in pixels
		600,										// height, in pixels
		SDL_WINDOW_SHOWN);

	// Check that the window was successfully made
	if (NULL == pWindow)
	{
		// In the event that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	// Read background BMP
	pMgr->SetWindow(pWindow);
	if (!pMgr->Init()) {
		std::cout << "Something wrong." << std::endl;
		return 1;
	}

	
	// Game loop
	while(true == appIsRunning)
	{
		appIsRunning = pMgr->Loop();

		SDL_Event e;
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				appIsRunning = false;
			}
		}
	}

	delete pMgr;

	// Close and destroy the window
	SDL_DestroyWindow(pWindow);

	// Quit SDL subsystems
	SDL_Quit();
	
	return 0;
}