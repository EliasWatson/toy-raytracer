#ifndef H_VEC3
#define H_VEC3

#include <math.h>

struct vec3 {
	float x, y, z;

	// Constructors
	vec3() : x(0), y(0), z(0) { }
	vec3(float n) : x(n), y(n), z(n) { }
	vec3(float x, float y, float z) : x(x), y(y), z(z) { }

	// Positive and negative operators
	inline const vec3& operator+() const { return *this; }
	inline vec3 operator-() const { return vec3(-x, -y, -z); }

	// Modify operators
	inline vec3& operator+=(const vec3& v2) {
		this->x += v2.x;
		this->y += v2.y;
		this->z += v2.z;
		return *this;
	}

	inline vec3& operator-=(const vec3& v2) {
		this->x -= v2.x;
		this->y -= v2.y;
		this->z -= v2.z;
		return *this;
	}

	inline vec3& operator*=(const vec3& v2) {
		this->x *= v2.x;
		this->y *= v2.y;
		this->z *= v2.z;
		return *this;
	}

	inline vec3& operator/=(const vec3& v2) {
		this->x /= v2.x;
		this->y /= v2.y;
		this->z /= v2.z;
		return *this;
	}

	// Modify by float operators
	inline vec3& operator*=(const float t) {
		this->x *= t;
		this->y *= t;
		this->z *= t;
		return *this;
	}

	inline vec3& operator/=(const float t) {
		this->x /= t;
		this->y /= t;
		this->z /= t;
		return *this;
	}
};

// Vector-Vector operators
inline vec3 operator+(const vec3& v1, const vec3& v2) {
	return vec3(
		v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z
	);
}

inline vec3 operator-(const vec3& v1, const vec3& v2) {
	return vec3(
		v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z
	);
}

inline vec3 operator*(const vec3& v1, const vec3& v2) {
	return vec3(
		v1.x * v2.x,
		v1.y * v2.y,
		v1.z * v2.z
	);
}

inline vec3 operator/(const vec3& v1, const vec3& v2) {
	return vec3(
		v1.x / v2.x,
		v1.y / v2.y,
		v1.z / v2.z
	);
}

// Vector-Scalar operators
inline vec3 operator*(const vec3& v1, const float n) {
	return vec3(
		v1.x * n,
		v1.y * n,
		v1.z * n
	);
}

inline vec3 operator*(const float n, const vec3& v1) {
	return vec3(
		v1.x * n,
		v1.y * n,
		v1.z * n
	);
}

inline vec3 operator/(const vec3& v1, const float n) {
	return vec3(
		v1.x / n,
		v1.y / n,
		v1.z / n
	);
}

// Vector operators
inline float dot(const vec3& v1, const vec3& v2) {
	return (v1.x * v2.x)
		+  (v1.y * v2.y)
		+  (v1.z * v2.z);
}

inline vec3 cross(const vec3& v1, const vec3& v2) {
	return vec3(
		(v1.y * v2.z) - (v1.z * v2.y),
		(v1.z * v2.x) - (v1.x * v2.z),
		(v1.x * v2.y) - (v1.y * v2.x)
	);
}

inline float squared_length(const vec3& v) {
	return dot(v, v);
}

inline float length(const vec3& v) {
	return sqrt(squared_length(v));
}

inline vec3 normalize(const vec3& v) {
	return v / length(v);
}

#endif
