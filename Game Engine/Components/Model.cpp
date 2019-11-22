#include "Model.h"
#include "../GameStateManager.h"
#include "Transform.h"

extern GameStateManager *pMgr;


Model::Model(): Component(COMPONENT_TYPE::MODEL), _useMaterial(false)
{
	_diffuse[0] = 0.8;
	_diffuse[1] = 0.5;
	_diffuse[2] = 0.2;
	_specular[0] = 0.4;
	_specular[1] = 0.4;
	_specular[2] = 0.4;
}


Model::~Model()
{
}

void Model::Serialize(json data)
{
	std::string path = "Resources/" + data["Filename"].get<std::string>();
	Load(path);

	_diffuse[0] = data["Diffuse"][0].get<float>();
	_diffuse[1] = data["Diffuse"][1].get<float>();
	_diffuse[2] = data["Diffuse"][2].get<float>();

	_specular[0] = data["Specular"][0].get<float>();
	_specular[1] = data["Specular"][1].get<float>();
	_specular[2] = data["Specular"][2].get<float>();

	_shininess = data["Shininess"].get<float>();

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
	Matrix4 model_tr = translate * rotateY * rotateX * rotateZ * scale;
	Matrix4 normal_tr;
	model_tr.Inverse(normal_tr);

	GLuint loc;
	loc = glGetUniformLocation(shader->_programId, "ModelTr");
	glUniformMatrix4fv(loc, 1, GL_TRUE, model_tr.Pntr());

	loc = glGetUniformLocation(shader->_programId, "NormalTr");
	glUniformMatrix4fv(loc, 1, GL_TRUE, normal_tr.Pntr());

	loc = glGetUniformLocation(shader->_programId, "diffuse");
	glUniform3fv(loc, 1, &_diffuse[0]);

	loc = glGetUniformLocation(shader->_programId, "specular");
	glUniform3fv(loc, 1, &_specular[0]);

	loc = glGetUniformLocation(shader->_programId, "shininess");
	glUniform1f(loc, _shininess);

	loc = glGetUniformLocation(shader->_programId, "useTexture");
	glUniform1i(loc, _useMaterial);

	loc = glGetUniformLocation(shader->_programId, "isPlayer");
	glUniform1i(loc, (_owner->GetTag() == "Player"));

	_modelRoot->DrawChildren(shader->_programId, _useMaterial);
}
