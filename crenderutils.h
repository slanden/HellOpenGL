#pragma once
#include <GL\glew.h>
#include <GL\wglew.h>
#include <GLFW\glfw3.h>
#include <STB\stb_image.h>

#include <cassert>
#include <fstream>
#include <string>
#include <sstream>

#include "Matrix4.h"
#include "Vector4.h"
#include "Vector3.h"

struct Vertex { vec4 position; vec4 color; };

struct Triangle { unsigned v[3]; }; // 12 bytes

struct RenderObject
{
	unsigned VBO, IBO, VAO, size;
};

RenderObject loadMesh(Vertex *verts, unsigned nverts,
					  Triangle *tris, unsigned ntris);

void drawRenderObject(RenderObject ro, unsigned shader);

GLuint CreateProgram(const char *a_vertex, const char *a_frag);

Matrix4 getOrtho(float left, float right, 
				 float bottom, float top, 
				 float a_fNear, float a_fFar);

GLuint LoadTexture(const char *a_path);