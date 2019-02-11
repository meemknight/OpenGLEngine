#include <cstdlib>
#include <Windows.h>
#include <iostream>
#include "perlinNoise.h"
#include <glm/glm.hpp>

namespace shapeGenerator
{

	auto getVertex(int x, int y, int element, float **vertexes, int size)
	{
		int evaluated = (((x)+(y * (size + 1))) * 9) + (element);
		// std::cout << evaluated << std::endl;

		return &((*vertexes)[(((x)+(y * (size + 1))) * 9) + (element)]);
	}

	auto getVertexS(int x, int y, int element, float **vertexes, int size)
	{
		if (x < 0) { x = 0; }
		if (y < 0) { y = 0; }
		if (x >= size) { x = size - 1;}
		if (y >= size) { y = size - 1;}
		return(getVertex(x, y, element, vertexes, size));
	}

	void generateMountains(float **vertexes, unsigned int **indices, int size, int &vSize, int &iSize)
	{
		//srand(GetTickCount());
		srand(28244);

		vSize = (size + 1)*(size + 1) * 9;
		iSize = (size)*(size) * 6;

		*vertexes = new float[vSize];
		*indices = new unsigned int[iSize];

		float *fNoiseSeed2D = nullptr;
		float *fPerlinNoise2D = nullptr;
		fNoiseSeed2D = new float[size * size];
		fPerlinNoise2D = new float[size * size];
		for (int i = 0; i < size * size; i++) fNoiseSeed2D[i] = (float)rand() / (float)RAND_MAX;

		PerlinNoise2D(size, size, fNoiseSeed2D, 10, 1.5, fPerlinNoise2D);


		for (int y = 0; y < size + 1; y++)
		{
			for (int x = 0; x < size + 1; x++)
			{

				*(getVertex(x, y, 0, vertexes, size)) = x - (size / 2);  //x component
				*(getVertex(x, y, 1, vertexes, size)) = fPerlinNoise2D[x + size * y] * 70;
				*(getVertex(x, y, 2, vertexes, size)) = y - (size / 2); //z component
				//*(getVertex(x, y, 3, vertexes, size)) = pow(fPerlinNoise2D[x + size * y],3); //color
				//*(getVertex(x, y, 4, vertexes, size)) = pow(fPerlinNoise2D[x + size * y],3)*2; //color
				//*(getVertex(x, y, 5, vertexes, size)) = pow(fPerlinNoise2D[x + size * y],3); //color
				*(getVertex(x, y, 3, vertexes, size)) = 0.5;
				*(getVertex(x, y, 4, vertexes, size)) = 0.5;
				*(getVertex(x, y, 5, vertexes, size)) = 0.5;
		
			}
		}

		for (int y = 0; y < size + 1; y++)
		{
			for (int x = 0; x < size + 1; x++)
			{
				// normals
				glm::vec3 normal;
				// # P.xy store the position for which we want to calculate the normals
				// # height() here is a function that return the height at a point in the terrain

				// read neightbor heights using an arbitrary small offset
				float hL = *getVertexS(x - 1, y, 7, vertexes, size) - *getVertex(x, y, 7, vertexes, size);
				float hR = *getVertexS(x + 1, y, 7, vertexes, size) - *getVertex(x, y, 7, vertexes, size);
				float hD = *getVertexS(x, y - 1, 7, vertexes, size) - *getVertex(x, y, 7, vertexes, size);
				float hU = *getVertexS(x, y + 1, 7, vertexes, size) - *getVertex(x, y, 7, vertexes, size);
				  
				// deduce terrain normal
				normal.x = hL - hR;
				normal.y = 2.0;
				normal.z = hD - hU;
				normal = normalize(normal);

				*(getVertex(x, y, 6, vertexes, size)) = normal.x;
				*(getVertex(x, y, 7, vertexes, size)) = normal.y;
				*(getVertex(x, y, 8, vertexes, size)) = normal.z;

			}
		}

		int count = 0;

		for (int y = 0; y < size; y++)
		{
			for (int x = 0; x < size; x++)
			{
				/*
				(*indices)[count] = x + (y * (size + 1));
				count++;
				(*indices)[count] = x + 1 + (y * (size + 1));
				count++;
				(*indices)[count] = x + ((y + 1) * (size + 1));
				count++;

				(*indices)[count] = x + 1 + (y * (size + 1));
				count++;
				(*indices)[count] = x + 1 + ((y + 1) * (size + 1));
				count++;
				(*indices)[count] = x + ((y + 1) * (size + 1));
				count++;
				*/
				
				(*indices)[count] = x + ((y + 1) * (size + 1));
				count++;
				(*indices)[count] = x + 1 + (y * (size + 1));
				count++;
				(*indices)[count] = x + (y * (size + 1));
				count++;

				(*indices)[count] = x + ((y + 1) * (size + 1));
				count++;
				(*indices)[count] = x + 1 + ((y + 1) * (size + 1));
				count++;
				(*indices)[count] = x + 1 + (y * (size + 1));
				count++;
			}

		}

		delete[] fNoiseSeed2D;
		delete[] fPerlinNoise2D;
		
	}


	void generatePlane(float **vertexes, unsigned int **indices, int size, int &vSize, int &iSize)
	{

		vSize = (size + 1)*(size + 1) * 9;
		iSize = (size)*(size) * 6;

		*vertexes = new float[vSize];
		*indices = new unsigned int[iSize];

		//int count2 = 0;
		for (int y = 0; y < size + 1; y++)
		{
			for (int x = 0; x < size + 1; x++)
			{

				*(getVertex(x, y, 0, vertexes, size)) = x - (size / 2);  //x component
				*(getVertex(x, y, 1, vertexes, size)) = 0;
				*(getVertex(x, y, 2, vertexes, size)) = y - (size / 2); //z component

				// colors
				*(getVertex(x, y, 3, vertexes, size)) = 0.2;		
				*(getVertex(x, y, 4, vertexes, size)) = 0.2;
				*(getVertex(x, y, 5, vertexes, size)) = 0.2;

				// normals
				*(getVertex(x, y, 6, vertexes, size)) = 0;
				*(getVertex(x, y, 7, vertexes, size)) = 1;
				*(getVertex(x, y, 8, vertexes, size)) = 0;
			

				//count2 += 6;

			}
		}

		int count = 0;

		for (int y = 0; y < size; y++)
		{
			for (int x = 0; x < size; x++)
			{
				/*
				(*indices)[count] = x + (y * (size + 1));
				count++;
				(*indices)[count] = x + 1 + (y * (size + 1));
				count++;
				(*indices)[count] = x + ((y + 1) * (size + 1));
				count++;

				(*indices)[count] = x + 1 + (y * (size + 1));
				count++;
				(*indices)[count] = x + 1 + ((y + 1) * (size + 1));
				count++;
				(*indices)[count] = x + ((y + 1) * (size + 1));
				count++;
				*/

				(*indices)[count] = x + ((y + 1) * (size + 1));
				count++;
				(*indices)[count] = x + 1 + (y * (size + 1));
				count++;
				(*indices)[count] = x + (y * (size + 1));
				count++;

				(*indices)[count] = x + ((y + 1) * (size + 1));
				count++;
				(*indices)[count] = x + 1 + ((y + 1) * (size + 1));
				count++;
				(*indices)[count] = x + 1 + (y * (size + 1));
				count++;
			}

		}

	}


}