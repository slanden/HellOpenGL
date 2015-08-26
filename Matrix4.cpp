#include "Matrix4.h"
#include <cmath>
#include <cstring>


Matrix4::Matrix4()
{

}

Matrix4::Matrix4(const vec4 &col1, const vec4 &col2, const vec4 &col3, const vec4 &col4)
	:v1(col1), v2(col2), v3(col3), v4(col4)
{}

Matrix4::Matrix4(const vec4 cols[4])
	: v1(cols[0]), v2(cols[1]), v3(cols[2]), v4(cols[3])
{}
Matrix4::Matrix4(const float mm[4][4])
{
	memcpy(this->mm, mm, 16 * 4);
}
Matrix4::Matrix4(const float m[16])
{
	memcpy(this->m, m, 16 * 4);
}

Matrix4::Matrix4(float m11, float m12, float m13, float m14,
				 float m21, float m22, float m23, float m24,
				 float m31, float m32, float m33, float m34,
				 float m41, float m42, float m43, float m44)
				 : m11(m11), m12(m12), m13(m13), m14(m14),
				   m21(m21), m22(m22), m23(m23), m24(m24),
				   m31(m31), m32(m32), m33(m33), m34(m34),
				   m41(m41), m42(m42), m43(m43), m44(m44)
{

}

//builds and returns a new identity matrix
Matrix4 Matrix4::Mat4MakeIdentity()
{
	const Matrix4 id(1, 0, 0, 0,
					 0, 1, 0, 0,
					 0, 0, 1, 0,
					 0, 0, 0, 1);
	return id;
}
//transposes matrix and returns *this
Matrix4 Matrix4::GetTranspose() const
{
	return Matrix4(m11, m21, m31, m41,
				   m12, m22, m32, m42,
				   m13, m23, m33, m43,
				   m14, m24, m34, m44);
}

Matrix4 &Matrix4::Transpose()
{
	return *this = GetTranspose();
}

Matrix4 Matrix4::MakeRotation(float angle)
{
	Matrix4 r = { cos(angle), sin(angle), 0, 0,
				 -sin(angle), cos(angle), 0, 0,
						   0,		   0, 1, 0,
						   0,		   0, 0, 1 };
	return r;
}

Matrix4 Matrix4::MakeTranslation(vec3 pos)
{
	Matrix4 r = Matrix4::Mat4MakeIdentity();

	r.v4.x = pos.x;
	r.v4.y = pos.y;
	r.v4.z = pos.z;

	return r;
}

Matrix4 Matrix4::operator +(const Matrix4& a_rhs) const
{
	return Matrix4(v1 + a_rhs.v1, v2 + a_rhs.v2, v3 + a_rhs.v3, v4 + a_rhs.v4);
}
Matrix4 Matrix4::operator -(const Matrix4& a_rhs) const
{
	return Matrix4(v1 - a_rhs.v1, v2 - a_rhs.v2, v3 - a_rhs.v3, v4 - a_rhs.v4);
}
Matrix4 Matrix4::operator *(const Matrix4& a_r) const
{
	return Matrix4( m11 * a_r.m11 + m12 * a_r.m21 + m13 * a_r.m31 + m14 * a_r.m41,
					m11 * a_r.m12 + m12 * a_r.m22 + m13 * a_r.m32 + m14 * a_r.m42,
					m11 * a_r.m13 + m12 * a_r.m23 + m13 * a_r.m33 + m14 * a_r.m43,
					m11 * a_r.m14 + m12 * a_r.m24 + m13 * a_r.m34 + m14 * a_r.m44,

					m21 * a_r.m11 + m22 * a_r.m21 + m23 * a_r.m31 + m24 * a_r.m41,
					m21 * a_r.m12 + m22 * a_r.m22 + m23 * a_r.m32 + m24 * a_r.m42,
					m21 * a_r.m13 + m22 * a_r.m23 + m23 * a_r.m33 + m24 * a_r.m43,
					m21 * a_r.m14 + m22 * a_r.m24 + m23 * a_r.m34 + m24 * a_r.m44,

					m31 * a_r.m11 + m32 * a_r.m21 + m33 * a_r.m31 + m34 * a_r.m41,
					m31 * a_r.m12 + m32 * a_r.m22 + m33 * a_r.m32 + m34 * a_r.m42,
					m31 * a_r.m13 + m32 * a_r.m23 + m33 * a_r.m33 + m34 * a_r.m43,
					m31 * a_r.m14 + m32 * a_r.m24 + m33 * a_r.m34 + m34 * a_r.m44,

					m41 * a_r.m11 + m42 * a_r.m21 + m43 * a_r.m31 + m44 * a_r.m41,
					m41 * a_r.m12 + m42 * a_r.m22 + m43 * a_r.m32 + m44 * a_r.m42,
					m41 * a_r.m13 + m42 * a_r.m23 + m43 * a_r.m33 + m44 * a_r.m43,
					m41 * a_r.m14 + m42 * a_r.m24 + m43 * a_r.m34 + m44 * a_r.m44);
}

/*

a, b, c, d,		  11, 12, 13, 14,
e, f, g, h,		  21, 22, 23, 24,
i, j, k, l,		  31, 32, 33, 34,
m, n, o, p		  41, 42, 43, 44

a * r.a + b * r.e + c * r.i + d * r.m,
a * r.b + b * r.f + c * r.j + d * r.n,
a * r.c + b * r.g + c * r.k + d * r.o,
a * r.d + b * r.h + c * r.l + d * r.p,

e * r.a + f * r.e + g * r.i + h * r.m,
e * r.b + b * r.f + c * r.j + d * r.n,
e * r.c + b * r.g + c * r.k + d * r.o,
e * r.d + b * r.h + c * r.l + d * r.p,

*/


////////////////////////////////////////////////////////////////
//vec4 Matrix4::operator *(const vec4& a_rhs) const
//{
//
//}
//
Matrix4& Matrix4::operator +=(Matrix4& a_rhs)
{
	return *this = *this + a_rhs;
}
Matrix4& Matrix4::operator -=(Matrix4& a_rhs)
{
	return *this = *this - a_rhs;
}
Matrix4& Matrix4::operator *=(Matrix4& a_rhs)
{
	return *this = *this * a_rhs;
}

bool Matrix4::operator ==(const Matrix4& a_rhs) const
{
	return v1 == a_rhs.v1 && v2 == a_rhs.v2 && v3 == a_rhs.v3 && v4 == a_rhs.v4;
}
bool Matrix4::operator !=(const Matrix4& a_rhs) const
{
	return v1 != a_rhs.v1 || v2 != a_rhs.v2 || v3 != a_rhs.v3 || v4 != a_rhs.v4;
}