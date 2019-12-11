/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Model.cpp
Purpose: 3D model informations
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#include "Model.h"
#include "../GameStateManager.h"
#include "Transform.h"
#include "../Events/GameOver.h"

extern GameStateManager *pMgr;


Model::Model(): Component(COMPONENT_TYPE::MODEL), _useMaterial(false), _defaultMaterial(new Material)
{

}


Model::~Model()
{
}

void Model::Serialize(json data)
{
	std::string model_path = "Resources/Models/" + data["Filename"].get<std::string>();
	Load(model_path);

	_defaultMaterial->_diffuse.x = data["Diffuse"][0].get<float>();
	_defaultMaterial->_diffuse.y = data["Diffuse"][1].get<float>();
	_defaultMaterial->_diffuse.z = data["Diffuse"][2].get<float>();

	_defaultMaterial->_specular.x = data["Specular"][0].get<float>();
	_defaultMaterial->_specular.y = data["Specular"][1].get<float>();
	_defaultMaterial->_specular.z = data["Specular"][2].get<float>();
	
	_defaultMaterial->_shininess = data["Shininess"].get<float>();

	if (data.find("Texture") != data.end()) {
		std::string texture_path = "Resources/Models/" + data["Texture"].get<std::string>();
		_defaultMaterial->LoadMap(texture_path);
	}

	_useMaterial = data["UseMaterial"].get<int>();
}

bool Model::Load(std::string path)
{
	if (!pMgr->_resourceManager->RegisterModel(path)) {
		std::cout << "Could not load resource: " << path << std::endl;
		return false;
	}
	_modelRoot = pMgr->_resourceManager->GetModelByPath(path);
	return true;
}

void Model::Draw(ShaderProgram * shader)
{
	Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
	
	Matrix4 translate, rotateX, rotateY, rotateZ, scale;
	if (transform) {
		scale = Scale(transform->_scaleX, transform->_scaleY, transform->_scaleZ);
		rotateX = Rotate(0, transform->_rotateX);
		rotateY = Rotate(1, transform->_rotateY);
		rotateZ = Rotate(2, transform->_rotateZ);
		translate = Translate(transform->_translateX, transform->_translateY, transform->_translateZ);
	}
	Matrix4 model_tr = translate * rotateZ * rotateY * rotateX * scale;
	Matrix4 normal_tr;
	model_tr.Inverse(normal_tr);

	GLuint loc;
	loc = glGetUniformLocation(shader->_programId, "ModelTr");
	glUniformMatrix4fv(loc, 1, GL_TRUE, model_tr.Pntr());

	loc = glGetUniformLocation(shader->_programId, "NormalTr");
	glUniformMatrix4fv(loc, 1, GL_TRUE, normal_tr.Pntr());

	loc = glGetUniformLocation(shader->_programId, "useTexture");
	glUniform1i(loc, _useMaterial);

	loc = glGetUniformLocation(shader->_programId, "isPlayer");
	glUniform1i(loc, (_owner->GetTag() == "Player"));

	_defaultMaterial->Use(shader->_programId);
	_modelRoot->DrawChildren(shader->_programId, _useMaterial);
	_defaultMaterial->Unuse();
}

void Model::HandleEvent(Event * e)
{
	if (e->GetType() == EVENT_TYPE::GAME_OVER) {
		GameOver * go = dynamic_cast<GameOver*>(e);
		if (_owner->GetTag() == "Player") {
			if (!go->_victory) {
				_useMaterial = false;
			}
		}
	}
}