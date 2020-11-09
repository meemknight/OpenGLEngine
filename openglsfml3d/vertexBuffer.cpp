/////////////////////////////////////////////
//vertexBuffer.cpp
//Copyright(c) 2019 Luta Vlad
//https://github.com/meemknight/OpenGLEngine
/////////////////////////////////////////////
#include "vertexBuffer.h"



vertexBuffer::vertexBuffer(float *data, size_t size, GLenum hint) :size(size)
{
	createData(data, size, hint);
}

void vertexBuffer::subData(void * data,size_t offset ,size_t size)
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void vertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void vertexBuffer::unBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vertexBuffer::createData(float *data, size_t size, GLenum hint)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, data, hint);
}

void vertexBuffer::recreateData(float * data, size_t size)
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

void vertexBuffer::cleanup()
{
	glDeleteBuffers(1, &id);
}

