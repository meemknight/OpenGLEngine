/////////////////////////////////////////////
//GameObjectPool.h
//Copyright(c) 2019 Luta Vlad
//https://github.com/meemknight/OpenGLEngine
/////////////////////////////////////////////

#pragma once
#include <algorithm>
#include "GameObject.h"
#include "AssetManager.h"
#include "ParticleSystem.h"

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
	id,
	scale,
	mass,
	collision,
	unique,
	empty,
	particle,
};

struct generalObjectData
{
	std::string name = "";
	std::string collisionName = "COLLISION";
	int type = 0;
	glm::vec3 position = { 0.f ,0.f ,0.f };
	glm::vec3 rotation = { 0.f ,0.f ,0.f };
	glm::vec3 ka = { 0.f ,0.f ,0.f };
	glm::vec3 kd = { 0.f ,0.f ,0.f };
	glm::vec3 ks = { 0.f ,0.f ,0.f };
	float strength = 0;
	float ambienceExponent = 1;
	float scale = 1.f;
	float mass = 0;
	int id = 0;
	bool unique = 0;
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
	int PushElement(T &e)
	{
		elements.push_back(e);
		currentKeyCount++;
		key.push_back(currentKeyCount);
		return currentKeyCount;
	}

	int PushElement(T &&e)
	{
		elements.push_back(e);
		currentKeyCount++;
		key.push_back(currentKeyCount);
		return currentKeyCount;
	}

	int PushElementWithId(T e, int id)
	{
		elements.push_back(e);
		key.push_back(id);
		return id;
	}

	T RemoveElement(int index)
	{
		T temp = std::forward<T>(elements[index]);

		elements.erase(elements.begin() + index);
		key.erase(key.begin() + index);

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

	T &getElementById(int id)
	{
		return elements[getPositionById(id)];
	}

	void eraseVectors()
	{
		elements.clear();
		key.clear();
		currentKeyCount = 0;
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
	KeyPair<glm::vec3> emptyObjectVector;
	KeyPair<ParticleSystem> particleObjectVector;

	ShaderProgram *sp = nullptr;
	Camera *camera = nullptr;
	LightContext *lights = nullptr;
	btDynamicsWorld *world = nullptr;
	ShaderProgram *particleShaderProgram = nullptr;

	void initialize(ShaderProgram *sp, Camera *camera, LightContext * lights, btDynamicsWorld *world, AssetManager<Texture> *textureManager, AssetManager<LoadedIndexModel> *modelManager, ShaderProgram *particleShaderProgram)
	{
		this->sp = sp; this->camera = camera;	this->lights = lights; this->world = world;
		this->textureManager = textureManager; this->modelManager = modelManager;
		this->particleShaderProgram = particleShaderProgram;
	}

	void setShaderProgramToAllComponents(ShaderProgram *sp);
	
	void clearLightContextContent();
	void load(const char *file);
	void drawAll(float deltaTime);
	void clearAll();

};

