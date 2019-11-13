/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: ObjectFactory.h
Purpose: Creates objects depend on input data
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/26/2019

---------------------------------------------------------*/

#include "ObjectFactory.h"

ObjectFactory::ObjectFactory()
{
}

ObjectFactory::~ObjectFactory()
{
}

GameObject * ObjectFactory::CreateObject(std::string type)
{
	GameObject * object = new GameObject(type);
	SetObject(object, json());
	return object;
}

void ObjectFactory::SetObject(GameObject* object, json level_data)
{
	object->ClearComponents();
	json data = GetDefaultObjectModel(object->GetType());
	
	std::cout << level_data << std::endl;
	std::cout << data << std::endl;
	data.merge_patch(level_data);
	std::cout << data << std::endl;

	for (json::iterator it = data.begin(); it != data.end(); ++it) {
		Component * component = 0;
		if (it.key() == "Transform") {
			std::cout << "Adding " << it.key() << std::endl;
			Transform * tComponent = new Transform;
			tComponent->Serialize(it.value());
			component = tComponent;
		}
		else if (it.key() == "Sprite") {
			std::cout << "Adding " << it.key() << std::endl;
			Sprite * sComponent = new Sprite;
			sComponent->Serialize(it.value());
			component = sComponent;
		}
		else if (it.key() == "Controller") {
			std::cout << "Adding " << it.key() << std::endl;
			Controller * cComponent = new Controller;
			cComponent->Serialize(it.value());
			component = cComponent;
		}
		else if (it.key() == "Patrol") {
			std::cout << "Adding " << it.key() << std::endl;
			Patrol * pComponent = new Patrol;
			pComponent->Serialize(it.value());
			component = pComponent;
		}
		else if (it.key() == "RigidBody") {
			std::cout << "Adding " << it.key() << std::endl;
			RigidBody * rComponent = new RigidBody;
			rComponent->Serialize(it.value());
			component = rComponent;
		}
		if (component) { object->AddComponent(component); }
	}
}

json ObjectFactory::GetDefaultObjectModel(std::string type)
{
	if (_objectModels.find(type) == _objectModels.end()) {
		_objectModels[type] = ReadFile(type);
	}
	return _objectModels[type];
}

json ObjectFactory::ReadFile(std::string type)
{
	std::string file_path = "./Levels/Types/" + type + ".txt";

	std::ifstream file;
	file.open(file_path);

	json file_data;
	file >> file_data;

	file.close();
	return file_data;
}