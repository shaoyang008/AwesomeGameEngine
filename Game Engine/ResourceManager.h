/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: ResourceManager.h
Purpose: Register textures and stored them by map
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/14/2019

---------------------------------------------------------*/

#pragma once
#include <unordered_map>
#include <string>

struct SDL_Surface;

class ResourceManager {
public:
	ResourceManager();
	~ResourceManager();

	bool RegisterSurface(std::string);
	SDL_Surface * GetSurfaceByPath(std::string);
	void FreeAll();

private:
	std::unordered_map<std::string, SDL_Surface*> _resources;
};