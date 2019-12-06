#pragma once
#include "Component.h"
#include "Transform.h"
#include "../ObjectModel.h"
#include "../ShaderProgram.h"
#include "../Utilities/Matrix4.h"
#include "../Utilities/Shape.h"


class Collider : public Component
{
public:
	enum TYPE {
		STATIC_AABB,
		DYNAMIC_AABB,
		STATIC_SPHERE,
		DYNAMIC_SPHERE,
		count
	};

	Collider();
	~Collider();

	void Update();
	void Serialize(json data);
	void Initialize();

	void Draw(ShaderProgram*);

	float _posX, _posY, _posZ;
	Shape * _shape;

	int GetType() { return _type; }

private:
	int _type;
};