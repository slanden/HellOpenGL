#pragma once

class vec3
{
public:

	union
	{
		struct { float x, y, z; };
		struct { float r, g, b; };
		float v[3];
	};

	vec3();
	vec3(float x, float y, float z);

	vec3 operator+(const vec3 &rhs) const;
	vec3 operator-(const vec3 &rhs) const;
	vec3 operator/(float rhs) const;
	vec3 operator*(float rhs) const;
	vec3 cross(const vec3 &rhs) const;

	float magnitude() const;
	vec3 normal() const;
	vec3 &operator=(const vec3 &rhs);
	vec3 &normalize();	//assignment normal
	vec3 operator-() const;

	float dot(const vec3 &rhs) const;
	float angleBetween(const vec3 &rhs) const;

	vec3 &operator+=(const vec3 &rhs);
	vec3 &operator-=(const vec3 &rhs);
	vec3 &operator/=(float &rhs);
	vec3 &operator*=(float &rhs);

	bool operator==(const vec3 &rhs) const;
	bool operator!=(const vec3 &rhs) const;

	float distanceBetween(const vec3 &rhs) const;
};

vec3 operator*(float lhs, const vec3 &rhs);