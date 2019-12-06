/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Sprite.cpp
Purpose: Sprite of objects
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 10/19/2019

---------------------------------------------------------*/

#include "Sprite.h"
#include "../GameStateManager.h"

extern GameStateManager *pMgr;

Sprite::Sprite(): Component(COMPONENT_TYPE::SPRITE), _texture(0),
_posX(0.0f), _posY(0.0f), _scaleX(1.0f), _scaleY(1.0f)
{
}

Sprite::~Sprite()
{
}

void Sprite::Update()
{

}

void Sprite::Serialize(json data)
{
	if (data.find("Filename") != data.end()) {
		std::string texture_path = "Resources/" + data["Filename"].get<std::string>();
		_texture = new Material;
		_texture->LoadMap(texture_path);
	}

	_posX = data["PositionX"].get<float>();
	_posY = data["PositionY"].get<float>();

	_scaleX = data["ScaleX"].get<float>();
	_scaleY = data["ScaleY"].get<float>();
}

void Sprite::UseSprite(ShaderProgram * shader)
{
	if (_texture) {
		Matrix4 model_tr;
		model_tr = Translate(_posX, _posY, 0.0f) * Scale(_scaleX, _scaleY, 1.0f);

		GLuint loc;
		loc = glGetUniformLocation(shader->_programId, "ModelTr");
		glUniformMatrix4fv(loc, 1, GL_TRUE, model_tr.Pntr());

		_texture->Use(shader->_programId);
	}
}

void Sprite::Unuse()
{
	_texture->Unuse();
}

void Sprite::SetTexture(Material * texture)
{
	_texture = texture;
}
