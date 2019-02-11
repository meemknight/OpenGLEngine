#pragma once
#include "indexBuffer.h"
#include "vertexBuffer.h"
#include "vertexAttribute.h"
#include "Texture.h"

class Game
{
public:
	Game();
	
	static void draw(int count, vertexBuffer &vb, indexBuffer &ib, vertexAttribute &va);

};

namespace shapeGenerator
{
	void generateMountains(float **vertexes, unsigned int **indices, int size, int &vSize, int &iSize);
	void generatePlane(float **vertexes, unsigned int **indices, int size, int &vSize, int &iSize);
	
}
