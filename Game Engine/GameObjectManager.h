#pragma once
#include <vector>
#include <fstream>
#include <json.hpp>
#include "GameObject.h"
#include "ObjectFactory.h"
#include "Utilities/Base.h"

using json = nlohmann::json;

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void Update();
	void LoadObject(std::string);
	
	GameObject *  CreateObject(OBJECT_TYPE, std::string);

	std::vector<GameObject*> _objects;
	BinaryTree<std::string, GameObject*> _tagObjects;

private:
	ObjectFactory *_factory;
};
