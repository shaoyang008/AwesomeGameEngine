#include "GameObject.h"

GameObject::GameObject(): _tag(""), _active(false)
{

}

GameObject::GameObject(std::string tag): _tag(tag),  _active(false)
{

}

GameObject::~GameObject()
{
	for (int i = 0; i < _components.size(); ++i) {
		delete _components[i];
	}
}

void GameObject::Update() {
	for (int i = 0; i < _components.size(); ++i) {
		if (_components[i]) _components[i]->Update();
	}
}

Component * GameObject::GetComponent(COMPONENT_TYPE type) {
	for (int i = 0; i < _components.size(); ++i) {
		if (_components[i]->GetType() == type) return _components[i];
	}
	return 0;
}

bool GameObject::AddComponent(Component * c) {
	for (int i = 0; i < _components.size(); ++i) {
		if (_components[i]->GetType() == c->GetType()) return false;
	}
	c->pOwner = this;
	_components.push_back(c);
	return true;
}