///////////////////////////////////
//GameObjectPool.cpp
//Copyright(c) 2019 Luta Vlad
///////////////////////////////////
#include "GameObjectPool.h"

//todo 
void GameObjectPool::load(const char * file)
{
	auto data = loadMapData(file);
	for(auto i: data)
	{
		switch (i.type)
		{
		case simple:
			{
				GameObject object;
				object.camera = camera;
				object.sp = sp;
				object.loadPtn323(modelManager->getTexture(i.name.c_str()), sp);
				//object.
				//gameObjectVector.PushElement(object);
			}
			break;
		default:
			elog("error in the map file: ", file, " unrecognised object type: ", i.type);
			break;
		}
	
	}
}

void GameObjectPool::drawAll()
{
	for(auto &i : gameObjectVector.elements)
	{
		i.draw();
	}

	for (auto &i : complexObjectVector.elements)
	{
		i.draw();
	}

	for (auto &i : phisicalObjectVector.elements)
	{
		i.draw();
	}

}

void GameObjectPool::clearAll()
{
	for (auto &i : gameObjectVector.elements)
	{
		i.cleanup();
	}

	for (auto &i : complexObjectVector.elements)
	{
		i.cleanup();
	}

	for (auto &i : phisicalObjectVector.elements)
	{
		i.cleanup();
	}
}
