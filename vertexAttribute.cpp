#include "vertexAttribute.h"
#include <glm/glm.hpp>

using glm::mat4;

vertexAttribute::vertexAttribute()
{
}

vertexAttribute::vertexAttribute(const std::initializer_list<unsigned int>& a)
{
	for(unsigned int const &i: a)
	{
		pushAttribute(Attribute(i, sizeof(float), GL_FLOAT));
	}
}


void vertexAttribute::pushAttribute(const Attribute &a)
{
	attributes.push_back(a);
}

void vertexAttribute::bind()
{
	int size = 0;
	int cumulatedSize = 0;

	for (int i = 0; i < attributes.size(); i++)
	{
		int deba = attributes[i].sizeOfElement;
		int debb = attributes[i].length;
		size += attributes[i].sizeOfElement * attributes[i].length;
	}

	for (int i = 0; i < attributes.size(); i++)
	{	
		glEnableVertexAttribArray(i);
		glVertexAttribDivisor(i, 0);
		glVertexAttribPointer(i, attributes[i].length, attributes[i].type, 0, size, (void*)cumulatedSize);
		cumulatedSize += attributes[i].sizeOfElement * attributes[i].length;
	}

}

void vertexAttribute::bindForInstances()
{
	int c = 0;
	for(int i = attributes.size(); i<attributes.size()+8; i++)
	{
		glVertexAttribPointer(i, 4, GL_FLOAT, 0, sizeof(mat4) * 2, (void*)(sizeof(float) * c*4));
		glEnableVertexAttribArray(i);
		glVertexAttribDivisor(i, 1);
		c++;
	}
}


