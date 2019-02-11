#pragma once
#include <GL/glew.h>
#include <vector>
#include <initializer_list>

struct Attribute	///vbo
{
	Attribute() = default;
	Attribute(unsigned int length, size_t sizeOfElement, GLenum type) :length(length), sizeOfElement(sizeOfElement), type(type)
	{};

	///this is how many attributes can be 1-4
	unsigned int length;

	///this is just the sizeof(type)
	size_t sizeOfElement;
	GLenum type;
};


class vertexAttribute
{
public:
	vertexAttribute();
	
	/// the quick constructor used for float values
	explicit vertexAttribute(const std::initializer_list<unsigned int> &a);
	

	std::vector<Attribute> attributes;


	void pushAttribute(const Attribute &a);
	void bind();
	void bindForInstances();
};

