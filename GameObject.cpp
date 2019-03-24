/////////////////////////////////////////////
//GameObject.cpp
//Copyright(c) 2019 Luta Vlad
//https://github.com/meemknight/OpenGLEngine
/////////////////////////////////////////////

#include "GameObject.h"
#include "tools.h"
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

#define ALLOCA_OPTIMISATIONS

//if the collisionidentifiername is nullptr then it would be just ignored
void appendObject_(vertexBuffer &dataTodraw, std::vector<ObjectData> &objectData, const LoadedIndexModel & model, const glm::vec3 &padding, AssetManager<Texture> &manager, const char* collisionIdentifierName = "COLLISION")
{
	std::vector<float> dataForModel;
	std::vector<unsigned int> indicesForModel; 
	
	int materialStart = objectData.size();

	int maxData = 0;
	int maxIndices = 0;
	for (unsigned int m = 0; m < model.m.LoadedMeshes.size(); m++)
	{
		int d = model.m.LoadedMeshes[m].Vertices.size();
		int i = model.m.LoadedMeshes[m].Indices.size();
		if (d < maxData) { d = maxData; }
		if (i < maxIndices) { i = maxIndices; }
	}

	dataForModel.reserve(maxData * 8);
	indicesForModel.reserve(maxIndices);


	for (unsigned int m = 0; m < model.m.LoadedMeshes.size(); m++)
	{
		
		
		
		
		if (collisionIdentifierName != nullptr && model.m.LoadedMeshes[m].MeshName != "" && model.m.LoadedMeshes[m].MeshName.find(collisionIdentifierName) != std::string::npos)
		{
		
			continue;
			//not loading the collision boxes into the gpu 
		}
		
		ObjectData temp;

		dataForModel.clear();
		for (unsigned int i = 0; i < model.m.LoadedMeshes[m].Vertices.size(); i++)
		{
			dataForModel.push_back(model.m.LoadedMeshes[m].Vertices[i].Position.X + padding.x);
			dataForModel.push_back(model.m.LoadedMeshes[m].Vertices[i].Position.Y + padding.y);
			dataForModel.push_back(model.m.LoadedMeshes[m].Vertices[i].Position.Z + padding.z);

			dataForModel.push_back(model.m.LoadedMeshes[m].Vertices[i].TextureCoordinate.X);
			dataForModel.push_back(model.m.LoadedMeshes[m].Vertices[i].TextureCoordinate.Y);

			dataForModel.push_back(model.m.LoadedMeshes[m].Vertices[i].Normal.X);
			dataForModel.push_back(model.m.LoadedMeshes[m].Vertices[i].Normal.Y);
			dataForModel.push_back(model.m.LoadedMeshes[m].Vertices[i].Normal.Z);
		}
		temp.vb = vertexBuffer(dataForModel.data(), dataForModel.size() * sizeof(float));

		indicesForModel.clear();

		for (unsigned int i = 0; i < model.m.LoadedMeshes[m].Indices.size(); i++)
		{
		
			indicesForModel.push_back(model.m.LoadedMeshes[m].Indices[i]);
		}
		temp.ib = indexBuffer(indicesForModel.data(), indicesForModel.size() * sizeof(unsigned int));
		temp.va.attributes.clear();
		temp.va = std::move(vertexAttribute{ 3, 2, 3 }); 

		
		
		objectData.push_back(temp);
	}
	int padd = 0;
	for (unsigned int m = 0; m < model.m.LoadedMeshes.size(); m++)
	{
		if (collisionIdentifierName != nullptr && model.m.LoadedMeshes[m].MeshName != "" && model.m.LoadedMeshes[m].MeshName.find(collisionIdentifierName) != std::string::npos)
		{
			padd++;
			continue;
			//not loading the collision boxes into the gpu 
		}

		auto mat = model.m.LoadedMeshes[m].MeshMaterial;
		Material material;

		material.ka = { mat.Ka.X, mat.Ka.Y, mat.Ka.Z };
		material.kd = { mat.Kd.X, mat.Kd.Y, mat.Kd.Z };
		material.ks = { mat.Ks.X, mat.Ks.Y, mat.Ks.Z };
		material.shiny = mat.Ns;
		if (material.shiny == 0) { material.shiny = 1; }
		
		if (mat.map_Kd != "")
		{
			
			objectData[m + materialStart - padd].texture = manager.getData(mat.map_Kd.c_str());

		}
		
		objectData[m + materialStart - padd].material = material;

		//old implementation
		/*
		Material material;
		material.ka = glm::vec3(model.m.LoadedMaterials[m].Ka.X, model.m.LoadedMaterials[m].Ka.Y, model.m.LoadedMaterials[m].Ka.Z);
		material.kd = glm::vec3(model.m.LoadedMaterials[m].Kd.X, model.m.LoadedMaterials[m].Kd.Y, model.m.LoadedMaterials[m].Kd.Z);
		material.ks = glm::vec3(model.m.LoadedMaterials[m].Ks.X, model.m.LoadedMaterials[m].Ks.Y, model.m.LoadedMaterials[m].Ks.Z);
		material.shiny = model.m.LoadedMaterials[m].Ns;
		if (material.shiny == 0) { material.shiny = 1; }
		if (model.m.LoadedMaterials[m].map_Kd != "")
		{
			std::cout << "found texture: " << model.m.LoadedMaterials[m].map_Kd << "\n";
			//if(manager!=0)
			//{
			//	Texture t(model.m.LoadedMaterials[m].map_Kd.c_str());
			//	manager->pushBack(t);
			//	material.materialIndex = t.id;
			//}
		
			objectData[m + materialStart].texture = manager.getTexture(model.m.LoadedMaterials[m].map_Kd.c_str());
		}
		if(m<objectData.size())
		{
			objectData[m + materialStart].material = material;
		}
		else 
		{
			objectData[m + materialStart].material = Material::defaultMaterial();
			wlog("missing a material...");
		}
		*/
	}

}

void GameObject::initialize()
{
	//warning, adding code here might break some code at the gpucleanup and cleanup
	dataTodraw.createData(0, 0);
	//timeUniformLocation = glGetUniformLocation(sp.id, "u_time");
}



void GameObject::loadPtn323(const LoadedIndexModel &model, AssetManager<Texture> *manager)
{
	
	//initialize();

	std::vector<float> dataForModel;
	dataForModel.reserve(model.m.LoadedVertices.size() * 8);
	for (unsigned int i = 0; i < model.m.LoadedVertices.size(); i++)
	{
		dataForModel.push_back(model.m.LoadedVertices[i].Position.X);
		dataForModel.push_back(model.m.LoadedVertices[i].Position.Y);
		dataForModel.push_back(model.m.LoadedVertices[i].Position.Z);

		dataForModel.push_back(model.m.LoadedVertices[i].TextureCoordinate.X);
		dataForModel.push_back(model.m.LoadedVertices[i].TextureCoordinate.Y);

		dataForModel.push_back(model.m.LoadedVertices[i].Normal.X);
		dataForModel.push_back(model.m.LoadedVertices[i].Normal.Y);
		dataForModel.push_back(model.m.LoadedVertices[i].Normal.Z);
	}
	std::vector<unsigned int> indicesForModel;
	indicesForModel.reserve(model.m.LoadedIndices.size());
	for (unsigned int i = 0; i < model.m.LoadedIndices.size(); i++)
	{
		indicesForModel.push_back(model.m.LoadedIndices[i]);
	}
	vb = vertexBuffer(dataForModel.data(), dataForModel.size() * sizeof(float));
	ib = indexBuffer(indicesForModel.data(), indicesForModel.size() * sizeof(unsigned int));
	va = std::move(vertexAttribute{ 3, 2, 3 });


	if(model.m.LoadedMaterials.size()>0)
	{
	
		material.ka = glm::vec3(model.m.LoadedMaterials[0].Ka.X, model.m.LoadedMaterials[0].Ka.Y, model.m.LoadedMaterials[0].Ka.Z);
		material.kd = glm::vec3(model.m.LoadedMaterials[0].Kd.X, model.m.LoadedMaterials[0].Kd.Y, model.m.LoadedMaterials[0].Kd.Z);
		material.ks = glm::vec3(model.m.LoadedMaterials[0].Ks.X, model.m.LoadedMaterials[0].Ks.Y, model.m.LoadedMaterials[0].Ks.Z);
		material.shiny = model.m.LoadedMaterials[0].Ns;
		if (material.shiny == 0) { material.shiny = 1; }

		if (model.m.LoadedMaterials[0].map_Kd != "")
		{

			texture = manager->getData(model.m.LoadedMaterials[0].map_Kd.c_str());

		}
	}

	//std::cout << "\n material file name: " <<model.m.LoadedMaterials[0].name <<" "<<model.m.LoadedMaterials.size();
}

/// may be deprecated
[[deprecated]]
void GameObject::loadPcn333(const LoadedIndexModel &model, ShaderProgram *sp)
{
	std::vector<float> dataForModel;
	dataForModel.reserve(model.m.LoadedVertices.size() * 9);
	for (unsigned int i = 0; i < model.m.LoadedVertices.size(); i++)
	{
		dataForModel.push_back(model.m.LoadedVertices[i].Position.X);
		dataForModel.push_back(model.m.LoadedVertices[i].Position.Y);
		dataForModel.push_back(model.m.LoadedVertices[i].Position.Z);

		dataForModel.push_back(0.5);	//color
		dataForModel.push_back(0.5);	
		dataForModel.push_back(0.5);

		dataForModel.push_back(model.m.LoadedVertices[i].Normal.X);
		dataForModel.push_back(model.m.LoadedVertices[i].Normal.Y);
		dataForModel.push_back(model.m.LoadedVertices[i].Normal.Z);
	}
	std::vector<unsigned int> indicesForModel;
	indicesForModel.reserve(model.m.LoadedIndices.size());
	for (unsigned int i = 0; i < model.m.LoadedIndices.size(); i++)
	{
		indicesForModel.push_back(model.m.LoadedIndices[i]);
	}
	vb = vertexBuffer(dataForModel.data(), dataForModel.size() * sizeof(float));
	ib = indexBuffer(indicesForModel.data(), indicesForModel.size() * sizeof(unsigned int));
	vertexAttribute v;
	v.pushAttribute(Attribute(3, sizeof(float), GL_FLAT));
	v.pushAttribute(Attribute(3, sizeof(float), GL_FLAT));
	v.pushAttribute(Attribute(3, sizeof(float), GL_FLAT));
	va = std::move(v);
	this->sp = sp;

	//initialize();
}

void GameObject::setData(vertexBuffer vb, indexBuffer ib, vertexAttribute va, ShaderProgram * sp, Camera * camera)
{
	this->vb = vb;
	this->ib = ib;
	this->va = std::move(va);
	this->sp = sp;
	this->camera = camera;
}

/*
Material GameObject::getMaterial()
{
	return material;
}
*/

Material & GameObject::getMaterialReffernce()
{
	return material;
}


void GameObject::setMaterial(const Material & m)
{
	material = m;
}


void GameObject::draw()
{
	if (camera != 0)
	{
		for (auto &i : instances)
		{
			//i.worldToViexMatrix = camera->getProjectionViewMatrix();
			
		}
		sp->uniform("u_eyePosition", camera->getCurrentViewingPosition().x, camera->getCurrentViewingPosition().y, camera->getCurrentViewingPosition().z);
	} //sets the world to view matrix;

	
	material.bind(*sp);
	
	if (texture.id)
	{
		texture.bind();
		sp->uniformi("u_sampl", 0);
		GLuint temp = sp->getSoubRutineLocation("p_withT");
		if (temp != GL_INVALID_INDEX)
		{
			glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &temp);
		}
	}
	else
	{
		GLuint temp = sp->getSoubRutineLocation("p_withoutT");
		if (temp != GL_INVALID_INDEX)
		{
			glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &temp);
		}
	}

	sp->bind();
	vb.bind();
	ib.bind();

	va.bind();

#ifndef ALLOCA_OPTIMISATIONS
	int offset = 0;
	glm::mat4 temp[2];
	for (int i = 0; i < instances.size(); i++)
	{
		temp[0] = camera->getProjectionViewMatrix() * instances[i].objectToWorldMatrix();
		temp[1] = instances[i].objectToWorldMatrix();
		dataTodraw.subData(temp, offset, sizeof(temp));
		offset += sizeof(glm::mat4);
		offset += sizeof(glm::mat4);
	}
#else // !ALLOCA_OPTIMISATIONS \/

	int offset = 0;
	size_t tempSize = 2 * sizeof(glm::mat4) * instances.size();
	glm::mat4 *temp = (glm::mat4*)alloca(tempSize);
	for (unsigned int i = 0; i < instances.size(); i++)
	{
		temp[offset + 0] = camera->getProjectionViewMatrix() * instances[i].objectToWorldMatrix();
		temp[offset + 1] = instances[i].objectToWorldMatrix();
		offset += 2;
	}
	dataTodraw.subData(temp, 0, tempSize);

#endif //ALLOCA_OPTIMISATIONS ^

	if(lights != nullptr)
	{
		lights->bind(*sp);
	}
	
	va.bindForInstances();

	glDrawElementsInstanced(GL_TRIANGLES, ib.size / sizeof(unsigned int), GL_UNSIGNED_INT, 0, instances.size());

}

void GameObject::pushElement(glm::mat4 matrix)
{
	instances.push_back(ObjectPosition(matrix));
	dataTodraw.recreateData(0, sizeof(glm::mat4)*instances.size() * 2);
}

void GameObject::pushElement(glm::vec3 position)
{
	pushElement(glm::translate(position));
}

void GameObject::pushElement(glm::vec3 position, glm::vec3 rotation)
{
	
	auto objectToWorldMatrix = glm::rotate(glm::translate(position), glm::radians(rotation.x), glm::vec3(1, 0, 0)) *
		glm::rotate(glm::radians(rotation.y), glm::vec3(0, 1, 0)) *
		glm::rotate(glm::radians(rotation.z), glm::vec3(0, 0, 1));
	pushElement(objectToWorldMatrix);
	
		
}

void GameObject::pushElement(glm::vec3 position, glm::vec3 rotation, float scale)
{
	auto objectToWorldMatrix = glm::scale(glm::rotate(glm::translate(position), glm::radians(rotation.x), glm::vec3(1, 0, 0)) *
		glm::rotate(glm::radians(rotation.y), glm::vec3(0, 1, 0)) *
		glm::rotate(glm::radians(rotation.z), glm::vec3(0, 0, 1)), {scale, scale, scale});
	pushElement(objectToWorldMatrix);
}

void GameObject::deleteElement(int index)
{
#ifdef _DEBUG
	assert(index < instances.size());
#endif // _DEBUG
	instances.erase(instances.begin() + index);
}

void GameObject::cleanup()
{
	instances.clear();
	//gpuCleanup();

	dataTodraw.cleanup();
	initialize();
}

void GameObject::gpuCleanup()
{
	vb.cleanup();
	va.attributes.clear();
	ib.cleanup();
}

glm::mat4 ObjectPosition::objectToWorldMatrix()
{
	if (modified)
	{
		modified = 0;

		if (scale == 1)
		{
			glm::mat4 transl = glm::translate(glm::vec3(x, y, z));
			_objectToWorldMatrix = glm::rotate(transl, glm::radians(rx), glm::vec3(1, 0, 0)) *
				glm::rotate(glm::radians(ry), glm::vec3(0, 1, 0)) *
				glm::rotate(glm::radians(rz), glm::vec3(0, 0, 1));
		}
		else
		{
			glm::mat4 transl = glm::translate(glm::vec3(x, y, z));
			glm::mat4 rotated = glm::rotate(transl, glm::radians(rx), glm::vec3(1, 0, 0)) *
				glm::rotate(glm::radians(ry), glm::vec3(0, 1, 0)) *
				glm::rotate(glm::radians(rz), glm::vec3(0, 0, 1));
			_objectToWorldMatrix = glm::scale(rotated, glm::vec3(scale, scale, scale));
		}

		//to compute matrixes
	}

	return _objectToWorldMatrix;
}

void ComplexObject::initialize()
{
	dataTodraw.createData(0, 0);
}

void ComplexObject::loadPtn323(const LoadedIndexModel & model, AssetManager<Texture> &manager, const char* collisionIdentifierName)
{

	appendObject(model, manager, {0,0,0}, collisionIdentifierName);

}

void ComplexObject::draw()
{
	sp->bind();
	if (lights != nullptr)
	{
		lights->bind(*sp);
	}

	if (camera != 0)
	{
		for (auto &i : instances)
		{
			//i.worldToViexMatrix = camera->getProjectionViewMatrix();
			
		}
		sp->uniform("u_eyePosition", camera->getCurrentViewingPosition().x, camera->getCurrentViewingPosition().y, camera->getCurrentViewingPosition().z);
	} //sets the world to view matrix;
	
	
	//todo ? only in textures ??
	sp->uniformi("u_sampl", 0);

	for(unsigned int m=0; m<objectData.size(); m++)
	{
		objectData[m].material.bind(*sp);

		objectData[m].vb.bind();
		objectData[m].ib.bind();

		objectData[m].va.bind();

		int offset = 0;
		glm::mat4 temp[2];
		for (unsigned int i = 0; i < instances.size(); i++)
		{
			//temp[i * 2] = instances[i].fullTransformMatrix();
			//temp[i * 2 + 1] = instances[i].objectToWorldMatrix();
			temp[0] = camera->getProjectionViewMatrix() * instances[i].objectToWorldMatrix();
			temp[1] = instances[i].objectToWorldMatrix();
			dataTodraw.subData(temp, offset, sizeof(temp));
			//dataTodraw.subData(&instances[i].fullTransformMatrix(), offset, sizeof(glm::mat4));
			//dataTodraw.subData(&instances[i].objectToWorldMatrix(), offset, sizeof(glm::mat4));
			offset += sizeof(glm::mat4);
			offset += sizeof(glm::mat4);
		}


		objectData[m].va.bindForInstances();

		if (objectData[m].texture.id != 0)
		{
			objectData[m].texture.bind(0);
			GLuint temp = sp->getSoubRutineLocation("p_withT");
			glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &temp);
		}
		else
		{
			GLuint temp = sp->getSoubRutineLocation("p_withoutT");
			glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &temp);
		}

		glDrawElementsInstanced(GL_TRIANGLES, objectData[m].ib.size / sizeof(unsigned int), GL_UNSIGNED_INT, 0, instances.size());
		
	}
	
}

void ComplexObject::pushElement(glm::mat4 matrix)
{
	instances.push_back(ObjectPosition(matrix));
	dataTodraw.recreateData(0, sizeof(glm::mat4)*instances.size() * 2);
}

void ComplexObject::pushElement(glm::vec3 position)
{
	pushElement(glm::translate(position));
}

void ComplexObject::pushElement(glm::vec3 position, glm::vec3 rotation)
{

	auto objectToWorldMatrix = glm::rotate(glm::translate(position), glm::radians(rotation.x), glm::vec3(1, 0, 0)) *
		glm::rotate(glm::radians(rotation.y), glm::vec3(0, 1, 0)) *
		glm::rotate(glm::radians(rotation.z), glm::vec3(0, 0, 1));
	pushElement(objectToWorldMatrix);

}

void ComplexObject::pushElement(glm::vec3 position, glm::vec3 rotation, float scale)
{
	auto objectToWorldMatrix = glm::scale(glm::rotate(glm::translate(position), glm::radians(rotation.x), glm::vec3(1, 0, 0)) *
		glm::rotate(glm::radians(rotation.y), glm::vec3(0, 1, 0)) *
		glm::rotate(glm::radians(rotation.z), glm::vec3(0, 0, 1)), { scale, scale, scale });
	pushElement(objectToWorldMatrix);
}

void ComplexObject::deleteElement(int index)
{
	instances.erase(instances.begin() + index);
	dataTodraw.recreateData(0, sizeof(glm::mat4)*instances.size() * 2);
}


void ComplexObject::appendObject(const LoadedIndexModel & model, AssetManager<Texture> &manager, const glm::vec3 &padding, const char* collisionIdentifierName)
{
	appendObject_(dataTodraw, objectData, model, padding, manager, collisionIdentifierName);
}

void ComplexObject::cleanup()
{
	instances.clear();

	//gpuCleanup();
}

void ComplexObject::gpuCleanup()
{
	for(auto &i: objectData)
	{
		i.ib.cleanup();
		i.vb.cleanup();
	}
	objectData.clear();

}

// ////////////////////////


void PhisicalObject::initialize()
{
	dataTodraw.createData(0, 0);
}

void PhisicalObject::loadPtn323(const LoadedIndexModel & model, AssetManager<Texture> &manager, const char* collisionIdentifierName)
{
	//initialize();
	appendObject(model, manager, {0,0,0}, collisionIdentifierName);
}

///collisionIdentifier can be a nullptr
void PhisicalObject::loadCollisionBox(const LoadedIndexModel & model, const char* collisionIdentifierName)
{
	//old implementation
	/*
	unsigned int size = model.m.LoadedIndices.size();
	btVector3 *temp = new btVector3[size];

	for (int i = 0; i < size; i++)
	{
		auto v = model.m.LoadedVertices[model.m.LoadedIndices[i]].Position;
		temp[i] = { v.X, v.Y, v.Z };
	}
	auto a = new btCompoundShape;
	a->addChildShape(btTransform::getIdentity(), new btConvexHullShape(*temp, size));
	collisionShape = a; 
	*/
	
	//deleteCollisionShape();

	if(mass != 0)
	{
		collisionShape = new btCompoundShape();

		size_t size = model.m.LoadedMeshes.size();
		size_t loadedCollisionBoxes = 0;
		for (unsigned int m = 0; m < size; m++)
		{
			if (collisionIdentifierName == nullptr || (model.m.LoadedMeshes[m].MeshName != "" && model.m.LoadedMeshes[m].MeshName.find(collisionIdentifierName) != std::string::npos))
			{
				loadedCollisionBoxes++;
				unsigned int size = model.m.LoadedMeshes[m].Indices.size();

#ifdef ALLOCA_OPTIMISATIONS
				btVector3 *temp = (btVector3*)alloca(sizeof(btVector3) * size);
#else
				btVector3 *temp = new btVector3[size];
#endif // ALLOCA_OPTIMISATIONS

			

				for (unsigned int i = 0; i < size; i++)
				{
					auto v = model.m.LoadedMeshes[m].Vertices[model.m.LoadedIndices[i]].Position;
					temp[i] = { v.X, v.Y, v.Z };
				}

				((btCompoundShape*)collisionShape)->addChildShape(btTransform::getIdentity(), new btConvexHullShape(*temp, size));
				
#ifndef ALLOCA_OPTIMISATIONS
				delete temp;
#endif // !ALLOCA_OPTIMISATIONS
			
			}
		}
	
	}else
	{
	 	btTriangleMesh *triangle = new btTriangleMesh();
		//bttrianglevert
		//triangle->addIndexedMesh();

		size_t size = model.m.LoadedMeshes.size();
		size_t loadedCollisionBoxes = 0;
		for (unsigned int m = 0; m < size; m++)
		{
			if (collisionIdentifierName == nullptr || (model.m.LoadedMeshes[m].MeshName != "" && model.m.LoadedMeshes[m].MeshName.find(collisionIdentifierName) != std::string::npos))
			{
				loadedCollisionBoxes++;
				
				btIndexedMesh mesh;
				mesh.m_numTriangles = model.m.LoadedMeshes[m].Indices.size() / 3;
				mesh.m_numVertices = model.m.LoadedMeshes[m].Vertices.size();
				
				triangeIndexBase = new unsigned char[model.m.LoadedMeshes[m].Indices.size() * sizeof(model.m.LoadedMeshes[m].Indices[0])];
				memcpy(triangeIndexBase, (void*)&model.m.LoadedMeshes[m].Indices[0], model.m.LoadedMeshes[m].Indices.size() * sizeof(model.m.LoadedMeshes[m].Indices[0]));
				mesh.m_triangleIndexBase = triangeIndexBase;
				mesh.m_triangleIndexStride = sizeof(model.m.LoadedMeshes[m].Indices[0]) * 3;


				vertexBase = new unsigned char[model.m.LoadedMeshes[m].Vertices.size() * sizeof(model.m.LoadedMeshes[m].Vertices[0])];
				memcpy(vertexBase, (unsigned char*)&model.m.LoadedMeshes[m].Vertices[0], model.m.LoadedMeshes[m].Vertices.size() * sizeof(model.m.LoadedMeshes[m].Vertices[0]));
				mesh.m_vertexBase = vertexBase;
				mesh.m_vertexStride = sizeof(model.m.LoadedMeshes[m].Vertices[0]);

				triangle->addIndexedMesh(mesh);
			}
		}

		if (loadedCollisionBoxes == 0)
		{
			elog("no collisions detected");
		}

		collisionShape = new btBvhTriangleMeshShape(triangle, 1);
		
	
	}
	
	
	
}

void PhisicalObject::draw()
{
	if (sp != nullptr)
	{
		sp->bind();
	}
	else
	{
		elog("missing shader program!");
	}

	if (camera != nullptr)
	{

		sp->uniform("u_eyePosition", camera->getCurrentViewingPosition().x, camera->getCurrentViewingPosition().y, camera->getCurrentViewingPosition().z);

	} //sets the world to view matrix;
	else
	{
		elog("missing camera!");
	}

	if (lights != nullptr)
	{
		lights->bind(*sp);
	}
	else
	{
		elog("missing light!\n");
	}
	

	sp->uniformi("u_sampl", 0);

	for (unsigned int m = 0; m < objectData.size(); m++)
	{
		objectData[m].material.bind(*sp);

		objectData[m].vb.bind();
		objectData[m].ib.bind();

		objectData[m].va.bind();

		int offset = 0;
		glm::mat4 temp[2];
		for (unsigned int i = 0; i < rigidBodies.size(); i++)
		{
			//btCollisionObject *obj = world->getCollisionObjectArray()[i];
			//btRigidBody * body = btRigidBody::upcast(obj);
			btTransform t;
			//body->getMotionState()->getWorldTransform(t);
			rigidBodies[i]->getMotionState()->getWorldTransform(t);
			glm::mat4 glMatrix;
			t.getOpenGLMatrix((float*)&glMatrix);
			//temp[i * 2] = instances[i].fullTransformMatrix();
			//temp[i * 2 + 1] = instances[i].objectToWorldMatrix();
			
			temp[0] = camera->getProjectionViewMatrix() * glMatrix;
			temp[1] = glMatrix;
			dataTodraw.subData(temp, offset, sizeof(temp));
			//dataTodraw.subData(&instances[i].fullTransformMatrix(), offset, sizeof(glm::mat4));
			//dataTodraw.subData(&instances[i].objectToWorldMatrix(), offset, sizeof(glm::mat4));
			offset += sizeof(glm::mat4);
			offset += sizeof(glm::mat4);
		}


		objectData[m].va.bindForInstances();

		if (objectData[m].texture.id != 0)
		{
			objectData[m].texture.bind(0);
			GLuint temp = sp->getSoubRutineLocation("p_withT");
			glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &temp);
		}else
		{
			GLuint temp = sp->getSoubRutineLocation("p_withoutT");
			glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &temp);
		}

		glDrawElementsInstanced(GL_TRIANGLES, objectData[m].ib.size / sizeof(unsigned int), GL_UNSIGNED_INT, 0, rigidBodies.size());

	}

}

void PhisicalObject::pushElement(glm::vec3 position, glm::vec3 rotation)
{
	rotation = glm::radians(rotation);

	/*
	btTransform t;
	t.setIdentity();
	t.setOrigin({ position.x, position.y, position.z });

	btVector3 inertia = { 0, 0, 0 };
	if (mass != 0.0)
	{
		collisionShape->calculateLocalInertia(mass, inertia);
	}

	btMotionState *motion = new btDefaultMotionState(t);
	btRigidBody *body = new btRigidBody(mass, motion, collisionShape, inertia);
	*/

	//
	if(collisionShape->isCompound())
	{
		size_t loadedCollisionBoxes = ((btCompoundShape*)collisionShape)->getNumChildShapes();

#ifdef ALLOCA_OPTIMISATIONS
		float *masses = (float*)alloca(sizeof(float) * loadedCollisionBoxes);
		for (unsigned int i = 0; i < loadedCollisionBoxes; i++)
		{
			masses[i] = mass / loadedCollisionBoxes; //todo ?
		}

		btTransform t;
		t.setIdentity();
		t.setOrigin({ position.x, position.y, position.z });
		t.setRotation({ rotation.x, rotation.y, rotation.z });
		btVector3 inertia = { 0,0,0 };
		((btCompoundShape*)collisionShape)->calculatePrincipalAxisTransform(masses, t, inertia);
#else // ALLOCA_OPTIMISATIONS
		float *masses = new float[loadedCollisionBoxes]; 
		for (unsigned int i = 0; i < loadedCollisionBoxes; i++)
		{
			masses[i] = mass / loadedCollisionBoxes; //todo ?
		}

		btTransform t;
		t.setIdentity();
		t.setOrigin({ position.x, position.y, position.z });
		t.setRotation({ rotation.x, rotation.y, rotation.z });
		btVector3 inertia = { 0,0,0 };
		((btCompoundShape*)collisionShape)->calculatePrincipalAxisTransform(masses, t, inertia);
		delete[] masses;
#endif // ^ no optimisations

		
	


		t.setIdentity();
		t.setOrigin({ position.x, position.y, position.z});
		t.setRotation({ rotation.x, rotation.y, rotation.z });


		btMotionState *motion = new btDefaultMotionState(t);
		btRigidBody *body = new btRigidBody(mass, motion, collisionShape, inertia);
		//body->setCenterOfMassTransform(t);
		body->setFriction(1);
		body->setRestitution(0);

	
		//
		world->addRigidBody(body);

		rigidBodies.push_back(body);
	
	}else
	{
		btTransform t;
		t.setIdentity();
		t.setOrigin({ position.x, position.y, position.z });
		t.setRotation({ rotation.x, rotation.y, rotation.z });

		btVector3 inertia = { 0, 0, 0 };
	

		btMotionState *motion = new btDefaultMotionState(t);
		btRigidBody *body = new btRigidBody(mass, motion, collisionShape, inertia);
		
		body->setFriction(1);
		//body->setRestitution(0);

		world->addRigidBody(body);

		rigidBodies.push_back(body);
	}

	

	dataTodraw.recreateData(0, sizeof(glm::mat4)*rigidBodies.size() * 2);
}

void PhisicalObject::deleteElement(unsigned int index)
{
	
	auto body = rigidBodies.at(index);
	world->removeRigidBody(body);

	delete body->getMotionState();
	delete body;

	rigidBodies.erase(rigidBodies.begin() + index);
	
	
}

void PhisicalObject::setElementPosition(int index, glm::vec3 position)
{

	//btTransform trans = _body->getWorldTransform();
	//trans.setOrigin(btVector3(position.x, position.y, position.z));
	//_body->setWorldTransform(trans);

	btTransform t;
	//t.setIdentity();
	//t.setOrigin({ position.x, position.y, position.z });
	//rigidBodies[index]->getMotionState()->setWorldTransform(t);

	t = rigidBodies[index]->getWorldTransform();
	t.setOrigin({ position.x, position.y, position.z });
	rigidBodies[index]->setWorldTransform(t);
}

bool PhisicalObject::colidesWith(int thisIndex, PhisicalObject with, int secondIndex)
{
	return colidesWith(thisIndex, with.rigidBodies[secondIndex]);
}

bool PhisicalObject::colidesWith(int thisIndex, btRigidBody * with)
{
	int numManifolds = world->getDispatcher()->getNumManifolds();
	for (int i = 0; i < numManifolds; i++)
	{
		btPersistentManifold* contactManifold = world->getDispatcher()->getManifoldByIndexInternal(i);
		const btCollisionObject* obA = contactManifold->getBody0();
		const btCollisionObject* obB = contactManifold->getBody1();
		auto thiss = rigidBodies[thisIndex];
		if((obA == with || obB == with)&&(obA == thiss || obB == thiss))
		{
			return true;
		}
	}
	return false;
}

void PhisicalObject::appendObject(const LoadedIndexModel & model, AssetManager<Texture> &manager, const glm::vec3 &padding, const char* collisionIdentifierName)
{
	appendObject_(dataTodraw, objectData, model, padding, manager, collisionIdentifierName);
}


void PhisicalObject::cleanup()
{
	// remove the rigidbodies from the dynamics world and delete them
	/*
	for (int i = world->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject * obj = world->getCollisionObjectArray()[i];
		btRigidBody * body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		world->removeCollisionObject(obj);
		delete obj;
	}
	*/

	for (int i = 0; i < rigidBodies.size();/*no increment*/)
	{
		deleteElement(i);
	}

	//if(collisionShape)
	//{
	//	deleteCollisionShape();
		//todo implement
	//}

	dataTodraw.cleanup();
	initialize();
}

void PhisicalObject::gpuCleanup()
{
	for (auto &i : objectData)
	{
		i.ib.cleanup();
		i.vb.cleanup();
		i.va.attributes.clear();
	}

	objectData.clear();
}

void PhisicalObject::deleteCollisionShape()
{
	if(triangeIndexBase)
	{
		delete[] triangeIndexBase;
		triangeIndexBase = nullptr;
	}

	if(vertexBase)
	{
		delete[] vertexBase;
		vertexBase = nullptr;
	}

	if(collisionShape->isCompound())
	{
		size_t loadedCollisionBoxes = ((btCompoundShape*)collisionShape)->getNumChildShapes();
		for(int i=0; i<loadedCollisionBoxes; i++)
		{
			delete ((btCompoundShape*)collisionShape)->getChildShape(i);
		}
	}else
	{
		delete ((btBvhTriangleMeshShape*)collisionShape)->getTriangleInfoMap();
	}

	delete collisionShape;
	//todo: implement
}

