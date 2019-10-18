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
#include "InputManager.h"
#include "ResourceManager.h"
#include "FramerateManager.h"
#include <string>

#define MOVEMENT_SPEED 5
#define MAX_FRAME_RATE 60

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
	InputManager *pIM = new InputManager;
	ResourceManager *pRM = new ResourceManager;
	FramerateManager *pFM = new FramerateManager(MAX_FRAME_RATE);
	SDL_Surface *pCharacter, *pImage, *pWindowSurface;

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
	pWindowSurface = SDL_GetWindowSurface(pWindow);
	std::string path = "Resources/background.bmp";
	if (!pRM->RegisterSurface(path)) {
		printf("Could not load resource: %s\n", path);
		return 1;
	}
	pImage = pRM->GetSurfaceByPath(path);

	// Get character BMP for controlling
	std::string character_path = "Resources/bird.bmp";
	if (!pRM->RegisterSurface(character_path)) {
		std::string s = SDL_GetError();
		printf("Could not load resource: %s\nReason: %s", character_path, s);
		return 1;
	}
	pCharacter = pRM->GetSurfaceByPath(character_path);

	SDL_Rect * character_offset = new SDL_Rect;
	character_offset->x = 0;
	character_offset->y = 0;
	
	// Game loop
	while(true == appIsRunning)
	{
		// Record frame start time
		pFM->FrameStart();

		// Draw
		SDL_BlitSurface(pImage, NULL, pWindowSurface, NULL);
		SDL_BlitSurface(pCharacter, NULL, pWindowSurface, character_offset);
		SDL_UpdateWindowSurface(pWindow);

		SDL_Event e;
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				appIsRunning = false;
			}
		}

		// Input events
		pIM->update_state();
		if (pIM->key_pressed(SDL_SCANCODE_UP)) {
			character_offset->y -= MOVEMENT_SPEED;
		}
		else if (pIM->key_pressed(SDL_SCANCODE_DOWN)) {
			character_offset->y += MOVEMENT_SPEED;
		}
		else if (pIM->key_pressed(SDL_SCANCODE_LEFT)) {
			character_offset->x -= MOVEMENT_SPEED;
		}
		else if (pIM->key_pressed(SDL_SCANCODE_RIGHT)) {
			character_offset->x += MOVEMENT_SPEED;
		}

		// update frame end time
		pFM->FrameEnd();
	}

	// Free all registered surface
	pRM->FreeAll();

	// Close and destroy the window
	SDL_DestroyWindow(pWindow);

	// Quit SDL subsystems
	SDL_Quit();
	
	return 0;
}