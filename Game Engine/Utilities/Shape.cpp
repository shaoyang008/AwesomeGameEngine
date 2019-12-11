/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Shape.cpp
Purpose: Geometrical shapes
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#include "Shape.h"

ObjectModel * Box::UnitBox = 0;
ObjectModel * Sphere::UnitSphere = 0;

Shape::Shape()
{
}


Shape::~Shape()
{
}

Matrix4 Shape::GetScale()
{
	return Matrix4();
}

Box::Box() : _width(0.0f), _length(0.0f), _height(0.0f)
{

}

Box::Box(float w, float l, float h) : _width(w), _length(l), _height(h)
{

}

Box::~Box()
{

}

Matrix4 Box::GetScale()
{
	return Scale(_width, _length, _height);
}

float Box::GetRange(int axis)
{
	float res = 0.0f;
	switch (axis) {
		case 0:
			res = _width;
			break;
		case 1:
			res = _length;
			break;
		case 2:
			res = _height * 2;
			break;
		default:
			break;
	}
	return res / 2;
}

ObjectModel * Box::GetShape()
{
	if (UnitBox == 0) {
		UnitBox = new ObjectModel;
		UnitBox->ReadModel("Resources/Models/box2.obj");
	}
	return UnitBox;
}

Sphere::Sphere() : _radius(0.0f)
{

}

Sphere::Sphere(float r) : _radius(r)
{

}

Sphere::~Sphere()
{

}

Matrix4 Sphere::GetScale()
{
	return Scale(_radius, _radius, _radius);
}

float Sphere::GetRange(int axis)
{
	return _radius;
}

ObjectModel * Sphere::GetShape()
{
	if (UnitSphere == 0) {
		std::cout << "Called!!" << std::endl;
		UnitSphere = new ObjectModel;
		UnitSphere->ReadModel("Resources/Models/sphere2.obj");
	}
	return UnitSphere;
}
