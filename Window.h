#pragma once
#include <GL\glew.h>
#include <GL\wglew.h>
#include <GLFW\glfw3.h>
#include "Core.h"

#ifndef e_SCREEN_WIDTH
#define e_SCREEN_WIDTH 1280
#endif

extern const unsigned int e_SCREEN_HEIGHT;
extern const char			e_SCREEN_NAME[];

class Window : public Core
{
	GLFWwindow* m_window;

	Window() : m_window(nullptr) {}

protected:
	bool OnCreate()
	{
		if (!glfwInit()) return false;

		m_window = glfwCreateWindow(e_SCREEN_WIDTH, e_SCREEN_HEIGHT, e_SCREEN_NAME, NULL, NULL);
		if (!m_window) { glfwTerminate(); return false; }
		glfwMakeContextCurrent(m_window);
		if (glewInit() != GLEW_OK) { glfwTerminate(); return false; }

		////////////////////////////////////////////////////////////////////////
		auto major = glfwGetWindowAttrib(m_window, GLFW_CONTEXT_VERSION_MAJOR);
		auto minor = glfwGetWindowAttrib(m_window, GLFW_CONTEXT_VERSION_MINOR);
		auto revision = glfwGetWindowAttrib(m_window, GLFW_CONTEXT_REVISION);
		printf("GL %i.%i.%i\n", major, minor, revision);
		////////////////////////////////////////////////////////////////////////

		return true;
	}

	bool OnUpdate()
	{
		glfwSwapBuffers(m_window);
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		return !glfwWindowShouldClose(m_window);
	}

	bool OnShutdown()
	{
		glfwTerminate();
		return true;
	}

public:
	static Window &getInstance()
	{
		static Window w;
		return w;
	}
	GLFWwindow *getHandle() { return m_window; }
};