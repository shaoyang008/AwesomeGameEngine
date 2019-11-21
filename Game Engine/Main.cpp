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

#define MOVEMENT_SPEED 5
#define MAX_FRAME_RATE 60

#define USING_OPENGL 0

GameStateManager *pMgr = new GameStateManager;
FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

#pragma comment(lib, "legacy_stdio_definitions.lib")

int main(int argc, char* args[])
{
	int error = 0;
	bool appIsRunning = true;

	// Initialize SDL
	if ((error = SDL_Init(SDL_INIT_VIDEO)) < 0)
	{
		printf("Couldn't initialize SDL, error %i\n", error);
		return 1;
	}


	// Setup Manager
	if (!pMgr->Load()) {
		std::cout << "Something wrong." << std::endl;
		return 1;
	}

	// Game loop
	while(true == appIsRunning)
	{

		pMgr->RunGame();
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				appIsRunning = false;
			}
		}
	}
	
	// Destroy game manager
	delete pMgr;

	// Close and destroy SDLs
	SDL_Quit();

	return 0;
}