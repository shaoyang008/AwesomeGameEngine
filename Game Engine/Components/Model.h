#pragma once
#include "Component.h"
#include "../ObjectModel.h"
#include "../Utilities/Matrix4.h"
#include "../ShaderProgram.h"

class Model : public Component
{
public:
	Model();
	~Model();

	void Update() {}
	void Serialize(json);

	bool Load(std::string);
	void Draw(ShaderProgram *);

	ObjectModel *_model;
	float _diffuse[3], _specular[3];
	float _shininess;
};

