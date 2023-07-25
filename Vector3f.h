#pragma once
#include <cmath>

class Vector3f {

public:
	Vector3f();
	Vector3f(float x, float y, float z);
	void setPos(float x, float y, float z);
	float& operator[](const int i);
	float operator[](const int i) const;
	Vector3f operator+(const Vector3f& v);
	Vector3f operator-(const Vector3f& v);
	Vector3f operator*(const float s);
	float operator*(const Vector3f& v);
	Vector3f operator/(const float s);
	double dist(const Vector3f& v);

private:
	float pos[3];
};