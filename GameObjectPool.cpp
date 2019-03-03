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


	for(auto i: data)
	{

		switch (i.type)
		{

		case simple:
			{
				if(i.unique)
				{
					GameObject temp(sp, camera, lights);
					temp.loadPtn323(modelManager->getData(i.name.c_str()), textureManager);

					int id = 0;

					if (i.id != 0)
					{
						id = gameObjectVector.PushElementWithId(temp, i.id);
					}
					else
					{
						id = gameObjectVector.PushElement(temp);
					}

					gameObjectVector.getElementById(id).pushElement(i.position, i.rotation, i.scale);

				}else
				{
					if (objectsNames.find(i.name) == objectsNames.end())
					{
						GameObject temp(sp, camera, lights);
						temp.loadPtn323(modelManager->getData(i.name.c_str()), textureManager);

						if (i.id != 0)
						{
							objectsNames[i.name] = gameObjectVector.PushElementWithId(temp, i.id);
						}
						else
						{
							objectsNames[i.name] = gameObjectVector.PushElement(temp);
						}

					}
					gameObjectVector.getElementById(objectsNames[i.name]).pushElement(i.position, i.rotation, i.scale);

				}
			}
			break;
		case complex:
			{
				if(i.unique)
				{
					ComplexObject temp(camera, sp, lights);
					if (i.collisionName == "")
					{
						temp.loadPtn323(modelManager->getData(i.name.c_str()), *textureManager, nullptr);
					}
					else
					{
						temp.loadPtn323(modelManager->getData(i.name.c_str()), *textureManager, i.collisionName.c_str());
					}
					int id;
					if (i.id != 0)
					{
						id = complexObjectVector.PushElementWithId(temp, i.id);
					}
					else
					{
						id = complexObjectVector.PushElement(temp);
					}

					complexObjectVector.getElementById(id).pushElement(i.position, i.rotation, i.scale);

				}else
				{
					if (complexObjectsNames.find(i.name) == complexObjectsNames.end())
					{
						ComplexObject temp(camera, sp, lights);
						if (i.collisionName == "")
						{
							temp.loadPtn323(modelManager->getData(i.name.c_str()), *textureManager, nullptr);
						}
						else
						{
							temp.loadPtn323(modelManager->getData(i.name.c_str()), *textureManager, i.collisionName.c_str());
						}

						if (i.id != 0)
						{
							complexObjectsNames[i.name] = complexObjectVector.PushElementWithId(temp, i.id);
						}
						else
						{
							complexObjectsNames[i.name] = complexObjectVector.PushElement(temp);
						}

					}

					complexObjectVector.getElementById(complexObjectsNames[i.name]).pushElement(i.position, i.rotation, i.scale);

				}	
			}
			break;
		case phisical:
			{

				if(i.unique)
				{
					PhisicalObject temp(camera, sp, lights, world, nullptr, i.mass);
					if (i.collisionName == "")
					{
						temp.loadPtn323(modelManager->getData(i.name.c_str()), *textureManager, nullptr);
						temp.loadCollisionBox(modelManager->getData(i.name.c_str()), nullptr);

					}
					else
					{
						temp.loadCollisionBox(modelManager->getData(i.name.c_str()), i.collisionName.c_str());
						temp.loadPtn323(modelManager->getData(i.name.c_str()), *textureManager, i.collisionName.c_str());
					}
					int id;
					if (i.id != 0)
					{
						id = phisicalObjectVector.PushElementWithId(temp, i.id);
					}
					else
					{
						id = phisicalObjectVector.PushElement(temp);
					}
					phisicalObjectVector.getElementById(id).pushElement(i.position, i.rotation);
				}else
				{
					if (phsicalObjectsNames.find(i.name) == phsicalObjectsNames.end())
					{
						PhisicalObject temp(camera, sp, lights, world, nullptr, i.mass);
						if (i.collisionName == "")
						{
							temp.loadPtn323(modelManager->getData(i.name.c_str()), *textureManager, nullptr);
							temp.loadCollisionBox(modelManager->getData(i.name.c_str()), nullptr);

						}
						else
						{
							temp.loadCollisionBox(modelManager->getData(i.name.c_str()), i.collisionName.c_str());
							temp.loadPtn323(modelManager->getData(i.name.c_str()), *textureManager, i.collisionName.c_str());
						}

						if (i.id != 0)
						{
							phsicalObjectsNames[i.name] = phisicalObjectVector.PushElementWithId(temp, i.id);
						}
						else
						{
							phsicalObjectsNames[i.name] = phisicalObjectVector.PushElement(temp);
						}

					}
					phisicalObjectVector.getElementById(phsicalObjectsNames[i.name]).pushElement(i.position, i.rotation);
				}
				
			}
			break;
		case light:
		{
			lights->pushElement(Light({ i.position.x, i.position.y, i.position.z, 1 }, i.ka, i.kd, i.ks, i.strength));
		}
			break;
		default:
			elog("error in the map file: ", file, " unrecognised object type: ", i.type);
			break;
		}
	}

	glog("Loaded map: ", file);

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
	gameObjectVector.currentKeyCount = 0;

	for (auto &i : complexObjectVector.elements)
	{
		i.fullCleanup();
	}
	complexObjectVector.eraseVectors();
	complexObjectVector.currentKeyCount = 0;

	for (auto &i : phisicalObjectVector.elements)
	{
		i.fullCleanup();
	}
	phisicalObjectVector.eraseVectors();
	phisicalObjectVector.currentKeyCount = 0;

}
