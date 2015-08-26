#pragma once
#include "cRenderUtils.h"


class Transform
{
public:

	Transform(Transform *a_parent = nullptr, Matrix4 a_local = Matrix4::Mat4MakeIdentity()) 
		: right(*(vec3*)&m_local.v1), up(*(vec3*)&m_local.v2), forward(*(vec3*)&m_local.v3), position(*(vec3*)&m_local.v4) { }

	Transform *m_parent;
	Matrix4 m_local;
	Matrix4 getGlobal()
	{
		return m_parent ? m_local * m_parent->getGlobal() : m_local;
	}

	vec3 &up, &right, &forward, &position;
};