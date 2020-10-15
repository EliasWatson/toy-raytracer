#include "vec3.h"

#include <math.h>

vec3& vec3::operator+=(const vec3& v2) {
	this->x += v2.x;
	this->y += v2.y;
	this->z += v2.z;
	return *this;
}

vec3& vec3::operator-=(const vec3& v2) {
	this->x -= v2.x;
	this->y -= v2.y;
	this->z -= v2.z;
	return *this;
}

vec3& vec3::operator*=(const vec3& v2) {
	this->x *= v2.x;
	this->y *= v2.y;
	this->z *= v2.z;
	return *this;
}

vec3& vec3::operator/=(const vec3& v2) {
	this->x /= v2.x;
	this->y /= v2.y;
	this->z /= v2.z;
	return *this;
}

vec3& vec3::operator*=(const float t) {
	this->x *= t;
	this->y *= t;
	this->z *= t;
	return *this;
}

vec3& vec3::operator/=(const float t) {
	this->x /= t;
	this->y /= t;
	this->z /= t;
	return *this;
}

vec3 operator+(const vec3& v1, const vec3& v2) {
	return vec3(
		v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z
	);
}

vec3 operator-(const vec3& v1, const vec3& v2) {
	return vec3(
		v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z
	);
}

vec3 operator*(const vec3& v1, const vec3& v2) {
	return vec3(
		v1.x * v2.x,
		v1.y * v2.y,
		v1.z * v2.z
	);
}

vec3 operator/(const vec3& v1, const vec3& v2) {
	return vec3(
		v1.x / v2.x,
		v1.y / v2.y,
		v1.z / v2.z
	);
}

vec3 operator*(const vec3& v1, const float n) {
	return vec3(
		v1.x * n,
		v1.y * n,
		v1.z * n
	);
}

vec3 operator*(const float n, const vec3& v1) {
	return vec3(
		v1.x * n,
		v1.y * n,
		v1.z * n
	);
}

vec3 operator/(const vec3& v1, const float n) {
	return vec3(
		v1.x / n,
		v1.y / n,
		v1.z / n
	);
}

float length(const vec3& v) {
	return sqrt(squared_length(v));
}

float squared_length(const vec3& v) {
	return dot(v, v);
}

vec3 normalize(const vec3& v) {
	return v / length(v);
}

float dot(const vec3& v1, const vec3& v2) {
	return (v1.x * v2.x)
		+  (v1.y * v2.y)
		+  (v1.z * v2.z);
}

vec3 cross(const vec3& v1, const vec3& v2) {
	return vec3(
		(v1.y * v2.z) - (v1.z * v2.y),
		(v1.z * v2.x) - (v1.x * v2.z),
		(v1.x * v2.y) - (v1.y * v2.x)
	);
}
