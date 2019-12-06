#include "Collider.h"

Collider::Collider(): Component(COMPONENT_TYPE::COLLIDER), _type(TYPE::STATIC_AABB),
_posX(0.0f), _posY(0.0f), _posZ(0.0f)
{
}

 
Collider::~Collider()
{
	delete _shape;
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
	std::string shape = data["Type"].get<std::string>();

	if (shape == "StaticAABB") {
		_type = TYPE::STATIC_AABB;
		_shape = new Box(data["Width"].get<float>(), data["Length"].get<float>(), data["Height"].get<float>());
	}
	else if (shape == "DynamicAABB") {
		_type = TYPE::DYNAMIC_AABB;
		_shape = new Box(data["Width"].get<float>(), data["Length"].get<float>(), data["Height"].get<float>());
	}
	else if (shape == "StaticSphere") {
		_type = TYPE::STATIC_SPHERE;
		_shape = new Sphere(data["Radius"].get<float>());
	}
	else if (shape == "DynamicSphere") {
		_type = TYPE::DYNAMIC_SPHERE;
		_shape = new Sphere(data["Radius"].get<float>());
	}
}

void Collider::Initialize()
{

}

void Collider::Draw(ShaderProgram * shader)
{
	Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));

	Matrix4 translate, scale;
	if (transform) {
		scale = _shape->GetScale();
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

	// UnitBox->DrawChildren(shader->_programId, true);
	_shape->GetShape()->DrawChildren(shader->_programId, true);
}

