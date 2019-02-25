///////////////////////////////////
//GameObjectPool.cpp
//Copyright(c) 2019 Luta Vlad
///////////////////////////////////
#include "GameObjectPool.h"

//todo 
void GameObjectPool::load(const char * file)
{
	auto data = loadMapData(file);

	std::map <std::string, int> objectsNames;
	std::map <std::string, int> complexObjectsNames;
	std::map <std::string, int> phsicalObjectsNames;
	std::map <std::string, int> lightsNames;


	for(auto i: data)
	{
		switch (i.type)
		{

		case simple:
			{
			
				if(objectsNames.find(i.name) == objectsNames.end())
				{
					GameObject temp(sp, camera, lights);
					temp.loadPtn323(modelManager->getData(i.name.c_str()), textureManager);
					objectsNames[i.name] = gameObjectVector.PushElement(temp);
				
				}

			gameObjectVector.getElementById(objectsNames[i.name]).pushElement(i.position, i.rotation, i.scale);
			}
			break;
		case complex:
			{
				if (complexObjectsNames.find(i.name) == complexObjectsNames.end())
				{
					ComplexObject temp(camera, sp, lights);
					temp.loadPtn323(modelManager->getData(i.name.c_str()), *textureManager);
					complexObjectsNames[i.name] = complexObjectVector.PushElement(temp);

				}

				complexObjectVector.getElementById(complexObjectsNames[i.name]).pushElement(i.position, i.rotation, i.scale);

			}
			break;
		case phisical:
			{
				if (phsicalObjectsNames.find(i.name) == phsicalObjectsNames.end())
				{
					PhisicalObject temp(camera, sp, lights, world, nullptr, i.mass);
					temp.loadPtn323(modelManager->getData(i.name.c_str()), *textureManager);
					temp.loadCollisionBox(modelManager->getData(i.name.c_str()));
					phsicalObjectsNames[i.name] = phisicalObjectVector.PushElement(temp);
	
				}
	
				phisicalObjectVector.getElementById(phsicalObjectsNames[i.name]).pushElement(i.position, i.rotation);
	
		
			}
			break;
		case light:
			{
		
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
		i.fullCleanup();
	}
	gameObjectVector.eraseVectors();

	for (auto &i : complexObjectVector.elements)
	{
		i.fullCleanup();
	}
	complexObjectVector.eraseVectors();

	for (auto &i : phisicalObjectVector.elements)
	{
		i.fullCleanup();
	}
	phisicalObjectVector.eraseVectors();

}
