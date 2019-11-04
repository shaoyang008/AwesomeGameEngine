/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: ResourceManager.cpp
Purpose: Register textures and stored them by map
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/14/2019

---------------------------------------------------------*/

#include "ResourceManager.h"
#include "SDL_surface.h"

ResourceManager::ResourceManager() {}
ResourceManager::~ResourceManager()
{
	FreeAll();
}

bool ResourceManager::RegisterSurface(std::string path)
{
	if (_resources[path]) return true;
	else {
		SDL_Surface * new_surface = SDL_LoadBMP(path.c_str());
		if (!new_surface) return false;
		else {
			_resources[path] = new_surface;
			return true;
		}
	}
}

SDL_Surface * ResourceManager::GetSurfaceByPath(std::string path)
{
	return _resources[path];
}

void ResourceManager::FreeAll()
{
	std::unordered_map<std::string, SDL_Surface*>::iterator it;
	for (it = _resources.begin(); it != _resources.end(); ++it) {
		SDL_FreeSurface(it->second);
	}
}