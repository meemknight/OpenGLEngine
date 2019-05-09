#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <GL/glew.h>

#include "Shader.h"
#include "Camera.h"

struct ParticleSystem
{
	ParticleSystem(unsigned int count, ShaderProgram &program);
	glm::vec3 position = { 0,0,0 };

	void draw();
	void cleanup();

	glm::vec3 *ParticlePositions;
	glm::vec4 *ParticleDrag; // the last element is the gravity
	
	ShaderProgram sp;
	Camera *camera;

private:
	void buildParticleSystem();

	unsigned int count = 1;

	GLuint vertexShapeId = 0;
	GLuint vertexPositionId = 0;
	GLuint vertexColorsId = 0;
	


};