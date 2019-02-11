#include "Shader.h"
#include <cstdio>
#include <iostream>


ShaderProgram::ShaderProgram()
{

}

ShaderProgram::ShaderProgram(const VertexShader & vs,const FragmentShader & fs) :
	vs(vs), fs(fs)
{
	compileProgram();
}


void ShaderProgram::compileProgram()
{
	id = glCreateProgram();
	glAttachShader(id, vs.id);
	glAttachShader(id, fs.id);
	glLinkProgram(id);

	int info;
	glGetProgramiv(id, GL_LINK_STATUS, &info);
	if (info != GL_TRUE)
	{
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &info);
		char *p = new char[info];

		glGetProgramInfoLog(id, info, 0, p);
		std::cout << "Error compiling Shader: ";
		std::cout << p << "\n";
		delete[] p;
	}

	glValidateProgram(id);

	

}

void ShaderProgram::bind()
{
	glUseProgram(id);
}

void ShaderProgram::unBind()
{
	glUseProgram(0);
}

void ShaderProgram::deleteProgram()
{
	glDeleteProgram(id);
}


int ShaderProgram::getUniformLocation(const char* name)
{
	if(locations.find(name) == locations.end())
	{
		int a = glGetUniformLocation(id, name);

	#ifdef DEBUG
		if(a==-1)
		{
			std::cerr << "Uniform error: "<< name << std::endl;
		}
	#endif // DEBUG
		
		locations[name] = a;
		return a;
	}else
	{
		return locations[name];
	}

}

unsigned int ShaderProgram::getSoubRutineLocation(const char * name)
{
	if (subRoutines.find(name) == subRoutines.end())
	{
		int a = glGetSubroutineIndex(id, GL_FRAGMENT_SHADER, name);

#ifdef DEBUG
		if (a == -1)
		{
			std::cerr << "Uniform subroutine error: " << name << std::endl;
		}
#endif // DEBUG

		subRoutines[name] = a;
		return a;
	}
	else
	{
		return subRoutines[name];
	}
}

void ShaderProgram::uniform(const char * name, float a)
{
	bind(); // ? usefull
	glUniform1f(getUniformLocation(name), a);
}

void ShaderProgram::uniformi(const char * name, int a)
{
	bind(); // ? usefull
	glUniform1i(getUniformLocation(name), a);
}

void ShaderProgram::uniform(const char * name, float a, float b, float c, float d)
{
	bind(); // ? usefull
	glUniform4f(getUniformLocation(name), a, b, c, d);
}


void ShaderProgram::uniform(const char * name, float a, float b, float c)
{
	bind(); // ? usefull
	glUniform3f(getUniformLocation(name), a, b, c);
}

void ShaderProgram::uniform(const char * name, int count, float * a)
{
	bind(); // ? usefull
	glUniform1fv(getUniformLocation(name), count, a);
}


