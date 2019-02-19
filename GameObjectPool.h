///////////////////////////////////
//GameObjectPool.h
//Copyright(c) 2019 Luta Vlad
///////////////////////////////////
#pragma once
#include "GameObject.h"

class GameObjectPool
{
public:
	GameObjectPool();

	std::vector<GameObject> gameObjectVector;
	std::vector<ComplexObject> complexObjectVector;
	std::vector<PhisicalObject> phisicalObjectVector;

};

