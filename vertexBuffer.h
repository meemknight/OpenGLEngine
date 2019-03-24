/////////////////////////////////////////////
//vertexBuffer.h
//Copyright(c) 2019 Luta Vlad
//https://github.com/meemknight/OpenGLEngine
/////////////////////////////////////////////

#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

///bref this class holds data on the gpu.
///Use cleanup to clear it from the vram
class vertexBuffer
{
	

public:
	vertexBuffer() {};
	vertexBuffer(float *data, size_t size);
	
	void subData(void *data,size_t offset, size_t size);
	void bind();
	void unBind();

	void createData(float *data, size_t size);

	/// used to expand the data, does not generate a buffer
	void recreateData(float *data, size_t size); 
	void cleanup();

	unsigned int id;
	size_t size;
};

