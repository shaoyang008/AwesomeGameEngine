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
}

void GameObjectManager::Update()
{
	for (int i = 0; i < _objects.size(); ++i) {
		_objects[i]->Update();
	}
}

void GameObjectManager::LoadLevel(std::string level)
{
	std::string level_path = "./Levels/" + level + ".txt";
	json level_data = ReadFile(level_path);

	for (json::iterator it = level_data.begin(); it != level_data.end(); ++it) {
		std::string model_type = it.value()["Type"];
		std::cout << "Creating " << model_type << std::endl;
		GameObject *new_object = CreateObject(model_type, it.value()["Components"]);

		_objects.push_back(new_object);
		_tagObjects.InsertNode(it.key(), new_object);
	}
}

// Creates an object with level parameters
GameObject * GameObjectManager::CreateObject(std::string model, json level_data)
{
	std::string model_path = "./Levels/Models/" + model + ".txt";
	json model_data = ReadFile(model_path);
	model_data.merge_patch(level_data);

	return _factory->CreateObject(model_data);
}

json GameObjectManager::ReadFile(std::string file_path)
{
	std::ifstream file;
	file.open(file_path);

	json file_data;
	file >> file_data;

	file.close();
	return file_data;
}
