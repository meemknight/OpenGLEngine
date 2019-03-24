/////////////////////////////////////////////
//indexBuffer.h
//Copyright(c) 2019 Luta Vlad
//https://github.com/meemknight/OpenGLEngine
/////////////////////////////////////////////

#pragma once
#include <GL/glew.h>

///bref the class for an openGl index buffer
///used to store the order of the geometry
///use the cleanup function to clear the data from the vram
class indexBuffer
{

public:
	indexBuffer();
	indexBuffer(unsigned int *data, size_t size);

	void subData(unsigned int *data, size_t offset, size_t size);
	void bind();
	void unBind();
	void cleanup();

	unsigned int id = 0;
	size_t size = 0;
};

