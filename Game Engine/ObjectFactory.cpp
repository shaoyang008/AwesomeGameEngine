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
	SetObject(object, json({}));
	return object;
}

void ObjectFactory::SetObject(GameObject* object, json level_data)
{
	json data = GetDefaultObjectModel(object->GetType());
	data.merge_patch(level_data);

	for (json::iterator it = data.begin(); it != data.end(); ++it) {
		Component * component = 0;
		if (it.key() == "Transform") {
			component = object->GetComponent(COMPONENT_TYPE::TRANSFORM);
			if (!component) {
				component = new Transform;
			}
		}
		else if (it.key() == "Sprite") {
			component = object->GetComponent(COMPONENT_TYPE::SPRITE);
			if (!component) {
				component = new Sprite;
			}
		}
		else if (it.key() == "Controller") {
			component = object->GetComponent(COMPONENT_TYPE::CONTROLLER);
			if (!component) {
				component = new Controller;
			}
		}
		else if (it.key() == "Patrol") {
			component = object->GetComponent(COMPONENT_TYPE::PATROL);
			if (!component) {
				component = new Patrol;
			}
		}
		else if (it.key() == "RigidBody") {
			component = object->GetComponent(COMPONENT_TYPE::RIGID_BODY);
			if (!component) {
				component = new RigidBody;
			}
		}
		else if (it.key() == "Collider") {
			component = object->GetComponent(COMPONENT_TYPE::COLLIDER);
			if (!component) {
				component = new Collider;
			}
		}
		else if (it.key() == "ResetPlayer") {
			component = object->GetComponent(COMPONENT_TYPE::RESET_PLAYER);
			if (!component) {
				component = new ResetPlayer;
			}
		}
		else if (it.key() == "Model") {
			component = object->GetComponent(COMPONENT_TYPE::MODEL);
			if (!component) {
				component = new Model;
			}
		}
		else if (it.key() == "Camera") {
			component = object->GetComponent(COMPONENT_TYPE::CAMERA);
			if (!component) {
				component = new Camera;
			}
		}
		else if (it.key() == "Animation") {
			component = object->GetComponent(COMPONENT_TYPE::ANIMATION);
			if (!component) {
				component = new Animation;
			}
		}
		else if (it.key() == "Follow") {
			component = object->GetComponent(COMPONENT_TYPE::FOLLOW);
			if (!component) {
				component = new Follow;
			}
		}
		else {
			continue;
		}
		component->Serialize(it.value());
		object->AddComponent(component);
	}
}

json ObjectFactory::GetDefaultObjectModel(std::string type)
{
	if (_objectModels.find(type) == _objectModels.end()) {
		std::string file_path = "./Levels/Types/" + type + ".json";
		_objectModels[type] = JsonHandle::ReadFile(file_path);
	}
	return _objectModels[type];
}
