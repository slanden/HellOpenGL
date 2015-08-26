#pragma once
#include "Core.h"
#include "Window.h"
#include "Time.h"
#include "Input.h"
#include "Camera.h"
#include <list>

class Engine : public Core
{
	std::list<Core*> m_cores;
	Engine() {}

public:
	static Engine &getInstance() { static Engine e; return e; }
	void LoadCore()
	{
		m_cores.push_back(&Window::getInstance());
		m_cores.push_back(&Time::getInstance());
		m_cores.push_back(&Input::getInstance());
		m_cores.push_back(&Camera::getInstance());
	}

	virtual bool Init()
	{
		for each(auto c in m_cores) if (!c->OnCreate()) return false;
		return true;
	}

	virtual bool Update()
	{
		for each(auto c in m_cores) if (!c->OnUpdate()) return false;
		return true;
	}
	virtual bool Shutdown()
	{
		m_cores.reverse();
		for each(auto c in m_cores) if (!c->OnShutdown()) return false;
		return true;
	}
};