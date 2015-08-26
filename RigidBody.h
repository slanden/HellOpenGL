#pragma once
#include "Transform.h"
#include <iostream>

class RigidBody
{
public:
	float drag;
	vec3 velocity, force;
	float angularMomentum, torque;
	
	void AddForce(vec3 a_force)		{ force = force + a_force; }
	void AddTorque(float a_torque)	{ torque = torque + a_torque; };

	void Update(Transform &transform, float dt, float a_mass)
	{
		//transform.position = transform.position + velocity * dt;
		transform.m_local =
			Matrix4::MakeRotation(angularMomentum * dt) *
				 transform.m_local *
					 Matrix4::MakeTranslation(velocity * dt);


		vec3 dampening = velocity * -drag;
		vec3 acceleration = (force + dampening) * (1 / a_mass);
		velocity = velocity + acceleration * dt;
		
		force.x = force.y = force.z = 0;

		float a_damp = (angularMomentum * -1) * drag;
		float a_acc = (torque + a_damp) * (1 / a_mass);
		angularMomentum = angularMomentum + a_acc * dt;
		torque = 0;
	}
};