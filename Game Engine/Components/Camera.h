#pragma once
#include "Component.h"
#include <string>

#include "glm/glm.hpp"
using namespace glm;

class Camera : public Component
{
public:
	Camera();
	~Camera();

	void Update();
	void Serialize(json);
	void Initialize();

	float _ry;
	float _front, _back;
	float _tile, _spin;

	vec3 _position;

	std::string _targetTag;
	GameObject * _target;
	vec3 _targetPosition;

};

