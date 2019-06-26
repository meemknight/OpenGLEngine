#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <GL/glew.h>

#include "Shader.h"
#include "Camera.h"
#include "Light.h"

struct ParticleSystem
{
	ParticleSystem() = default;

	ParticleSystem(unsigned int count, float cicleDuration,
		ShaderProgram &program, glm::vec3 color1, glm::vec3 color2,
		glm::vec3 direction1, glm::vec3 direction2,
		float speed1, float speed2
	);

	ParticleSystem(const char *file)
	{
		loadParticleSystem(file);
	}

	glm::vec3 position = { 0, 0, 0 };

	//there are 2 colors because the object will randomly interpolate between them
	glm::vec3 color1 = { 0, 0, 0 };
	glm::vec3 color2 = { 0, 0, 0 };
	glm::vec3 fadeColor = { 0,0,0 };

	glm::vec3 direction1;
	glm::vec3 direction2;
	float speed1;
	float speed2;

	float fadeWeight = 1;

	void draw(float deltaTime);
	void cleanup();

	glm::vec3 gravity = { 0, -1.5, 0 };
	float scale = 1;

	ShaderProgram sp;
	Camera *camera;
	LightContext *light = nullptr;

	float cicleDuration;
	bool affectedByLight = true;

	float kd = 0.5;

	void buildParticleSystem();

	///This function does not cleanup.
	void loadParticleSystem(const char* name);

	//modifying this might break the program if the particle system is running
	unsigned int count;

	bool running = true;

private:

	glm::vec3 *ParticlePositions;
	glm::vec3 *ParticleDrag;

	GLuint vertexShapeId = 0;
	GLuint vertexPositionId = 0;
	GLuint vertexColorsId = 0;

	int currentParticle = 0;
	float accumulatedAdvance = 0.f;

};