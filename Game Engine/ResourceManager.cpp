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

ResourceManager::ResourceManager() 
{

}

ResourceManager::~ResourceManager()
{
	FreeAll();
}

bool ResourceManager::RegisterModel(std::string path)
{
	if (_resources[path]) return true;
	else {
		ObjectModel * model = new ObjectModel;
		model->ReadModel(path);
		if (!model) {
			delete model;
			return false;
		}
		else {
			_resources[path] = model;
			return true;
		}
	}
}

ObjectModel * ResourceManager::GetModelByPath(std::string path)
{
	return _resources[path];
}

void ResourceManager::FreeAll()
{
	std::unordered_map<std::string, ObjectModel*>::iterator it;
	for (it = _resources.begin(); it != _resources.end(); ++it) {
		delete it->second;
	}
}