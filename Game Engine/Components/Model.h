/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Model.h
Purpose: 3D model informations
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

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
	void HandleEvent(Event * e);

	// Dummy root objects for storing and drawing all children
	ObjectModel *_modelRoot;

	Material * _defaultMaterial;
	bool  _useMaterial;
};

