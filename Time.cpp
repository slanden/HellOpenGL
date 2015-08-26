#include "Time.h"

bool Time::OnUpdate()
{
	m_currentTime = glfwGetTime();
	m_deltaTime = m_currentTime - m_totalTime;
	m_totalTime = m_currentTime;

	return true;
}