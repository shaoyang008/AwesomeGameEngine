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

void GameObjectManager::LoadLevel(json level_data)
{
	for (json::iterator it = level_data.begin(); it != level_data.end(); ++it) {
		GameObject * new_object = _tagObjects.FindValueByKey(it.key());
		if (!(new_object && new_object->IsUnique())) {
			new_object = GetObject(it.value()["Type"].get<std::string>());

			// Unique objects should only be set once
			if (it.value().find("Unique") != it.value().end()) {
				new_object->SetUnique();
			}

			new_object->SetTag(it.key());
		}
		_factory->SetObject(new_object, it.value()["Components"]);
	}

	for (int i = 0; i < _objects.size(); ++i) {
		_tagObjects.InsertNode(_objects[i]->GetTag(), _objects[i]);
	}
}

void GameObjectManager::DeactivateObjects()
{
	for (int i = 0; i < _objects.size(); ++i) {
		if (!_objects[i]->IsActive()) {
			_objects[i]->ClearComponents();
		}
	}
}

GameObject * GameObjectManager::GetObject(std::string type)
{
	for (int i = 0; i < _objects.size(); ++i) {
		if (!_objects[i]->IsActive() && _objects[i]->GetType() == type) {
			_factory->SetObject(_objects[i], json({}));
			_objects[i]->Activate();
			return _objects[i];
		}
	}
	GameObject * object = _factory->CreateObject(type);
	_objects.push_back(object);
	return object;
}

