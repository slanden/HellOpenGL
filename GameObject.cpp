#include "GameObject.h"

void GameObject::Draw(Matrix4 a_view, Matrix4 a_projection)	//void GameObject::Draw(Matrix4 a_view, Matrix4 a_projection)
{
	glUseProgram(m_shader);
	GLuint ul_proj = glGetUniformLocation(m_shader, "Projection");
	GLuint ul_view = glGetUniformLocation(m_shader, "View");
	GLuint ul_model = glGetUniformLocation(m_shader, "Model");

	glUniformMatrix4fv(ul_proj, 1, GL_FALSE, a_projection.m);
	glUniformMatrix4fv(ul_view, 1, GL_FALSE, a_view.m);
	glUniformMatrix4fv(ul_model, 1, GL_FALSE, m_transform.getGlobal().m);

	drawRenderObject(m_ro, m_shader);
}