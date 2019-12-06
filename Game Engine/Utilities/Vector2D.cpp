/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Vector2D.c
Purpose: Operations to vectors in 2D coordinates.
		 Includes basic operations such as addition, subtraction,
		 scaling, and distance calculation.
Language: C
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_1
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 09/14/2019

---------------------------------------------------------*/

#include "Vector2D.h"

#define EPSILON 0.0001

// ---------------------------------------------------------------------------

void Vector2DZero(Vector2D *pResult)
{
	pResult->x = 0;
	pResult->y = 0;
}

// ---------------------------------------------------------------------------

void Vector2DSet(Vector2D *pResult, float x, float y)
{
	pResult->x = x;
	pResult->y = y;
}

// ---------------------------------------------------------------------------

void Vector2DNeg(Vector2D *pResult, Vector2D *pVec0)
{
	pResult->x = -1 * pVec0->x;
	pResult->y = -1 * pVec0->y;
}

// ---------------------------------------------------------------------------

void Vector2DAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1)
{
	Vector2DSet(pResult, pVec0->x + pVec1->x, pVec0->y + pVec1->y);
}

// ---------------------------------------------------------------------------

void Vector2DSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1)
{
	Vector2DSet(pResult, pVec0->x - pVec1->x, pVec0->y - pVec1->y);
}

// ---------------------------------------------------------------------------

void Vector2DNormalize(Vector2D *pResult, Vector2D *pVec0)
{
	Vector2DScale(pResult, pVec0, 1 / Vector2DLength(pVec0));
}

// ---------------------------------------------------------------------------

void Vector2DScale(Vector2D *pResult, Vector2D *pVec0, float c)
{
	Vector2DSet(pResult, c * pVec0->x, c * pVec0->y);
}

// ---------------------------------------------------------------------------

void Vector2DScaleAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c)
{
	Vector2D _ScaleVec0;
	Vector2D * pScaleVec0 = &_ScaleVec0;
	Vector2DScale(pScaleVec0, pVec0, c);
	Vector2DAdd(pResult, pScaleVec0, pVec1);
}

// ---------------------------------------------------------------------------

void Vector2DScaleSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c)
{
	Vector2D _ScaleVec0;
	Vector2D * pScaleVec0 = &_ScaleVec0;
	Vector2DScale(pScaleVec0, pVec0, c);
	Vector2DSub(pResult, pScaleVec0, pVec1);
}

// ---------------------------------------------------------------------------

float Vector2DLength(Vector2D *pVec0)
{
	return sqrt(Vector2DSquareLength(pVec0));
}

// ---------------------------------------------------------------------------

float Vector2DSquareLength(Vector2D *pVec0)
{
	return pVec0->x * pVec0->x + pVec0->y * pVec0->y;
}

// ---------------------------------------------------------------------------

float Vector2DDistance(Vector2D *pVec0, Vector2D *pVec1)
{
	return sqrt(Vector2DSquareDistance(pVec0, pVec1));
}

// ---------------------------------------------------------------------------

float Vector2DSquareDistance(Vector2D *pVec0, Vector2D *pVec1)
{
	Vector2D _Diff;
	Vector2DSub(&_Diff, pVec0, pVec1);
	return Vector2DSquareLength(&_Diff);
}

// ---------------------------------------------------------------------------

float Vector2DDotProduct(Vector2D *pVec0, Vector2D *pVec1)
{
	return pVec0->x * pVec1->x + pVec0->y * pVec1->y;
}

// ---------------------------------------------------------------------------

void Vector2DFromAngleDeg(Vector2D *pResult, float angle)
{
	float _angleRadius = angle * PI / 180.0;
	Vector2DFromAngleRad(pResult, _angleRadius);
}

// ---------------------------------------------------------------------------

void Vector2DFromAngleRad(Vector2D *pResult, float angle)
{
	Vector2DSet(pResult, cos(angle), sin(angle));
}

// ---------------------------------------------------------------------------
