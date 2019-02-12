//////////////////////////////
//Copyright(c) 2019 Luta Vlad
//////////////////////////////

#pragma once
#include "indexBuffer.h"
#include "vertexBuffer.h"
#include "vertexAttribute.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "objLoader.h"
#include "Material.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "AssetManager.h"
#include <btBulletDynamicsCommon.h>
#include "Light.h"

struct LoadedIndexModel
{
	LoadedIndexModel() {}

	///this object should not be deleted if used with a collision object
	explicit LoadedIndexModel(const char* c) { m.LoadFile(c); }
	LoadedIndexModel(objl::Loader m) :m(m) {}
	objl::Loader m;
};

class ObjectPosition
{
	float x = 0, y = 0, z = 0;
	float rx = 0, ry = 0, rz = 0;
	float scale = 1;
	bool modified = 1;
	
public:
	glm::mat4 _objectToWorldMatrix;

	ObjectPosition() = default;
	explicit ObjectPosition(glm::mat4 om)noexcept :_objectToWorldMatrix(om) { modified = 0; }
	explicit ObjectPosition(float x, float y, float z)noexcept : x(x), y(y), z(z) { modified = 1; }


	//glm::mat4 fullTransformMatrix()
	//{
	//	return glm::mat4(worldToViexMatrix * objectToWorldMatrix()); //?
	//}

	void setPosition(float x, float y, float z)
	{
		ObjectPosition::x = x;
		ObjectPosition::y = y;
		ObjectPosition::z = z;
		modified = 1;
	}

	/// @brief
	/// sets the roataion, in degrees
	void setRotation(float x, float y, float z)
	{
		rx = x;
		ry = y;
		rz = z;
		modified = 1;
	}

	void setScale(float x)
	{
		scale = x;
		modified = 1;
	}

	void addScale(float x)
	{
		scale += x;
		modified = 1;
	}


	glm::mat4 objectToWorldMatrix();

};

struct ObjectData
{
	Material material;
	vertexBuffer vb;
	vertexAttribute va;
	indexBuffer ib;
	Texture texture = 0;
};

class GameObject
{
	void initialize();
	Material material;
protected:
	///used to specify coordonates of each object
	vertexBuffer dataTodraw;

public:


	std::vector<ObjectPosition> instances;

	GameObject() { initialize(); }
	GameObject(vertexBuffer vb, indexBuffer ib, vertexAttribute va, ShaderProgram *sp, Camera *camera = nullptr) : vb(vb), va(va), ib(ib), sp(sp), camera(camera) { initialize(); };

	///just a level of abstractization that allows the user to pass both a indexed model and a file name
	

	//GameObject(LoadedIndexModel &model, ShaderProgram sp, Camera *c = nullptr);

	void loadPtn323(const LoadedIndexModel &model, ShaderProgram *sp); //todo optimise refference
	void loadPcn333(const LoadedIndexModel &model, ShaderProgram *sp);

	vertexBuffer vb;
	vertexAttribute va;
	indexBuffer ib;
	ShaderProgram *sp = nullptr;
	Camera *camera = nullptr;

	Material getMaterial();
	Material &getMaterialReffernce();
	void setMaterial(const Material &m);
	

	//int timeUniformLocation;

	ObjectPosition &getInstance(int index) { return instances[index]; }

	void draw();
	void pushElement(glm::mat4 matrix = glm::mat4(0));

};

class ComplexObject
{
	///used to specify coordonates of each object
	vertexBuffer dataTodraw;
	glm::mat4 worldToViexMatrix = glm::mat4(0);


	void initialize();

public:
	ComplexObject() = default;
	 ComplexObject(Camera *c, ShaderProgram *sp, LightContext *lights) :
	 camera(c), sp(sp), lights(lights){}



	std::vector<ObjectData> objectData;

	std::vector<ObjectPosition> instances;
	Camera *camera = nullptr;
	ShaderProgram *sp = nullptr; 
	LightContext *lights = nullptr;

	void loadPtn323(const LoadedIndexModel &model, AssetManager &manager, const char* collisionIdentifierName = "COLLISION");

	void draw();
	void pushElement(glm::mat4 matrix = glm::mat4(0));
	void deleteElement(int index); //todo test
	ObjectPosition &getInstance(int index) { return instances[index]; }
	void appendObject(const LoadedIndexModel &model, AssetManager &manager ,const glm::vec3 &padding = { 0, 0, 0 }, const char* collisionIdentifierName = "COLLISION");
};

class PhisicalObject
{
	using collisionShapeType = btCollisionShape;
	///used to specify coordonates of each object
	vertexBuffer dataTodraw;


	void initialize();

public:
	PhisicalObject() = default;
	PhisicalObject(Camera *c, ShaderProgram *sp, LightContext *lights, btDynamicsWorld *world, collisionShapeType* collisionShape, float mass):
		collisionShape(collisionShape), mass(mass), camera(c), sp(sp), lights(lights), world(world){}

	std::vector<ObjectData> objectData;
	
	//btCollisionShape *collisionShape = 0;
	collisionShapeType *collisionShape = 0;
	std::vector<btRigidBody*> rigidBodies;
	
	///should be const
	float mass = 0; 

	Camera *camera = nullptr;
	ShaderProgram *sp = nullptr;
	LightContext *lights = nullptr;
	btDynamicsWorld *world = nullptr;
	

	void loadPtn323(const LoadedIndexModel &model, AssetManager &manager);
	void loadCollisionBox(const LoadedIndexModel &model, const char* collisionIdentifierName = "COLLISION");

	void draw();
	void pushElement(glm::vec3 position = {0,0,0});
	void deleteElement(int index); //todo test
	
	void setElementPosition(int index, glm::vec3 position);
	void aplyForce(int index);

	btRigidBody* getIndtance(int index) { return rigidBodies[index]; }

	//todo make getters for positions

	void appendObject(const LoadedIndexModel &model, AssetManager &manager, const glm::vec3 &padding = { 0, 0, 0 }, const char* collisionIdentifierName = "COLLISION");
	
	void cleanUp();
	void deleteCollisionShape();
};