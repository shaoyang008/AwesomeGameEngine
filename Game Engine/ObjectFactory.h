#pragma once
#include "Components/Base.h"
#include "GameObject.h"
#include "json.hpp"

using json = nlohmann::json;

enum class OBJECT_TYPE {
	IMAGE,
	PLAYER,
	ENEMY_1
};

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();

	GameObject * CreateObject(json);
};

