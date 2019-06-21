#include "ParticleSystem.h"
#include <random>
#include <functional>
#include <utility>

std::random_device rng;
std::uniform_real_distribution<float> negDist(-2.0, 2.0);
std::uniform_real_distribution<float> upDist(4.0, 10.0);
std::uniform_real_distribution<float> zeroOneDist(0, 1);

float mix(float a, float b, float r)
{
	return a * r + b * (1 - r);
}


static const GLfloat vertexBufferData[] = {
 -0.5f, -0.5f, 0.0f,
 0.5f, -0.5f, 0.0f,
 -0.5f, 0.5f, 0.0f,
 0.5f, 0.5f, 0.0f,
};

ParticleSystem::ParticleSystem(unsigned int count, float cicleDuration, ShaderProgram &sp, glm::vec3 color1, glm::vec3 color2) :color1(color1), color2(color2),count(count), sp(sp), cicleDuration(cicleDuration)
{
	buildParticleSystem();
}

void ParticleSystem::draw(float deltaTime)
{
	float particleDuration = cicleDuration / count;
	float fadvance = deltaTime / particleDuration + accumulatedAdvance;
	int particleAdvance = fadvance;
	accumulatedAdvance = fadvance - particleAdvance;
	
	int overflow = currentParticle + particleAdvance - count;
	int newPosition;

	if(overflow > 0)
	{
		particleAdvance = count - currentParticle;
		newPosition = overflow;
	}else
	{
		newPosition = currentParticle + particleAdvance;
	}

	for(int i = currentParticle; i < currentParticle+particleAdvance; i++)
	{
		ParticlePositions[i] = position;
		ParticleDrag[i].x = negDist(rng);
		ParticleDrag[i].z = negDist(rng);
		ParticleDrag[i].y = upDist(rng);
	
	}

	for(int i=0; i<overflow; i++)
	{
		ParticlePositions[i] = position;
		ParticleDrag[i].x = negDist(rng);
		ParticleDrag[i].z = negDist(rng);
		ParticleDrag[i].y = upDist(rng);

	}

	currentParticle = newPosition;

	
	for(int i=0; i<count; i++)
	{
		ParticlePositions[i] += glm::vec3(ParticleDrag[i]) * deltaTime;
		ParticleDrag[i].y += gravity * deltaTime;
	}


	//shape
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexShapeId);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//positions
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vertexPositionId);
	glBufferData(GL_ARRAY_BUFFER, count * 3 * sizeof(float), ParticlePositions, GL_STREAM_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//colors
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexColorsId);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glVertexAttribDivisor(0, 0);
	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 1);

	sp.bind();
	if(light && affectedByLight)
	{
		light->bind(sp);
		unsigned int u = sp.getSoubRutineLocation("p_withL", GL_VERTEX_SHADER);
		glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &u);
		

	}else
	{
		unsigned int u = sp.getSoubRutineLocation("p_outL", GL_VERTEX_SHADER);
		glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &u);

	}


	sp.uniformi("count", count);
	sp.uniformi("firstPos", currentParticle);
	sp.uniform("u_fadeColor", fadeColor.x, fadeColor.y, fadeColor.z);
	sp.uniform("u_fadeWeight", fadeWeight);
	glm::mat4 position = camera->getObjectToWorld();
	//resetting the rotation
	//projection[0][0] = 1;
	//projection[1][1] = 1;
	//projection[2][2] = 1;
	
	//projection[0][1] = 0;
	//projection[1][0] = 0;
	//projection[0][2] = 0;
	//projection[2][0] = 0;
	//projection[2][1] = 0;
	//projection[1][2] = 0;
	
	glm::mat4 projection = camera->getProjectionMatrix();

	glUniformMatrix4fv(sp.getUniformLocation("projectionMatrix"), 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(sp.getUniformLocation("positionMatrix"), 1, GL_FALSE, &position[0][0]);

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, count);
}

void ParticleSystem::buildParticleSystem()
{
	glGenBuffers(1, &vertexShapeId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexShapeId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

	glGenBuffers(1, &vertexPositionId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexPositionId);
	glBufferData(GL_ARRAY_BUFFER, count * 3 * sizeof(float) , nullptr , GL_STREAM_DRAW);

	glGenBuffers(1, &vertexColorsId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexColorsId);
	
	glm::vec3 *colors;
	colors = new glm::vec3[count];

	for(int i=0; i<count; i++)
	{
		colors[i].r = mix(color1.r, color2.r, zeroOneDist(rng));
		colors[i].g = mix(color1.g, color2.g, zeroOneDist(rng));
		colors[i].b = mix(color1.b, color2.b, zeroOneDist(rng));
	}

	glBufferData(GL_ARRAY_BUFFER, count * sizeof(glm::vec3), colors, GL_STREAM_DRAW);

	delete[] colors;

	ParticlePositions = new glm::vec3[count];
	ParticleDrag = new glm::vec3[count];
	
	for (int i = 0; i < count; i++)
	{
		ParticlePositions[i].x = 0;
		ParticlePositions[i].y = 0;
		ParticlePositions[i].z = 0;
	}

	for(int i=0; i<count; i++)
	{
		ParticleDrag[i].x = negDist(rng);
		ParticleDrag[i].z = negDist(rng);
		ParticleDrag[i].y = upDist(rng);
	}

}

/*
static const GLfloat g_vertex_buffer_data[] = {
 -0.5f, -0.5f, 0.0f,
 0.5f, -0.5f, 0.0f,
 -0.5f, 0.5f, 0.0f,
 0.5f, 0.5f, 0.0f,
};

GLuint billboard_vertex_buffer;
glGenBuffers(1, &billboard_vertex_buffer);
glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

// The VBO containing the positions and sizes of the particles
GLuint particles_position_buffer;
glGenBuffers(1, &particles_position_buffer);
glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
// Initialize with empty (NULL) buffer : it will be updated later, each frame.
glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

// The VBO containing the colors of the particles
GLuint particles_color_buffer;
glGenBuffers(1, &particles_color_buffer);
glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
// Initialize with empty (NULL) buffer : it will be updated later, each frame.
glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
*/