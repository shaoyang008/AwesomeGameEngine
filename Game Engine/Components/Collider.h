#pragma once
#include "Component.h"
#include "Transform.h"
#include "../ObjectModel.h"
#include "../ShaderProgram.h"
#include "../Utilities/Matrix4.h"

enum class COLLIDER_TYPE {
	STATIC_AABB,
	DYNAMIC_AABB,
	STATIC_CIRCLE,
	DYNAMIC_CIRCLE,
	count
};

class Collider : public Component
{
public:
	Collider();
	~Collider();

	void Update();
	void Serialize(json data);

	void Draw(ShaderProgram*);

	// Box colliders
	float _posX, _posY, _posZ;
	float _width, _length, _height;

	static void InitializeUnitBox();

private:
	static ObjectModel * UnitBox;
};

