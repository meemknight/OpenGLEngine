///////////////////////////////////
//GameObjectPool.h
//Copyright(c) 2019 Luta Vlad
///////////////////////////////////
#pragma once
#include <algorithm>
#include "GameObject.h"
#include "AssetManager.h"

enum Commands
{
	none,
	simple,
	complex,
	phisical,
	light,
	position,
	rotation,
	strength, //light strength
	exponent,  //ambience exponent
	ambience,
	diffuse,
	specular,
	id
};

struct generalObjectData
{
	std::string name = "";
	int type = 0;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 ka;
	glm::vec3 kd;
	glm::vec3 ks;
	float strength = 0;
	float ambienceExponent = 1;
	int id = 0;
};

std::vector<generalObjectData> loadMapData(const char *f);

template <class T>
struct KeyPair
{
	///you sholdn't modify this by hand
	std::vector<T> elements;
	std::vector<int> key;
	int currentKeyCount = 0;

	///this function returns the id
	int PushElement(T e)
	{
		elements.emplace_back(e);
		currentKeyCount++;
		key.push_back(currentKeyCount);
		return currentKeyCount;
	}

	int PushElementWithId(T e, int id)
	{
		elements.emplace_back(e);
		key.push_back(id);
		return currentKeyCount;
	}

	T RemoveElement(int index)
	{
		T temp = std::forward<T>(elements[index]);

		elements.erase(elements.begin() + index);

		return std::forward<T>(temp);
	}

	int getPositionById(int id)
	{
		auto i = std::find(key.begin(), key.end(), id);
		
		if(i == key.end())
		{
			return -1;
		}else
		{
			return (i - key.begin());
		}		
	}

	void eraseVectors()
	{
		elements.erase();
		key.erase();
	}
};



class GameObjectPool
{
public:
	GameObjectPool() = default;

	AssetManager<Texture> *textureManager = nullptr;
	AssetManager<LoadedIndexModel> *modelManager = nullptr;

	KeyPair<GameObject> gameObjectVector;
	KeyPair<ComplexObject> complexObjectVector;
	KeyPair<PhisicalObject> phisicalObjectVector;

	ShaderProgram *sp = nullptr;
	Camera *camera = nullptr;

	void load(const char *file);
	void drawAll();
	void clearAll();

};

