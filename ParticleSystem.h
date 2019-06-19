#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <GL/glew.h>

#include "Shader.h"
#include "Camera.h"
#include "Light.h"

struct ParticleSystem
{
	ParticleSystem(unsigned int count, float cicleDuration, ShaderProgram &program, glm::vec3 color1, glm::vec3 color2);
	glm::vec3 position = { 0, 0, 0 };
	
	//there are 2 colorus because the object will randomly interpolate between them
	glm::vec3 color1 = { 0, 0, 0};
	glm::vec3 color2 = { 0, 0, 0};
	glm::vec3 decayColor = { 0,0,0 };



	void draw(float deltaTime);
	void cleanup();


	float gravity = -1.5;

	ShaderProgram sp;
	Camera *camera;
	LightContext *light;

	float cicleDuration;
	bool affectedByLight = true;

private:
	void buildParticleSystem();

	unsigned int count;

	glm::vec3 *ParticlePositions;
	glm::vec3 *ParticleDrag;

	GLuint vertexShapeId = 0;
	GLuint vertexPositionId = 0;
	GLuint vertexColorsId = 0;
	
	int currentParticle = 0;
	float accumulatedAdvance = 0.f;
};