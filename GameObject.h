#pragma once
#include "cRenderUtils.h"
#include "RigidBody.h"
#include "Input.h"
#include "Camera.h"
#include "Time.h"

class GameObject
{
public:
	float m_mass;

	Transform m_transform;
	RenderObject m_ro;
	RigidBody m_rigidbody;

	Input &iref;

	GameObject() : iref(Input::getInstance()) {}

	unsigned m_shader;
	void Draw(Matrix4 a_view	   = Camera::getInstance().getCameraData().m_view, 
			  Matrix4 a_projection = Camera::getInstance().getCameraData().m_projection);

	virtual void Update(float a_dt = Time::getInstance().getDeltaTime(), 
						GLFWwindow *window = Window::getInstance().getHandle()) {};

};

//static void SpawnObject(const char a_name, int numObjects);