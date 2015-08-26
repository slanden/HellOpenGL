#pragma once
#include <GLFW\glfw3.h>
#include "Core.h"

class Time :public Core
{
private:
	float m_totalTime, m_deltaTime, m_currentTime;

	Time() : m_totalTime(0), m_deltaTime(0), m_currentTime(0) { glfwSetTime(0); }

protected:
	bool OnCreate() { glfwSetTime(0); return true; }
	bool OnUpdate();

public:
	static Time&getInstance()   { static Time t; return t; }
	const float getDeltaTime() const { return m_deltaTime; }
	const float getTotalTime() const { return m_totalTime; }
};
