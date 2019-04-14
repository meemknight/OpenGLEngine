/////////////////////////////////////////////
//Shader.h
//Copyright(c) 2019 Luta Vlad
//https://github.com/meemknight/OpenGLEngine
/////////////////////////////////////////////
#pragma once
#include<GL/glew.h>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <cstring>
#include "tools.h"

class ShaderProgram;

template <GLenum shaderType>
class Shader
{
	Shader() {};
public:
	Shader(const char* name)	//todo move in cpp
	{
		size_t size;
		FILE *input;
		input = fopen(name, "rb");

		fseek(input, 0, SEEK_END);
		size = ftell(input);
		fseek(input, 0, SEEK_SET);

		char *data = new char[size + 1];

		fread(data, size, 1, input);
		data[size] = 0;
		//

		id = glCreateShader(shaderType);
		glShaderSource(id, 1, &data, 0);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);

		if (!result)
		{
			char* message;
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			message = new char[length];
			glGetShaderInfoLog(id, length, &length, message);
			elog(message);
			delete[] message;
		}

		delete[] data;

	}
	
//	static using shaderType = shaderType;

	void deleteShader();

	unsigned int id;

	friend ShaderProgram;
};

using VertexShader = Shader<GL_VERTEX_SHADER>; 
using FragmentShader = Shader<GL_FRAGMENT_SHADER>;

struct cmp_str //for compairing the strings literals
{
	bool operator()(const char *a,const char *b)const
	{
		return std::strcmp(a, b) < 0;
	}
};

///bref this class is used for compiling shaders and also using their data
class ShaderProgram
{
	void compileProgram();
	std::unordered_map<const char*, int> locations;
	std::unordered_map<const char*, unsigned int> subRoutines;
public:

	ShaderProgram();
	ShaderProgram(const VertexShader &vs,const FragmentShader &fs);
	
	unsigned int id = 0;

	
	void bind();
	void unBind();
	void deleteProgram();
	
	int getUniformLocation(const char* name);

	unsigned int getSoubRutineLocation(const char* name);

	void uniform(const char* name, float a);
	void uniform(const char* name, float a, float b, float c);
	void uniform(const char* name, float a, float b, float c, float d);
	void uniform(const char* name, int count, float *a);
	void uniformi(const char * name, int a);

	VertexShader vs;
	FragmentShader fs;

};

template<GLenum shaderType>
inline void Shader<shaderType>::deleteShader()
{
	glDeleteShader(id);
}
