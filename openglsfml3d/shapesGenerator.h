/////////////////////////////////////////////
//shapesGenerator.h
//Copyright(c) 2019 Luta Vlad
//https://github.com/meemknight/OpenGLEngine
/////////////////////////////////////////////

#pragma once
namespace shapeGenerator
{
	void generateMountains(float **vertexes, unsigned int **indices, int size, int &vSize, int &iSize);
	void generatePlane(float **vertexes, unsigned int **indices, int size, int &vSize, int &iSize);
}
