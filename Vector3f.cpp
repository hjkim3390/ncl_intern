#include "Vector3f.h"

Vector3f::Vector3f()
{
	pos[0] = pos[1] = pos[2] = 0.0f;
}

Vector3f::Vector3f(float x, float y, float z)
{
	pos[0] = x; pos[1] = y; pos[2] = z;
}

void Vector3f::setPos(float x, float y, float z)
{
	pos[0] = x; pos[1] = y; pos[2] = z;
}

float& Vector3f::operator[](const int i)
{
	return pos[i];
}

float Vector3f::operator[](const int i) const
{
	return pos[i];
}

Vector3f Vector3f::operator+(const Vector3f& v)
{
	return Vector3f(pos[0] + v[0], pos[1] + v[1], pos[2] + v[2]);
}

Vector3f Vector3f::operator-(const Vector3f& v)
{
	return Vector3f(pos[0] - v[0], pos[1] - v[1], pos[2] - v[2]);
}

Vector3f Vector3f::operator*(const float s)
{
	return Vector3f(pos[0] * s, pos[1] * s, pos[2] * s);
}

float Vector3f::operator*(const Vector3f& v)
{
	return float(pos[0] * v.pos[0] + pos[1] * v.pos[1] + pos[2] * v.pos[2]);
}

Vector3f Vector3f::operator/(const float s)
{
	return Vector3f(pos[0] / s, pos[1] / s, pos[2] / s);
}

float Vector3f::dist(const Vector3f& v)
{
	float dx = v.pos[0] - pos[0];
	float dy = v.pos[1] - pos[1];
	float dz = v.pos[2] - pos[2];

	return sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
}
