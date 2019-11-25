/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: GameObjectManager.cpp
Purpose: Creates and manages all game objects
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/19/2019

---------------------------------------------------------*/

#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(): _tagObjects(BinaryTree<std::string, GameObject*>()), _factory(new ObjectFactory)
{
}


GameObjectManager::~GameObjectManager()
{
	// for(delete all game objects
	for (int i = 0; i < _objects.size(); ++i) {
		delete _objects[i];
	}
	delete _factory;
}

void GameObjectManager::Initialize()
{
	for (int i = 0; i < _objects.size(); ++i) {
		_objects[i]->InitComponents();
	}
}

void GameObjectManager::Update()
{
	for (int i = 0; i < _objects.size(); ++i) {
		_objects[i]->Update();
	}
}

void GameObjectManager::LoadLevel(std::string level)
{
	std::string level_path = "./Levels/" + level + ".json";
	std::cout << "Loading level from " << level_path << std::endl;
	json level_data = JsonHandle::ReadFile(level_path);

	for (json::iterator it = level_data.begin(); it != level_data.end(); ++it) {
		GameObject *new_object = GetObject(it.value()["Type"].get<std::string>());
		_factory->SetObject(new_object, it.value()["Components"]);

		new_object->SetTag(it.key());
		_tagObjects.InsertNode(it.key(), new_object);
	}
}

GameObject * GameObjectManager::GetObject(std::string type)
{
	for (int i = 0; i < _objects.size(); ++i) {
		if (!_objects[i]->_active && _objects[i]->GetType() == type) {
			_objects[i]->_active = true;
			return _objects[i];
		}
	}
	GameObject * object = _factory->CreateObject(type);
	_objects.push_back(object);
	return object;
}
