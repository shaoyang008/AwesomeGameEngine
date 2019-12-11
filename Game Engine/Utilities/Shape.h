/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Shape.h
Purpose: Geometrical shapes
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#pragma once
#include "Matrix4.h"
#include "../ObjectModel.h"

class Shape
{
public:
	Shape();
	~Shape();

	virtual Matrix4 GetScale();

	// 0: x, 1: y, 2: z
	virtual float GetRange(int) = 0;
	virtual ObjectModel* GetShape() = 0;
};

class Box : public Shape
{
public:
	Box();
	Box(float, float, float);
	~Box();

	Matrix4 GetScale();
	float GetRange(int);
	ObjectModel* GetShape();

	float _width, _length, _height;

private:
	static ObjectModel * UnitBox;
};

class Sphere : public Shape
{
public:
	Sphere();
	Sphere(float);
	~Sphere();

	Matrix4 GetScale();
	float GetRange(int);
	ObjectModel* GetShape();

	float _radius;

private:
	static ObjectModel * UnitSphere;
};