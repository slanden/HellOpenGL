#include "Vector4.h"
#include <cmath>

vec4::vec4()
{

}

vec4::vec4(float a_x, float a_y, float a_z, float a_w) : x(a_x), y(a_y), z(a_z), w(a_w)
{

}

vec4 vec4::operator+(const vec4 &rhs) const
{
	return vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

vec4 vec4::operator-(const vec4 &rhs) const
{
	return vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

vec4 vec4::operator/(float rhs) const
{
	return vec4(x / rhs, y / rhs, z / rhs, w / rhs);
}

vec4 vec4::operator*(float rhs) const
{
	return vec4(x * rhs, y * rhs, z * rhs, w * rhs);
}

float vec4::magnitude() const
{
	return sqrt(x*x + y*y + z*z + w*w);
}

vec4 vec4::normal() const
{
	return *this / magnitude();
}

vec4 &vec4::operator=(const vec4 &rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	w = rhs.w;
	return *this;
}

vec4 &vec4::normalize()		//assignment normal
{
	return *this = normal();
}

vec4 vec4::operator-() const	//return negation of vector
{
	return *this * -1;
}

float vec4::dot(const vec4 &rhs) const
{
	return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

float vec4::angleBetween(const vec4 &rhs) const
{
	//acos(normal().dot(rhs.normal()));

	return acos(dot(rhs) / (magnitude() * rhs.magnitude()));

	//acos(dot(rhs.normal()) / magnitude());
}

vec4 &vec4::operator+=(const vec4 &rhs)
{
	return *this = *this + rhs;
}

vec4 &vec4::operator-=(const vec4 &rhs)
{
	return *this = *this - rhs;
}

vec4 &vec4::operator/=(float &rhs)
{
	return *this = *this / rhs;
}

vec4 &vec4::operator*=(float &rhs)
{
	return *this = *this * rhs;
}

bool vec4::operator==(const vec4 &rhs) const
{
	return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
}

bool vec4::operator!=(const vec4 &rhs) const
{
	return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;

	//return !(*this == rhs);
}

float vec4::distanceBetween(const vec4 &rhs) const
{
	return (*this - rhs).magnitude();
}


vec4 operator*(float lhs, const vec4 &rhs)
{
	return rhs * lhs;
}