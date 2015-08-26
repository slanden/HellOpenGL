#include <GL\glew.h>
#include <GL\wglew.h>
#include <GLFW\glfw3.h>
#include "crenderutils.h"
#include "GameObject.h"
#include "Tank.h"
#include "Engine.h"
#include <cassert>
#include <iostream>

const unsigned int  e_SCREEN_HEIGHT = 720;
const char			e_SCREEN_NAME[] = "Tank Trangles";

////Matrix4 Debug////
////////////////////
void printMat4(Matrix4 a)
{
	for (int i = 0; i < 16; i += 4)
	{
		std::cout << "( ";
		for (int j = i; j < i + 4; ++j)
		{
			std::cout << a.m[j] << " ";
		}
		std::cout << ") " << std::endl;
	}
}
///////////////////



int main()
{
	Engine &engine = Engine::getInstance();

	engine.LoadCore();
	engine.Init();

	//Camera info
	//Matrix4 view = Matrix4::Mat4MakeIdentity();
	//Matrix4 ortho = getOrtho(0, e_SCREEN_WIDTH, 0, e_SCREEN_HEIGHT, 0, 100);
	
	

	//mesh info
	Vertex verts[3] = { { { 0, 30, 0, 1},
						  { 0, 1, 1, 1 } },

					    { { -30, -30, 0, 1 }, 
						  { 1, 1, 0, 1 } },	

						{ { 30, -30, 0, 1 },
						  { 1, 0, 1, 1 } } };

	Triangle tris[1] = { 0, 1, 2 };
	
	//More debuggin'

	//Matrix4 a(1, 2, 4, 6,
	//		  2, 2, 2, 2,
	//		  1, 1, 1, 1,
	//		  4, 4, 4, 4);

	//Matrix4 b(2, 1, 3, 2,
	//		  2, 2, 2, 2,
	//		  1, 1, 1, 1,
	//		  3, 3, 3, 3);

	//Matrix4 c = a - b;

	//a -= b;

	//Matrix4 a_b_answer(3, 3, 7, 8,
	//				   4, 4, 4, 4,
	//				   2, 2, 2, 2,
	//				   7, 7, 7, 1);


	//assert(a == c);
	//printMat4(a);
	//std::cout << std::endl;
	//printMat4(c);
	//system("pause");


	RenderObject ro = loadMesh(verts, 3, tris, 1);
	//create shader program
	GLuint shader = CreateProgram("./shaders/simpleShader.vert",
								  "./shaders/simpleShader.frag");

	Tank blue(ro, shader, Matrix4::Mat4MakeIdentity(), 3);

	blue.m_transform.m_local.v4.x = e_SCREEN_WIDTH / 2;
	blue.m_transform.m_local.v4.y = e_SCREEN_HEIGHT / 2;
	blue.m_transform.m_local.v4.z = 0;
	blue.m_transform.m_local.v4.w = 1;

	Turret blueTurret(ro, shader, blue);

	blueTurret.m_transform.m_local = Matrix4::Mat4MakeIdentity();

	blueTurret.m_transform.m_local.v4.y = 60;
	blueTurret.m_torque = 1.5;

	float currentTime = 0;
	float deltaTime = 0;
	glfwSetTime(0);

	while (engine.Update())
	{
		deltaTime = Time::getInstance().getDeltaTime();

		blue.Draw();
		blueTurret.Draw();

		blue.Update();
		blueTurret.Update();
	}

	engine.Shutdown();
	return 0;
}