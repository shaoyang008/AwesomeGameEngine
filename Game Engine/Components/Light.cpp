#include "Light.h"
#include "Camera.h"
#include "../GameObject.h"

Light::Light(): Component(COMPONENT_TYPE::LIGHT), _angle(90.0f)
{
	_lightPos[0] = 0.0;
	_lightPos[1] = 0.0;
	_lightPos[2] = 15.0;
	_light[0] = 3.0;
	_light[1] = 3.0;
	_light[2] = 3.0;
	_ambient[0] = 0.3;
	_ambient[1] = 0.3;
	_ambient[2] = 0.3;
}


Light::~Light()
{
}

void Light::Update()
{
	Camera * camera = dynamic_cast<Camera*>(_owner->GetComponent(COMPONENT_TYPE::CAMERA));
	_lightPos[0] = camera->_targetPosition.x;
	_lightPos[1] = camera->_targetPosition.y;
}

void Light::Serialize(json data)
{
	_ambient[0] = data["Ambient"][0].get<float>();
	_ambient[1] = data["Ambient"][1].get<float>();
	_ambient[2] = data["Ambient"][2].get<float>();

	_light[0] = data["Light"][0].get<float>();
	_light[1] = data["Light"][1].get<float>();
	_light[2] = data["Light"][2].get<float>();

	_lightPos[0] = data["LightPos"][0].get<float>();
	_lightPos[1] = data["LightPos"][1].get<float>();
	_lightPos[2] = data["LightPos"][2].get<float>();

	if (data.find("Angle") != data.end()) {
		_angle = data["Angle"].get<float>();
	}
	else {
		_angle = 90;
	}
}
