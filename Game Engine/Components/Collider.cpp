#include "Collider.h"

ObjectModel * Collider::UnitBox = new ObjectModel;

Collider::Collider(): Component(COMPONENT_TYPE::COLLIDER)
{
}

 
Collider::~Collider()
{
}

void Collider::Update()
{
	Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
	_posX = transform->_translateX;
	_posY = transform->_translateY;
	_posZ = transform->_translateZ;
}

void Collider::Serialize(json data)
{
	_height = data["Height"].get<float>();
	_width  = data["Width"].get<float>();
	_length = data["Length"].get<float>();
}

void Collider::Draw(ShaderProgram * shader)
{
	Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));

	Matrix4 translate, scale;
	if (transform) {
		scale = Scale(_width, _length, 2 * _height);
		translate = Translate(transform->_translateX, transform->_translateY, 0);
	}
	Matrix4 model_tr = translate * scale;
	Matrix4 normal_tr;
	model_tr.Inverse(normal_tr);

	GLuint loc;
	loc = glGetUniformLocation(shader->_programId, "ModelTr");
	glUniformMatrix4fv(loc, 1, GL_TRUE, model_tr.Pntr());

	loc = glGetUniformLocation(shader->_programId, "NormalTr");
	glUniformMatrix4fv(loc, 1, GL_TRUE, normal_tr.Pntr());

	loc = glGetUniformLocation(shader->_programId, "useTexture");
	glUniform1i(loc, 1);

	loc = glGetUniformLocation(shader->_programId, "isPlayer");
	glUniform1i(loc, 0);

	UnitBox->DrawChildren(shader->_programId, true);
}

void Collider::InitializeUnitBox()
{
	UnitBox->ReadModel("Resources/box2.obj");
	std::cout << "Unit box initialized " << UnitBox->_children.size() << std::endl;
}
