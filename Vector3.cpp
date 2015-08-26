#include "Vector3.h"
#include <cmath>

vec3::vec3()
{

}

vec3::vec3(float a_x, float a_y, float a_z) : x(a_x), y(a_y), z(a_z)
{

}

vec3 vec3::operator+(const vec3 &rhs) const
{
	return vec3(x + rhs.x, y + rhs.y, z + rhs.z);
}

vec3 vec3::operator-(const vec3 &rhs) const
{
	return vec3(x - rhs.x, y - rhs.y, z - rhs.z);
}

vec3 vec3::operator/(float rhs) const
{
	return vec3(x / rhs, y / rhs, z / rhs);
}

vec3 vec3::operator*(float rhs) const
{
	return vec3(x * rhs, y * rhs, z * rhs);
}

vec3 vec3::cross(const vec3 &rhs) const
{
	//23 32, 31 13, 12 21
	return vec3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}

float vec3::magnitude() const
{
	return sqrt(x*x + y*y + z*z);
}

vec3 vec3::normal() const
{
	return *this / magnitude();
}

vec3 &vec3::operator=(const vec3 &rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

vec3 &vec3::normalize()		//assignment normal
{
	return *this = normal();
}

vec3 vec3::operator-() const	//return negation of vector
{
	return *this * -1;
}

float vec3::dot(const vec3 &rhs) const
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}

float vec3::angleBetween(const vec3 &rhs) const
{
	//acos(normal().dot(rhs.normal()));

	return acos(dot(rhs) / (magnitude() * rhs.magnitude()));

	//acos(dot(rhs.normal()) / magnitude());
}

vec3 &vec3::operator+=(const vec3 &rhs)
{
	return *this = *this + rhs;
}

vec3 &vec3::operator-=(const vec3 &rhs)
{
	return *this = *this - rhs;
}

vec3 &vec3::operator/=(float &rhs)
{
	return *this = *this / rhs;
}

vec3 &vec3::operator*=(float &rhs)
{
	return *this = *this * rhs;
}

bool vec3::operator==(const vec3 &rhs) const
{
	return x == rhs.x && y == rhs.y && z == rhs.z;
}

bool vec3::operator!=(const vec3 &rhs) const
{
	return x != rhs.x || y != rhs.y || z != rhs.z;

	//return !(*this == rhs);
}

float vec3::distanceBetween(const vec3 &rhs) const
{
	return (*this - rhs).magnitude();
}


vec3 operator*(float lhs, const vec3 &rhs)
{
	return rhs * lhs;
}