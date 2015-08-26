#pragma once

class vec4
{
public:

	union
	{
		struct { float x, y, z, w; };
		struct { float r, g, b, a; };
		float v[4];
	};

	vec4();
	vec4(float x, float y, float z, float w);

	vec4 operator+(const vec4 &rhs) const;
	vec4 operator-(const vec4 &rhs) const;
	vec4 operator/(float rhs) const;
	vec4 operator*(float rhs) const;

	float magnitude() const;
	vec4 normal() const;
	vec4 &operator=(const vec4 &rhs);
	vec4 &normalize();	//assignment normal
	vec4 operator-() const;

	float dot(const vec4 &rhs) const;
	float angleBetween(const vec4 &rhs) const;

	vec4 &operator+=(const vec4 &rhs);
	vec4 &operator-=(const vec4 &rhs);
	vec4 &operator/=(float &rhs);
	vec4 &operator*=(float &rhs);

	bool operator==(const vec4 &rhs) const;
	bool operator!=(const vec4 &rhs) const;

	float distanceBetween(const vec4 &rhs) const;
};

vec4 operator*(float lhs, const vec4 &rhs);