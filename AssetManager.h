#pragma once
#include <map>
#include <cstring>
#include "Texture.h"

struct CompareCStrings
{
	bool operator()(const char* lhs, const char* rhs) const {
		return std::strcmp(lhs, rhs) < 0;
	}
};

template <class T>
class AssetManager
{
public:

	std::map<const char*, T, CompareCStrings> loadedTextures;

	///the load method can both be used as a way of getting loaded Textures and load textures
	T getTexture(const char* name);

	void cleanUp();
};

template <class T>
T AssetManager<T>::getTexture(const char * name)
{
	auto temp = loadedTextures.find(name);
	if (temp == loadedTextures.end())
	{
		//not found
		T t(name);
		size_t size = strlen(name) + 1;
		char *c = new char[size];
		memcpy(c, name, size);
		loadedTextures[c] = t;
		return t;
	}
	else
	{
		return temp->second;
	}
}

template <class T>
void AssetManager<T>::cleanUp()
{
	for (auto &i : loadedTextures)
	{
		delete[] i.first;
	}

}

