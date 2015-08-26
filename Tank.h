#pragma once
#include "GameObject.h"

class Tank : public GameObject
{
public:
	float m_speed;
	float m_torque;	//rotation speed



	Tank(RenderObject a_ro, unsigned a_shader, Matrix4 a_tran, float a_mass);

	void Update(float a_dt = Time::getInstance().getDeltaTime(),
		GLFWwindow *window = Window::getInstance().getHandle());
};

class Turret : public GameObject
{
public:
	float m_torque;

	Turret(RenderObject a_ro, unsigned a_shader, Tank &parent);

	void Update(float a_dt = Time::getInstance().getDeltaTime(),
		GLFWwindow *window = Window::getInstance().getHandle());
};

//void SpawnObject(const char a_name, int numObjects);