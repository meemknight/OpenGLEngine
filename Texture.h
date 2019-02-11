#pragma once
#include<SFML/Graphics.hpp>
#include<GL/glew.h>

struct Texture
{
	unsigned int id = 0;


	Texture();
	Texture(const char *name);
	void create(const char *name);
	void bind(unsigned int sample = 0);
	void unBind();
};

