/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Sprite.cpp
Purpose: Sprite of objects
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/19/2019

---------------------------------------------------------*/

#include "Sprite.h"
#include "../GameStateManager.h"

extern GameStateManager *pMgr;

Sprite::Sprite(): Component(COMPONENT_TYPE::SPRITE), pSurface(NULL)
{
}

Sprite::~Sprite()
{
}

void Sprite::Update() {

}

void Sprite::Serialize(std::string data)
{
	std::string path = "Resources/" + data;
	if (!pMgr->_resourceManager->RegisterSurface(path)) {
		std::cout << "Could not load resource: " << path << ", Reason: " << SDL_GetError() << std::endl;
		return;
	}
	pSurface = pMgr->_resourceManager->GetSurfaceByPath(path);
}
