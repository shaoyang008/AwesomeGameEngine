#pragma once
#include "Component.h"

class EnemyAI : public Component
{
public:
	EnemyAI();
	~EnemyAI();

	void Update();
	void Serialize(json);
	void Initialize();
	void HandleEvent(Event*);

	void Reborn();

private:
	int _state;
	GameObject * _target;
	float _targetX, _targetY;

	int _size, _atkState;
	float *_speeds;
	float *_endpoints;

	int _atkFrames;
};

