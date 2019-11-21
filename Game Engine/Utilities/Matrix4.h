#pragma once

#include <vector>
#include <iostream>

#include <glm/glm.hpp>
using namespace glm;

typedef float row4[4];

class Matrix4
{
public:
	Matrix4();
	Matrix4(
		const float &x0, const float &x1, const float &x2, const float &x3,
		const float &y0, const float &y1, const float &y2, const float &y3,
		const float &z0, const float &z1, const float &z2, const float &z3,
		const float &w0, const float &w1, const float &w2, const float &w3
	);
	~Matrix4();

	bool Inverse(Matrix4& output);
	Matrix4 Transpose();
	Matrix4 operator * (const Matrix4& T) const;
	Matrix4 operator * (const float& f) const;
	Matrix4 operator * (const int& f) const;
	Matrix4 operator - (const Matrix4& T) const;
	Matrix4 operator + (const Matrix4& T) const;

	friend std::ostream& operator<<(std::ostream& os, const Matrix4& m);

	// Some indexing operations for the matrix
	row4& operator[](const int i) { return _mat[i]; }
	const row4& operator[](const int i) const { return _mat[i]; }

	// Used to communicate to OpenGL
	float* Pntr() { return &(_mat[0][0]); }

	row4 _mat[4];
};

Matrix4 Rotate(const int i, const float theta);
Matrix4 Scale(const float x, const float y, const float z);
Matrix4 Translate(const float x, const float y, const float z);
Matrix4 Perspective(const float rx, const float ry, const float front, const float back);
Matrix4 LookAt(const vec3 Eye, const vec3 Center, const vec3 Up);