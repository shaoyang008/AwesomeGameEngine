#include "Matrix4.h"



Matrix4::Matrix4()
{
	_mat[0][0] = 1;
	_mat[0][1] = 0;
	_mat[0][2] = 0;
	_mat[0][3] = 0;
	_mat[1][0] = 0;
	_mat[1][1] = 1;
	_mat[1][2] = 0;
	_mat[1][3] = 0;
	_mat[2][0] = 0;
	_mat[2][1] = 0;
	_mat[2][2] = 1;
	_mat[2][3] = 0;
	_mat[3][0] = 0;
	_mat[3][1] = 0;
	_mat[3][2] = 0;
	_mat[3][3] = 1;
}

Matrix4::Matrix4(
	const float &x0, const float &x1, const float &x2, const float &x3,
	const float &y0, const float &y1, const float &y2, const float &y3,
	const float &z0, const float &z1, const float &z2, const float &z3,
	const float &w0, const float &w1, const float &w2, const float &w3)
{
	_mat[0][0] = x0;
	_mat[0][1] = x1;
	_mat[0][2] = x2;
	_mat[0][3] = x3;
	_mat[1][0] = y0;
	_mat[1][1] = y1;
	_mat[1][2] = y2;
	_mat[1][3] = y3;
	_mat[2][0] = z0;
	_mat[2][1] = z1;
	_mat[2][2] = z2;
	_mat[2][3] = z3;
	_mat[3][0] = w0;
	_mat[3][1] = w1;
	_mat[3][2] = w2;
	_mat[3][3] = w3;
}


Matrix4::~Matrix4()
{
}

Matrix4 Matrix4::Transpose()
{
	Matrix4 trans;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			trans._mat[i][j] = _mat[j][i];
		}
	}
	return trans;
}

Matrix4 Matrix4::operator* (const Matrix4& T) const
{
	Matrix4 ans;
	ans._mat[0][0] = _mat[0][0] * T._mat[0][0] + _mat[0][1] * T._mat[1][0] + _mat[0][2] * T._mat[2][0] + _mat[0][3] * T._mat[3][0];
	ans._mat[0][1] = _mat[0][0] * T._mat[0][1] + _mat[0][1] * T._mat[1][1] + _mat[0][2] * T._mat[2][1] + _mat[0][3] * T._mat[3][1];
	ans._mat[0][2] = _mat[0][0] * T._mat[0][2] + _mat[0][1] * T._mat[1][2] + _mat[0][2] * T._mat[2][2] + _mat[0][3] * T._mat[3][2];
	ans._mat[0][3] = _mat[0][0] * T._mat[0][3] + _mat[0][1] * T._mat[1][3] + _mat[0][2] * T._mat[2][3] + _mat[0][3] * T._mat[3][3];
	ans._mat[1][0] = _mat[1][0] * T._mat[0][0] + _mat[1][1] * T._mat[1][0] + _mat[1][2] * T._mat[2][0] + _mat[1][3] * T._mat[3][0];
	ans._mat[1][1] = _mat[1][0] * T._mat[0][1] + _mat[1][1] * T._mat[1][1] + _mat[1][2] * T._mat[2][1] + _mat[1][3] * T._mat[3][1];
	ans._mat[1][2] = _mat[1][0] * T._mat[0][2] + _mat[1][1] * T._mat[1][2] + _mat[1][2] * T._mat[2][2] + _mat[1][3] * T._mat[3][2];
	ans._mat[1][3] = _mat[1][0] * T._mat[0][3] + _mat[1][1] * T._mat[1][3] + _mat[1][2] * T._mat[2][3] + _mat[1][3] * T._mat[3][3];
	ans._mat[2][0] = _mat[2][0] * T._mat[0][0] + _mat[2][1] * T._mat[1][0] + _mat[2][2] * T._mat[2][0] + _mat[2][3] * T._mat[3][0];
	ans._mat[2][1] = _mat[2][0] * T._mat[0][1] + _mat[2][1] * T._mat[1][1] + _mat[2][2] * T._mat[2][1] + _mat[2][3] * T._mat[3][1];
	ans._mat[2][2] = _mat[2][0] * T._mat[0][2] + _mat[2][1] * T._mat[1][2] + _mat[2][2] * T._mat[2][2] + _mat[2][3] * T._mat[3][2];
	ans._mat[2][3] = _mat[2][0] * T._mat[0][3] + _mat[2][1] * T._mat[1][3] + _mat[2][2] * T._mat[2][3] + _mat[2][3] * T._mat[3][3];
	ans._mat[3][0] = _mat[3][0] * T._mat[0][0] + _mat[3][1] * T._mat[1][0] + _mat[3][2] * T._mat[2][0] + _mat[3][3] * T._mat[3][0];
	ans._mat[3][1] = _mat[3][0] * T._mat[0][1] + _mat[3][1] * T._mat[1][1] + _mat[3][2] * T._mat[2][1] + _mat[3][3] * T._mat[3][1];
	ans._mat[3][2] = _mat[3][0] * T._mat[0][2] + _mat[3][1] * T._mat[1][2] + _mat[3][2] * T._mat[2][2] + _mat[3][3] * T._mat[3][2];
	ans._mat[3][3] = _mat[3][0] * T._mat[0][3] + _mat[3][1] * T._mat[1][3] + _mat[3][2] * T._mat[2][3] + _mat[3][3] * T._mat[3][3];
	return ans;
}

Matrix4 Matrix4::operator* (const float& f) const
{
	Matrix4 ans(f, 0, 0, 0, 0, f, 0, 0, 0, 0, f, 0, 0, 0, 0, f);
	return *this * ans;
}

Matrix4 Matrix4::operator* (const int& i) const
{
	Matrix4 ans(i, 0, 0, 0, 0, i, 0, 0, 0, 0, i, 0, 0, 0, 0, i);
	return *this * ans;
}

Matrix4 Matrix4::operator + (const Matrix4& T) const
{
	Matrix4 ans;
	ans._mat[0][0] = _mat[0][0] + T._mat[0][0];
	ans._mat[0][1] = _mat[0][1] + T._mat[0][1];
	ans._mat[0][2] = _mat[0][2] + T._mat[0][2];
	ans._mat[0][3] = _mat[0][3] + T._mat[0][3];
	ans._mat[1][0] = _mat[1][0] + T._mat[1][0];
	ans._mat[1][1] = _mat[1][1] + T._mat[1][1];
	ans._mat[1][2] = _mat[1][2] + T._mat[1][2];
	ans._mat[1][3] = _mat[1][3] + T._mat[1][3];
	ans._mat[2][0] = _mat[2][0] + T._mat[2][0];
	ans._mat[2][1] = _mat[2][1] + T._mat[2][1];
	ans._mat[2][2] = _mat[2][2] + T._mat[2][2];
	ans._mat[2][3] = _mat[2][3] + T._mat[2][3];
	ans._mat[3][0] = _mat[3][0] + T._mat[3][0];
	ans._mat[3][1] = _mat[3][1] + T._mat[3][1];
	ans._mat[3][2] = _mat[3][2] + T._mat[3][2];
	ans._mat[3][3] = _mat[3][3] + T._mat[3][3];
	return ans;
}

Matrix4 Matrix4::operator - (const Matrix4& T) const
{
	return *this + (T * -1);
}

std::ostream& operator<<(std::ostream& os, const Matrix4& m)
{
	std::cout << '[' << m._mat[0][0] << ", " << m._mat[0][1] << ", " << m._mat[0][2] << ", " << m._mat[0][3] << ']' << std::endl;
	std::cout << '[' << m._mat[1][0] << ", " << m._mat[1][1] << ", " << m._mat[1][2] << ", " << m._mat[1][3] << ']' << std::endl;
	std::cout << '[' << m._mat[2][0] << ", " << m._mat[2][1] << ", " << m._mat[2][2] << ", " << m._mat[2][3] << ']' << std::endl;
	std::cout << '[' << m._mat[3][0] << ", " << m._mat[3][1] << ", " << m._mat[3][2] << ", " << m._mat[3][3] << ']' << std::endl;
	return os;
}

const float pi = 3.14159f;
Matrix4 Rotate(const int i, const float theta)
{
	Matrix4 R;
	float _thetaRad = theta * pi / 180;
	int a = (i + 1) % 3;
	int b = (i + 2) % 3;

	R[a][a] = cos(_thetaRad);
	R[a][b] = -1 * sin(_thetaRad);
	R[b][a] = sin(_thetaRad);
	R[b][b] = cos(_thetaRad);

	return R;
}

// Return a scale matrix
Matrix4 Scale(const float x, const float y, const float z)
{
	Matrix4 S;
	S[0][0] = x;
	S[1][1] = y;
	S[2][2] = z;
	return S;
}

// Return a translation matrix
Matrix4 Translate(const float x, const float y, const float z)
{
	Matrix4 T;
	T[0][3] = x;
	T[1][3] = y;
	T[2][3] = z;
	return T;
}

Matrix4 Perspective(const float rx, const float ry, const float front, const float back)
{
	Matrix4 P;
	P[0][0] = 1.0 / rx;
	P[1][1] = 1.0 / ry;
	P[2][2] = -1 * (back + front) / (back - front);
	P[2][3] = -2 * back * front / (back - front);
	P[3][2] = -1;
	P[3][3] = 0;
	return P;
}

Matrix4 LookAt(const vec3 Eye, const vec3 Center, const vec3 Up)
{
	vec3 u = normalize(Center - Eye);
	vec3 v = normalize(cross(u, Up));
	vec3 w = normalize(cross(v, u));

	Matrix4 T = Translate(-1 * Eye.x, -1 * Eye.y, -1 * Eye.z);
	Matrix4 R;
	R[0][0] = v.x;
	R[0][1] = v.y;
	R[0][2] = v.z;
	R[1][0] = w.x;
	R[1][1] = w.y;
	R[1][2] = w.z;
	R[2][0] = u.x * -1;
	R[2][1] = u.y * -1;
	R[2][2] = u.z * -1;

	return R * T;
}


bool Matrix4::Inverse(Matrix4& output)
{
	float inv[16], m[16], det;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[4 * i + j] = _mat[j][i];
		}
	}

	inv[0] = m[5] * m[10] * m[15] -
		m[5] * m[11] * m[14] -
		m[9] * m[6] * m[15] +
		m[9] * m[7] * m[14] +
		m[13] * m[6] * m[11] -
		m[13] * m[7] * m[10];

	inv[4] = -m[4] * m[10] * m[15] +
		m[4] * m[11] * m[14] +
		m[8] * m[6] * m[15] -
		m[8] * m[7] * m[14] -
		m[12] * m[6] * m[11] +
		m[12] * m[7] * m[10];

	inv[8] = m[4] * m[9] * m[15] -
		m[4] * m[11] * m[13] -
		m[8] * m[5] * m[15] +
		m[8] * m[7] * m[13] +
		m[12] * m[5] * m[11] -
		m[12] * m[7] * m[9];

	inv[12] = -m[4] * m[9] * m[14] +
		m[4] * m[10] * m[13] +
		m[8] * m[5] * m[14] -
		m[8] * m[6] * m[13] -
		m[12] * m[5] * m[10] +
		m[12] * m[6] * m[9];

	inv[1] = -m[1] * m[10] * m[15] +
		m[1] * m[11] * m[14] +
		m[9] * m[2] * m[15] -
		m[9] * m[3] * m[14] -
		m[13] * m[2] * m[11] +
		m[13] * m[3] * m[10];

	inv[5] = m[0] * m[10] * m[15] -
		m[0] * m[11] * m[14] -
		m[8] * m[2] * m[15] +
		m[8] * m[3] * m[14] +
		m[12] * m[2] * m[11] -
		m[12] * m[3] * m[10];

	inv[9] = -m[0] * m[9] * m[15] +
		m[0] * m[11] * m[13] +
		m[8] * m[1] * m[15] -
		m[8] * m[3] * m[13] -
		m[12] * m[1] * m[11] +
		m[12] * m[3] * m[9];

	inv[13] = m[0] * m[9] * m[14] -
		m[0] * m[10] * m[13] -
		m[8] * m[1] * m[14] +
		m[8] * m[2] * m[13] +
		m[12] * m[1] * m[10] -
		m[12] * m[2] * m[9];

	inv[2] = m[1] * m[6] * m[15] -
		m[1] * m[7] * m[14] -
		m[5] * m[2] * m[15] +
		m[5] * m[3] * m[14] +
		m[13] * m[2] * m[7] -
		m[13] * m[3] * m[6];

	inv[6] = -m[0] * m[6] * m[15] +
		m[0] * m[7] * m[14] +
		m[4] * m[2] * m[15] -
		m[4] * m[3] * m[14] -
		m[12] * m[2] * m[7] +
		m[12] * m[3] * m[6];

	inv[10] = m[0] * m[5] * m[15] -
		m[0] * m[7] * m[13] -
		m[4] * m[1] * m[15] +
		m[4] * m[3] * m[13] +
		m[12] * m[1] * m[7] -
		m[12] * m[3] * m[5];

	inv[14] = -m[0] * m[5] * m[14] +
		m[0] * m[6] * m[13] +
		m[4] * m[1] * m[14] -
		m[4] * m[2] * m[13] -
		m[12] * m[1] * m[6] +
		m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] +
		m[1] * m[7] * m[10] +
		m[5] * m[2] * m[11] -
		m[5] * m[3] * m[10] -
		m[9] * m[2] * m[7] +
		m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] -
		m[0] * m[7] * m[10] -
		m[4] * m[2] * m[11] +
		m[4] * m[3] * m[10] +
		m[8] * m[2] * m[7] -
		m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] +
		m[0] * m[7] * m[9] +
		m[4] * m[1] * m[11] -
		m[4] * m[3] * m[9] -
		m[8] * m[1] * m[7] +
		m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] -
		m[0] * m[6] * m[9] -
		m[4] * m[1] * m[10] +
		m[4] * m[2] * m[9] +
		m[8] * m[1] * m[6] -
		m[8] * m[2] * m[5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	if (det == 0) return false;

	det = 1.0 / det;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			output._mat[j][i] = inv[4 * i + j] * det;
		}
	}
	return true;
}

