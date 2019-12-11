/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: SlideShow.h
Purpose: A set of images to display
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

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

