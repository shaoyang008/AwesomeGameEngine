/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: GameObjectManager.h
Purpose: Creates and manages all game objects
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/19/2019

---------------------------------------------------------*/

#pragma once
#include <vector>
#include <fstream>
#include <json.hpp>
#include "GameObject.h"
#include "ObjectFactory.h"
#include "Utilities/Base.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void Initialize();
	void Update();
	void LoadLevel(json);

	void DeactivateObjects();

	GameObject * GetObject(std::string);
	
	std::vector<GameObject*> _objects;
	std::unordered_map<std::string, GameObject*> _uniqueObjects;
	BinaryTree<std::string, GameObject*> _tagObjects;

private:
	ObjectFactory *_factory;
	std::vector<GameObject*> _inactiveObjects;
};
