#include "Animation.h"
#include "Model.h"
#include "../GameObject.h"
#include "../GameStateManager.h"
#include "../Events/ToggleAttack.h"

extern GameStateManager *pMgr;

Animation::Animation(): Component(COMPONENT_TYPE::ANIMATION), _original(0), _animation(0)
{
}


Animation::~Animation()
{
}

void Animation::Initialize()
{
	Model * model = dynamic_cast<Model*>(_owner->GetComponent(COMPONENT_TYPE::MODEL));
	_original = model->_modelRoot;
}

void Animation::Update()
{
}

void Animation::Serialize(json data)
{
	std::string path = "Resources/" + data["Filename"].get<std::string>();
	Load(path);
}

bool Animation::Load(std::string path)
{
	if (!pMgr->_resourceManager->RegisterModel(path)) {
		std::cout << "Could not load resource: " << path << std::endl;
		return false;
	}
	_animation = pMgr->_resourceManager->GetModelByPath(path);
	return true;
}

void Animation::HandleEvent(Event * e)
{
	if (e->GetType() == EVENT_TYPE::TOGGLE_ATTACK) {
		ToggleAttack * t = dynamic_cast<ToggleAttack*>(e);
		if (t->_toggle) {
			Model * model = dynamic_cast<Model*>(_owner->GetComponent(COMPONENT_TYPE::MODEL));
			model->_modelRoot = _animation;
		}
		else {
			Model * model = dynamic_cast<Model*>(_owner->GetComponent(COMPONENT_TYPE::MODEL));
			model->_modelRoot = _original;
		}
	}
}
