#pragma once
#include "Component.h"

class Projectile : public Component
{
public:
	Projectile();
	~Projectile();

	void Update();
	void Serialize(json);
	void Initialize();
	void HandleEvent(Event *);

	void SetShooter(std::string);

	GameObject * _shooter;
	int _lifetime;
};

