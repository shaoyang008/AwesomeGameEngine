#pragma once
#include "Component.h"
#include "../Material.h"
#include "Sprite.h"

class SlideShow : public Component
{
public:
	SlideShow();
	~SlideShow();

	void Update();
	void Serialize(json);
	void Initialize();
	void HandleEvent(Event*);

	int _currentSlide, _size;
	std::vector<Material*> _slides;

	Sprite * _ownerSprite;
};

