#include "Tank.h"
#include "RigidBody.h"
#include "Input.h"

Tank::Tank(RenderObject a_ro, unsigned a_shader, Matrix4 a_tran, float a_mass)
{
	m_ro = a_ro;
	m_shader = a_shader;
	m_transform.m_local = a_tran;

	m_speed = 240;
	m_torque = .8;
	m_mass = a_mass;
	m_rigidbody.drag = 1;
}

void Tank::Update(float a_dt, GLFWwindow* window)
{
	m_rigidbody.Update(m_transform, a_dt, m_mass);

	//auto &iref = Input::getInstance();
	if (iref.getKeyDown('W'))
	{
		m_rigidbody.AddForce(m_transform.up * m_speed);
	}

	if (iref.getKeyDown('S'))
	{

	}

	if (iref.getKeyDown('A'))
	{
		float angle = m_torque * a_dt;
		m_rigidbody.AddTorque(m_torque);
		//m_transform.m_local = Matrix4::MakeRotation(angle) * m_transform.m_local;
	}

	if (iref.getKeyDown('D'))
	{
		float angle = -m_torque * a_dt;
		m_rigidbody.AddTorque(-m_torque);
		//m_transform.m_local = Matrix4::MakeRotation(angle) * m_transform.m_local;
	}
	
}

Turret::Turret(RenderObject a_ro, unsigned a_shader, Tank &parent)
{
	m_ro = a_ro;
	m_shader = a_shader;
	m_transform.m_parent = &parent.m_transform;
}

void Turret::Update(float a_dt, GLFWwindow *window)
{
	//auto &iref = Input::getInstance();

	if (iref.getKeyDown('Q'))
	{
		float angle = m_torque * a_dt;
		m_transform.m_local = Matrix4::MakeRotation(angle) * m_transform.m_local;
	}

	if (iref.getKeyDown('E'))
	{
		float angle = -m_torque * a_dt;
		m_transform.m_local = Matrix4::MakeRotation(angle) * m_transform.m_local;
	}
}

//void SpawnObject(const char a_type_name, const char a_name, int numObjects)
//{
//	Tank a_name(ro, shader, Matrix4::Mat4MakeIdentity(), 3);
//
//	a_name.m_transform.m_local.v4.x = S_W / 2;
//	a_name.m_transform.m_local.v4.y = S_H / 2;
//	a_name.m_transform.m_local.v4.z = 0;
//	a_name.m_transform.m_local.v4.w = 1;
//
//	Turret blueTurret(ro, shader, a_name);
//
//	blueTurret.m_transform.m_local = Matrix4::Mat4MakeIdentity();
//
//	blueTurret.m_transform.m_local.v4.y = 60;
//	blueTurret.m_torque = 1.5;
//}