#include <GL\glew.h>
#include <GL\wglew.h>
#include <GLFW\glfw3.h>

#include <cassert>
#include <fstream>
#include <string>
#include <sstream>

#include "crenderutils.h"

// unsigned integer
//typedef unsigned int GLuint;
//typedef float GLfloat;

#include <vector>
#include <string>
#include <fstream>

GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile)
{
	std::string strShaderCode;
	//open shader file
	std::ifstream shaderStream(a_strShaderFile);
	//if that worked ok, load file line by line
	if (shaderStream.is_open())
	{
		std::string Line = "";
		while (std::getline(shaderStream, Line))
		{
			strShaderCode += "\n" + Line;
		}
		shaderStream.close();
	}

	//convert to cstring
	char const *szShaderSourcePointer = strShaderCode.c_str();

	//create shader ID
	GLuint uiShader = glCreateShader(a_eShaderType);
	//load source code
	glShaderSource(uiShader, 1, &szShaderSourcePointer, NULL);

	//compile shader
	glCompileShader(uiShader);

	//check for compilation errors and output them
	GLint iStatus;
	glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iStatus);
	if (iStatus == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(uiShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(uiShader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch (a_eShaderType)
		{
		case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
		case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}

	return uiShader;
}

GLuint CreateProgram(const char *a_vertex, const char *a_frag)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(CreateShader(GL_VERTEX_SHADER, a_vertex));
	shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, a_frag));

	//create shader program ID
	GLuint uiProgram = glCreateProgram();

	//attach shaders
	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
		glAttachShader(uiProgram, *shader);

	//link program
	glLinkProgram(uiProgram);

	//check for link errors and output them
	GLint status;
	glGetProgramiv(uiProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(uiProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(uiProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
	{
		glDetachShader(uiProgram, *shader);
		glDeleteShader(*shader);
	}

	return uiProgram;
}



Matrix4 getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar)
{
	//to correspond with mat4 in the shader
	//ideally this function would be part of your matrix class
	//however I wasn't willing to write your matrix class for you just to show you this
	//so here we are in array format!
	//add this to your matrix class as a challenge if you like!
	Matrix4 toReturn;
	toReturn.m[0] = 2.0 / (right - left);
	toReturn.m[1] = toReturn.m[2] = toReturn.m[3] = toReturn.m[4] = 0;
	toReturn.m[5] = 2.0 / (top - bottom);
	toReturn.m[6] = toReturn.m[7] = toReturn.m[8] = toReturn.m[9] = 0;
	toReturn.m[10] = 2.0 / (a_fFar - a_fNear);
	toReturn.m[11] = 0;
	toReturn.m[12] = -1 * ((right + left) / (right - left));
	toReturn.m[13] = -1 * ((top + bottom) / (top - bottom));
	toReturn.m[14] = -1 * ((a_fFar + a_fNear) / (a_fFar - a_fNear));
	toReturn.m[15] = 1;
	return toReturn;
}




RenderObject loadMesh(Vertex *verts, unsigned nverts, Triangle *tris, unsigned ntris)
{
	RenderObject ro;

	glGenBuffers(1, &ro.VBO);
	glGenBuffers(1, &ro.IBO);
	glGenVertexArrays(1, &ro.VAO);
	ro.size = 3 * ntris;

	glBindVertexArray(ro.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, ro.VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ro.IBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * nverts, verts, GL_STATIC_DRAW);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Triangle) * ntris, tris, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // position, 4 bytes (0)
	glEnableVertexAttribArray(1); //    color, 4 bytes (16)

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*) 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*) 16);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return ro;
}

void drawRenderObject(RenderObject ro,unsigned shader)
{
	glUseProgram(shader);
	glBindVertexArray(ro.VAO);
	glDrawElements(GL_TRIANGLES, ro.size, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0); // optional
	glUseProgram(0);
}

//GLuint LoadTexture(const char *a_path)
//{
//	GLuint handle;
//	int width = 0;
//	int height = 0;
//	int format = 0; //RGBA, RGB, Greyscale, etc.
//
//	unsigned char *pixelData = 
//		stbi_load(a_path, &width, &height, &format, STBI_default);
//
//	format = format == 3 ? GL_RGB : GL_RGBA;
//
//	glGenTextures(1, &handle);
//	glBindTexture(GL_TEXTURE_2D, handle);
//	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 
//				 0, format, GL_UNSIGNED_BYTE, pixelData);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	delete[] pixelData;
//}