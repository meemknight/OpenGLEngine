#include "AssetManager.h"


Texture AssetManager::getTexture(const char * name)
{
	auto temp = loadedTextures.find(name);
	if(temp == loadedTextures.end())
	{
		//not found
		Texture t(name);
		size_t size = strlen(name) + 1;
		char *c = new char[size];
		memcpy(c, name, size);
		loadedTextures[c] = t;
		return t;
	}else
	{
		return temp->second;
	}
}

void AssetManager::cleanUp()
{
	for(auto &i: loadedTextures)
	{
		delete[] i.first;
	}

}


