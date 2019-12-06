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