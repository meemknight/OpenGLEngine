#include <iostream>
#include <vector>
#include <Windows.h>
#include <cmath>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
//#include <BulletSoftBody/btSoftRigidDynamicsWorld.h>
#include <BulletDynamics/Character/btCharacterControllerInterface.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>

#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "GameObject.h"
#include "Light.h"
#include "custumBulletdebuggClass.h"
#include "shapesGenerator.h"
#include "GameObjectPool.h"

#include "tools.h"

extern "C"
{
	//Enable dedicated graphics
	//__declspec(dllexport) DWORD NvOptimusEnablement = true;
	//__declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = true;
}

float width = 1280;
float height = 720;

using glm::mat4;

btDynamicsWorld *world;
btDispatcher *dispatcher;
btBroadphaseInterface *broadPhase;
btConstraintSolver *solver;
btCollisionConfiguration *collisionConfiguration;

btRigidBody addSphere(float rad, float x, float y, float z, float mass)
{
	btTransform t;
	t.setIdentity();
	t.setOrigin({ x, y, z });

	btSphereShape *sphere = new btSphereShape(rad);
	btVector3 inertia = { 0,0,0 };
	if (mass != 0.0)
	{
		sphere->calculateLocalInertia(mass, inertia);
	}
	btMotionState *motion = new btDefaultMotionState(t);
	
	//btRigidBody::btRigidBodyConstructionInfo info(mass, motion, sphere, inertia);
	btRigidBody body(mass, motion, sphere, inertia);
	
	return body;
}


int main()
{

	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	broadPhase = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();

	world = new btDiscreteDynamicsWorld(dispatcher, broadPhase, solver, collisionConfiguration);
	world->setGravity({ 0, -9.81f, 0 });
	

	btTransform t;
	t.setIdentity();
	t.setOrigin({0, -1, 0});
	
	btStaticPlaneShape *plane = new btStaticPlaneShape({0,1,0}, 0);
	btMotionState *motion =new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(0.0f, motion, plane);
	btRigidBody body(info);

	world->addRigidBody(&body);

	auto sphere = addSphere(1, -6, 2, -6, 10);
	world->addRigidBody(&sphere);
	//sphere.applyImpulse({ 10,0,0 }, { 0,0,0 });


	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;
	contextSettings.stencilBits = 8;
	contextSettings.antialiasingLevel = 2;
	//contextSettings.majorVersion = 3;
	//contextSettings.minorVersion = 3;

	sf::RenderWindow window(sf::VideoMode(width, height), "glEngine", sf::Style::Default, contextSettings);

	auto windoHandle = window.getSystemHandle();

	//window.setVerticalSyncEnabled(1);

	glewInit();
	glewExperimental = GL_TRUE;
	glEnable(GL_DEPTH_TEST);
	//glBlendFunc(GL_DST_COLOR, GL_ZERO);

#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
#endif
	
	glEnable(GL_CULL_FACE);



	float cube2[] = {
	-1.0f, +1.0f, +1.0f, // 0
	+1.0f, +0.0f, +0.0f, // Color
	+1.0f, +1.0f, +1.0f, // 1
	+1.0f,  0.0f, +0.0f, // Color
	+1.0f, +1.0f, -1.0f, // 2
	+1.0f, +0.0f, +0.0f, // Color
	-1.0f, +1.0f, -1.0f, // 3
	+1.0f, +0.0f, +0.0f, // Color
	-1.0f, +1.0f, -1.0f, // 4
	+0.0f, +1.0f, +0.0f, // Color
	+1.0f, +1.0f, -1.0f, // 5
	+0.0f, +1.0f, +0.0f, // Color
	+1.0f, -1.0f, -1.0f, // 6
	+0.0f, +1.0f, +0.0f, // Color
	-1.0f, -1.0f, -1.0f, // 7
	+0.0f, +1.0f, +0.0f, // Color
	+1.0f, +1.0f, -1.0f, // 8
	+0.0f, +0.0f, +1.0f, // Color
	+1.0f, +1.0f, +1.0f, // 9
	+0.0f, +0.0f, +1.0f, // Color
	+1.0f, -1.0f, +1.0f, // 10
	+0.0f, +0.0f, +1.0f, // Color
	+1.0f, -1.0f, -1.0f, // 11
	+0.0f, +0.0f, +1.0f, // Color
	-1.0f, +1.0f, +1.0f, // 12
	+1.0f, +1.0f, +0.0f, // Color
	-1.0f, +1.0f, -1.0f, // 13
	+1.0f, +1.0f, +0.0f, // Color
	-1.0f, -1.0f, -1.0f, // 14
	+1.0f, +1.0f, +0.0f, // Color
	-1.0f, -1.0f, +1.0f, // 15
	+1.0f, +1.0f, +0.0f, // Color
	+1.0f, +1.0f, +1.0f, // 16
	+0.0f, +1.0f, +1.0f, // Color
	-1.0f, +1.0f, +1.0f, // 17
	+0.0f, +1.0f, +1.0f, // Color
	-1.0f, -1.0f, +1.0f, // 18
	+0.0f, +1.0f, +1.0f, // Color
	+1.0f, -1.0f, +1.0f, // 19
	+0.0f, +1.0f, +1.0f, // Color
	+1.0f, -1.0f, -1.0f, // 20
	+1.0f, +0.0f, +1.0f, // Color
	-1.0f, -1.0f, -1.0f, // 21
	+1.0f, +0.0f, +1.0f, // Color
	-1.0f, -1.0f, +1.0f, // 22
	+1.0f, +0.0f, +1.0f, // Color
	+1.0f, -1.0f, +1.0f, // 23
	+1.0f, +0.0f, +1.0f, // Color
	};

	unsigned int cubeIndices[] = {
	0,   1,  2,  0,  2,  3, // Top
	4,   5,  6,  4,  6,  7, // Front
	8,   9, 10,  8, 10, 11, // Right
	12, 13, 14, 12, 14, 15, // Left
	16, 17, 18, 16, 18, 19, // Back
	20, 22, 21, 20, 23, 22, // Bottom
	};

	AssetManager<Texture> textureManager;
	AssetManager<LoadedIndexModel> modelManager;
	LightContext light;

	Camera camera(85.f, &width, &height, 0.01f, 1500.f);
	camera.mSpeed = 16.0f;

	camera.position = { 0, 3, -4 };
	//camera.viewDirection = { 0, 0, 1 };
	///
	camera.firstPersonCamera = 1;
	camera.distanceFromPlayer = 8;
	camera.cameraAngle = glm::radians(25.f);
	camera.topDownAngle = 3.141;


	ShaderProgram program(VertexShader("vertex.vert"), FragmentShader("fragment.frag"));
	ShaderProgram normalProgram(VertexShader("vertn.vert"), FragmentShader("fragn.frag"));
	ShaderProgram textureProgram(VertexShader("vertt.vert"), FragmentShader("fragt.frag"));
	ShaderProgram debugShader(VertexShader("debugShader.vert"), FragmentShader("debugShader.frag"));
	
	custumBulletdebuggClass debugDrawer(&debugShader ,&camera);

	world->setDebugDrawer(&debugDrawer);
	world->getDebugDrawer()->setDebugMode(btIDebugDraw::DebugDrawModes::DBG_DrawWireframe);

	GameObjectPool gameObjectPool;
	gameObjectPool.initialize(&textureProgram, &camera, &light, world, &textureManager, &modelManager);
	gameObjectPool.load("maps//map1.txt");

	//gameObjectPool.phisicalObjectVector.getElementById(250).objectData[0].material = Material::ruby();

	//GameObject tempObject(&textureProgram, &camera, &light);
	//tempObject.loadPtn323()

	float *planVertexes = 0;
	float *planVertexes2 = 0;

	unsigned int *planIndices = 0;
	unsigned int *planIndices2 = 0;

	int plansize = 0;
	int plansize2 = 0;
	int planIndicessize = 0;
	int planIndicessize2 = 0;


	//generateMountains(&planVertexes2, &planIndices2, 2, plansize2, planIndicessize2);
	shapeGenerator::generatePlane(&planVertexes, &planIndices, 512, plansize, planIndicessize);
	std::cout << glGetString(GL_VERSION);


	indexBuffer ib(cubeIndices, sizeof(cubeIndices));

	

	light.pushElement(Light::roomLight());
	light.pushElement(Light::roomLight(0.3));
	//light.pushElement(Light::SunLight());
	//light.getAmbience(0)  = glm::vec3(0.5, 0.1, 0.1);
	//light.getDiffuseness(0)  = glm::vec3(1.f, 0.4, 0.4);
	//light.getSpecularity(0) = glm::vec3(1.0, 0.2, 0.2);
	//light.getStrength(0) = 0.0003;
	light.getPosition(1).y = 20;
	light.getStrength(1) = 0.0003;


	//ComplexObject o2;
	//o2.camera = &camera;
	//o2.loadPtn323("objects//fireMonkey.obj", textureProgram, &manager);
	//o2.pushElement();
	//o2.getInstance(0).setPosition(0, 10, 0);

	GameObject lightObject;
	lightObject.setData(vertexBuffer(cube2, sizeof(cube2)), indexBuffer(cubeIndices, sizeof(cubeIndices)), vertexAttribute({ 3,3 }), &program, &camera);
	lightObject.pushElement(glm::mat4(0));
	glm::vec3 lightPosition = { 1, 1, -5 };

	GameObject plan(vertexBuffer(planVertexes, plansize * 4), indexBuffer(planIndices, planIndicessize * 4), vertexAttribute({ 3,3,3 }), &normalProgram, &camera);
	plan.pushElement(glm::mat4(0));
	plan.getInstance(0).setPosition(0, -1, 0);
	plan.getInstance(0).setRotation(0, 0, 0);
	plan.setMaterial(Material::greyMaterial(1, 0.5f, 0.01f, 1));


	sf::Clock c;
	sf::Clock fpsClock;
	bool updatemouse = 0;
	int frames = 0;
	//window.setMouseCursorVisible(0);

	PhisicalObject playerObject(&camera, &textureProgram, &light, world, nullptr/*new btSphereShape(1)*/, 10);
	//playerObject.loadCollisionBox("objects//fireMonkey.obj", nullptr);
	//playerObject.loadPtn323("objects//fireMonkey.obj", manager);
	playerObject.loadCollisionBox(modelManager.getData("objects//sphere.obj"), nullptr);
	playerObject.loadPtn323(modelManager.getData("objects//sphere.obj"), textureManager);
	//playerObject.appendObject(lmodel, manager, {0, 0, 3});

	float playerAngle = 0;
	float playerRotationSpeed = glm::radians(120.f);

	//playerObject.objectData[0].material = Material::emerald();
	//playerObject.objectData[0].texture = manager.getTexture("textures//cobble.jpg");

	playerObject.rigidBodies.reserve(2);

	
	playerObject.pushElement({ 0, 3 ,0 });

	for(int i =0; i< 20; i++)
	{
		//playerObject.pushElement({ 1, 100 + i * 3 ,1 });
	
	}

	
	//playerObject.getIndtance(0)->setFriction(0.5);

	
	

	//playerObject.getIndtance(0)->setCollisionFlags(playerObject.getIndtance(0)->getCollisionFlags() |
	//btCollisionObject::CF_KINEMATIC_OBJECT);
	//playerObject.getIndtance(0)->setActivationState(DISABLE_DEACTIVATION);


	window.setTitle((char*)glGetString(GL_RENDERER));
	while (window.isOpen())
	{

		float deltatime = c.restart().asSeconds();
		frames++;
		if (fpsClock.getElapsedTime().asSeconds() >= 1)
		{
			float time = fpsClock.restart().asSeconds();
			sf::String t;
			time = frames / time;
			char c[12];
			sprintf(c, "%f", time);
			window.setTitle(c);
			frames = 0;
		}


		//glClearColor(0.1, 0.5, 1.0, 1.0);
		glViewport(0, 0, width, height);

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				//std::cin.get();
				exit(0);
			}
			else
				if (event.type == sf::Event::Resized)
				{
					width = window.getSize().x;
					height = window.getSize().y;

				}
				else
					if (event.type == sf::Event::MouseLeft)
					{
						updatemouse = 0;
					}
					else
						if (event.type == sf::Event::MouseEntered)
						{
							updatemouse = 1;
							camera.oldMousePosition = { sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y };
						}

		}

#pragma region keys
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Escape)))
		{
			exit(0);
			//ShowWindow((HWND)(windoHandle), SW_MINIMIZE);
			//SendMessage((HWND)windoHandle, WM_KILLFOCUS, 0, 0);
			//updatemouse = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			camera.moveFront(deltatime);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			camera.moveBack(deltatime);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			camera.moveLeft(deltatime);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			camera.moveRight(deltatime);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			camera.moveUp(deltatime);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			camera.moveDown(deltatime);
		}

		//
		float lightSpeed = 4.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		{
			lightPosition.y += lightSpeed * deltatime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			lightPosition.y -= lightSpeed * deltatime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			lightPosition.z += lightSpeed * deltatime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			lightPosition.z -= lightSpeed * deltatime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			lightPosition.x += lightSpeed * deltatime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			lightPosition.x -= lightSpeed * deltatime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
		{
			camera.cameraAngle += glm::radians(25.f) * deltatime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
		{
			camera.cameraAngle -= glm::radians(25.f) * deltatime;
		}

		

		if (updatemouse)
		{
			camera.mouseUpdate({ (float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y });
			//sf::Mouse::setPosition(sf::Vector2i(width / 2, height / 2), window);
			//camera.oldMousePosition = { (int)sf::Mouse::getPosition(window).x, (int)sf::Mouse::getPosition(window).y };
			//todo: fix this >_<     this should make the mouse stay in the centre
		}

		if (window.hasFocus())
		{
			//window.setMouseCursorVisible(0);
		}
		else
		{
			//window.setMouseCursorVisible(1);
		}
		 float maxSpeed = 30000 * deltatime;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			//auto v = playerObject.getIndtance(0)->getLinearVelocity();
			//v.setZ(6);
			//playerObject.getIndtance(0)->setLinearVelocity(v);
			playerObject.getIndtance(0)->applyCentralForce({ 0,0,-maxSpeed * cos(playerAngle) });
			playerObject.getIndtance(0)->applyCentralForce({ -maxSpeed * sin(playerAngle), 0, 0 });
			playerObject.getIndtance(0)->activate(1);

			//auto s = playerObject.getIndtance(0)->getMotionState();
			//btTransform t; 
			//btVector3 move = { 0,0,0.006 };
			//s->getWorldTransform(t);
			//t.setOrigin( t.getOrigin() + move * deltatime);
			//s->setWorldTransform(t);

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		{
			//auto v = playerObject.getIndtance(0)->getLinearVelocity();
			//v.setZ(-6);
			//playerObject.getIndtance(0)->setLinearVelocity(v);
			playerObject.getIndtance(0)->applyCentralForce({ 0,0,maxSpeed * cos(playerAngle) });
			playerObject.getIndtance(0)->applyCentralForce({ maxSpeed * sin(playerAngle), 0, 0 });
			playerObject.getIndtance(0)->activate(1);

			//auto s = playerObject.getIndtance(0)->getMotionState();
			//btTransform t;
			//btVector3 move = { 0,0,-0.006 };
			//s->getWorldTransform(t);
			//t.setOrigin(t.getOrigin() + move * deltatime);
			//s->setWorldTransform(t);

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		{
			//auto v = playerObject.getIndtance(0)->getLinearVelocity();
			//v.setX(6);
			//playerObject.getIndtance(0)->setLinearVelocity(v);
			
			playerObject.getIndtance(0)->applyCentralForce({ -maxSpeed * cos(playerAngle),0,0 });
			playerObject.getIndtance(0)->applyCentralForce({ 0,0, maxSpeed * sin(playerAngle) });
			playerObject.getIndtance(0)->activate(1);

			//auto s = playerObject.getIndtance(0)->getMotionState();
			//btTransform t;
			//btVector3 move = { 0.006,0,0 };
			//s->getWorldTransform(t);
			//t.setOrigin(t.getOrigin() + move * deltatime);
			//s->setWorldTransform(t);
			

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		{
			//auto v = playerObject.getIndtance(0)->getLinearVelocity();
			//v.setX(-6);
			//playerObject.getIndtance(0)->setLinearVelocity(v);
			
			playerObject.getIndtance(0)->applyCentralForce({ maxSpeed * cos(playerAngle),0,0 });
			playerObject.getIndtance(0)->applyCentralForce({ 0,0,maxSpeed * -sin(playerAngle) });
			playerObject.getIndtance(0)->activate(1);


			//auto s = playerObject.getIndtance(0)->getMotionState();
			//btTransform t;
			//btVector3 move = { -0.006,0,0 };
			//s->getWorldTransform(t);
			//t.setOrigin(t.getOrigin() + move * deltatime);
			//s->setWorldTransform(t);

		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			playerAngle += playerRotationSpeed * deltatime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		{
			playerAngle -= playerRotationSpeed * deltatime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			playerObject.getIndtance(0)->applyCentralForce({ 0,maxSpeed*2,0 });
			playerObject.getIndtance(0)->activate(1);
		}

		auto v = playerObject.getIndtance(0)->getLinearVelocity();
		const int maxVelocity = 6;
		if (v.getZ() > maxVelocity) { v.setZ(maxVelocity); }
		if (v.getZ() < -maxVelocity) { v.setZ(-maxVelocity); }
		if (v.getX() > maxVelocity) { v.setX(maxVelocity); }
		if (v.getX() < -maxVelocity) { v.setX(-maxVelocity); }
		playerObject.getIndtance(0)->setLinearVelocity(v);
#pragma endregion

		
		light.getPosition(0) = glm::vec4(lightPosition, 1);
		//light.getPosition(1) = glm::vec4(lightPosition.x, lightPosition.y - 4, lightPosition.z, 1);		

		btTransform tr;
		//tr.setIdentity();
		//tr.setOrigin({0, 2, 0});
		//sphere.setLinearVelocity({ 0.2f * deltatime, 0, 0 });
		//sphere.applyForce({ 0.2f*deltatime, 0, 0}, {0,0,0}); 
		//sphere.setWorldTransform(tr);
		sphere.getMotionState()->getWorldTransform(tr);

		glm::vec3 playerPos;
		btTransform playerTransform;
		playerObject.getIndtance(0)->getMotionState()->getWorldTransform(playerTransform);
		playerObject.getIndtance(0)->setWorldTransform(playerTransform);
		playerPos = { playerTransform.getOrigin().x(), playerTransform.getOrigin().y(), playerTransform.getOrigin().z() };
		
		//auto pos = playerObject.getIndtance(0)->getCenterOfMassPosition();
		//playerPos = { pos.getX(), pos.getY(), pos.getZ() };

		camera.playerPosition = playerPos;
		camera.topDownAngle = playerAngle;
		playerObject.draw();
		

		gameObjectPool.drawAll();

		//gameObjectPool.clearAll();
		//gameObjectPool.load("maps//map1.txt");

		lightObject.sp->uniform("u_ambience", 1, 1, 1);

		lightObject.getInstance(0).setPosition(lightPosition.x, lightPosition.y, lightPosition.z);
		lightObject.getInstance(0).setScale(0.1f);

		lightObject.draw();

		world->stepSimulation(deltatime);


		//world->debugDrawWorld();

		plan.draw();

		window.pushGLStates();
		//glDisable(GL_DEPTH_TEST);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindVertexArray(0);
		//glBindTexture(GL_TEXTURE_2D, 0);
		//glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		for(int i=0; i<2; i++)
		{
			glDisableVertexAttribArray(i);
		}
		//glUseProgram(0);
		//window.resetGLStates();

		//glViewport(0, 0, width, height);
		sf::RectangleShape s({ 100,100 });
		s.setPosition({ 100, 100 });

		s.setFillColor(sf::Color::Green);
		window.draw(s);
		window.display();

		window.popGLStates();
		//glEnable(GL_DEPTH_TEST);
		
		/*window.pushGLStates();
		sf::Text text;
		text.setString("lol");
		text.setFillColor(sf::Color(255, 255, 255, 170));
		text.setPosition(250.f, 450.f);
		window.draw(text);
		window.popGLStates();
		*/

		//draw opengl here

		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindVertexArray(0);
		//glBindTexture(GL_TEXTURE_2D, 0);
		//glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		//glUseProgram(0);

		
		//glDisable(GL_DEPTH_TEST);
		
	
		//window.display();
		

	}

	/*
	playerObject.cleanup();

	world->removeCollisionObject(&body);
	delete body.getMotionState();
	delete body.getCollisionShape();

	world->removeCollisionObject(&sphere);
	delete sphere.getMotionState();
	delete body.getCollisionShape();

	delete dispatcher;
	delete collisionConfiguration;
	delete solver;
	delete broadPhase;
	delete world;

	textureManager.cleanUp();
	modelManager.cleanUp();
	*/
	return 0;
}


