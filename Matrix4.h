#pragma once
#include "Vector4.h"
#include "Vector3.h"

class Matrix4
{

public:

	union
	{
		struct { vec4 v1, v2, v3, v4; };
		float m[16];
		float mm[4][4];
		struct
		{
			float m11, m12, m13, m14,
				  m21, m22, m23, m24,
				  m31, m32, m33, m34,
				  m41, m42, m43, m44;
		};
	};

	Matrix4();
	Matrix4(const vec4 &col1, const vec4 &col2, const vec4 &col3, const vec4 &col4);
	Matrix4(const vec4 cols[4]);
	Matrix4(const float mm[4][4]);
	Matrix4(const float m[16]);
	Matrix4(float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44);

	static Matrix4 Mat4MakeIdentity();
	Matrix4 &Transpose();
	//builds and returns a new matrix that is the transpose of this matrix
	Matrix4 GetTranspose() const;

	static Matrix4 MakeRotation(float angle);
	static Matrix4 MakeTranslation(vec3 pos);

	Matrix4 operator   +(const Matrix4& a_rhs) const;
	Matrix4 operator   -(const Matrix4& a_rhs) const;
	Matrix4 operator   *(const Matrix4& a_rhs) const;
	vec4    operator   *(const vec4& a_rhs)    const;
	Matrix4 &operator +=(Matrix4& a_rhs);
	Matrix4 &operator -=(Matrix4& a_rhs);
	Matrix4 &operator *=(Matrix4& a_rhs);
	bool	operator  ==(const Matrix4& a_rhs) const;
	bool	operator  !=(const Matrix4& a_rhs) const;

};