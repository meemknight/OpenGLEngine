/////////////////////////////////////////////
//indexBuffer.cpp
//Copyright(c) 2019 Luta Vlad
//https://github.com/meemknight/OpenGLEngine
/////////////////////////////////////////////
#include "indexBuffer.h"

indexBuffer::indexBuffer()
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW);
}

indexBuffer::indexBuffer(unsigned int * data, size_t size) :size(size)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void indexBuffer::subData(unsigned int * data, size_t offset, size_t size)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}

void indexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void indexBuffer::unBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void indexBuffer::cleanup()
{
	glDeleteBuffers(1, &id);
}
