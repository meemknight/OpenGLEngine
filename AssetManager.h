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

	std::map<const char*, T, CompareCStrings> loadedData;

	///the load method can both be used as a way of getting loaded data and load data
	T getData(const char* name);

	void cleanUp();
};

template <class T>
T AssetManager<T>::getData(const char * name)
{
	auto temp = loadedData.find(name);
	if (temp == loadedData.end())
	{
		//not found
		T t(name);
		size_t size = strlen(name) + 1;
		char *c = new char[size];
		memcpy(c, name, size);
		loadedData[c] = std::move(t);
		return loadedData[c];
	}
	else
	{
		//return loadedData[name];
		return temp->second;
	}
}

template <class T>
void AssetManager<T>::cleanUp()
{
	for (auto &i : loadedData)
	{
		delete[] i.first;
	}
	loadedData.clear();
}

