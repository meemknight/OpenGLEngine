#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <GL/glew.h>

#include "Shader.h"
#include "Camera.h"

struct ParticleSystem
{
	ParticleSystem(unsigned int count, float cicleDuration, ShaderProgram &program);
	glm::vec3 position = { 0,0,0 };

	void draw(float deltaTime);
	void cleanup();

	glm::vec3 *ParticlePositions;
	glm::vec3 *ParticleDrag;

	float gravity = -1.5;

	ShaderProgram sp;
	Camera *camera;

	float cicleDuration;

private:
	void buildParticleSystem();

	unsigned int count;

	GLuint vertexShapeId = 0;
	GLuint vertexPositionId = 0;
	GLuint vertexColorsId = 0;
	
	int currentParticle = 0;
	float accumulatedTime = 0.f;
};