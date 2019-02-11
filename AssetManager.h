#pragma once
#include <map>
#include "Texture.h"

class AssetManager
{
	struct CompareCStrings
	{
		bool operator()(const char* lhs, const char* rhs) const {
			return std::strcmp(lhs, rhs) < 0;
		}
	};

public:

	std::map<const char*, Texture, CompareCStrings> loadedTextures;


	//void bind(const char* name, int bindPoint = 0);

	///the load method can both be used as a way of getting loaded Textures and load textures
	Texture getTexture(const char* name);

	void cleanUp();
};