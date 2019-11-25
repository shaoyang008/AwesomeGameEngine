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

	// Dummy root objects for storing and drawing all children
	ObjectModel *_modelRoot;

	Material * _defaultMaterial;
	bool  _useMaterial;
};

