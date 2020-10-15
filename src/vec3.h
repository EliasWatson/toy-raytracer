#ifndef H_VEC3
#define H_VEC3

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
	inline vec3& operator+=(const vec3& v2);
	inline vec3& operator-=(const vec3& v2);
	inline vec3& operator*=(const vec3& v2);
	inline vec3& operator/=(const vec3& v2);

	// Modify by float operators
	inline vec3& operator*=(const float t);
	inline vec3& operator/=(const float t);
};

// Vector-Vector operators
inline vec3 operator+(const vec3& v1, const vec3& v2);
inline vec3 operator-(const vec3& v1, const vec3& v2);
inline vec3 operator*(const vec3& v1, const vec3& v2);
inline vec3 operator/(const vec3& v1, const vec3& v2);

// Vector-Scalar operators
inline vec3 operator*(const vec3& v1, const float n);
inline vec3 operator*(const float n, const vec3& v1);
inline vec3 operator/(const vec3& v1, const float n);

// Vector operators
inline float length(const vec3& v);
inline float squared_length(const vec3& v);
inline vec3 normalize(const vec3& v);

inline float dot(const vec3& v1, const vec3& v2);
inline vec3 cross(const vec3& v1, const vec3& v2);

#endif
