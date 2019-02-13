#pragma once
#include <GL/glew.h>

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

