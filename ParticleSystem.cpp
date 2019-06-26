#include "ParticleSystem.h"
#include <random>
#include <functional>
#include <utility>
#include <fstream>

std::random_device rng;
std::uniform_real_distribution<float> negDist(-2.0, 2.0);
std::uniform_real_distribution<float> upDist(4.0, 10.0);
std::uniform_real_distribution<float> zeroOneDist(0, 1);

#define R(x, y) x.read((char*)&y, sizeof(y)) 


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

ParticleSystem::ParticleSystem(unsigned int count, float cicleDuration, ShaderProgram &sp, glm::vec3 color1, glm::vec3 color2,
	glm::vec3 direction1, glm::vec3 direction2,
	float speed1, float speed2) :
	color1(color1), color2(color2), count(count), sp(sp),
	cicleDuration(cicleDuration), direction1(direction1),
	direction2(direction2), speed1(speed1), speed2(speed2)
{
	buildParticleSystem();
}


void ParticleSystem::draw(float deltaTime)
{
	if (running)
	{
		std::uniform_real_distribution<float> xDist(direction1.x, direction2.x);
		std::uniform_real_distribution<float> yDist(direction1.y, direction2.y);
		std::uniform_real_distribution<float> zDist(direction1.z, direction2.z);
		std::uniform_real_distribution<float> speedDist(speed1, speed2);

		float particleDuration = cicleDuration / count;
		float fadvance = deltaTime / particleDuration + accumulatedAdvance;
		int particleAdvance = fadvance;
		accumulatedAdvance = fadvance - particleAdvance;

		int overflow = currentParticle + particleAdvance - count;
		int newPosition;

		if (overflow > 0)
		{
			particleAdvance = count - currentParticle;
			newPosition = overflow;
		}
		else
		{
			newPosition = currentParticle + particleAdvance;
		}

		for (int i = currentParticle; i < currentParticle + particleAdvance; i++)
		{
			ParticlePositions[i] = position;
			ParticleDrag[i].x = xDist(rng);
			ParticleDrag[i].y = yDist(rng);
			ParticleDrag[i].z = zDist(rng);
			ParticleDrag[i] = glm::normalize(ParticleDrag[i]);
			ParticleDrag[i] *= speedDist(rng);
		}

		for (int i = 0; i < overflow; i++)
		{
			ParticlePositions[i] = position;
			ParticleDrag[i].x = xDist(rng);
			ParticleDrag[i].y = yDist(rng);
			ParticleDrag[i].z = zDist(rng);
			ParticleDrag[i] = glm::normalize(ParticleDrag[i]);
			ParticleDrag[i] *= speedDist(rng);
		}

		currentParticle = newPosition;

		for (int i = 0; i < count; i++)
		{
			ParticlePositions[i] += glm::vec3(ParticleDrag[i]) * deltaTime;
			ParticleDrag[i] += gravity * deltaTime;
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
		if (light && affectedByLight)
		{
			light->bind(sp);
			unsigned int u = sp.getSoubRutineLocation("p_withL", GL_VERTEX_SHADER);
			glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &u);


		}
		else
		{
			unsigned int u = sp.getSoubRutineLocation("p_outL", GL_VERTEX_SHADER);
			glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &u);

		}

		sp.uniformi("count", count);
		sp.uniformi("firstPos", currentParticle);
		sp.uniform("u_fadeColor", fadeColor.x, fadeColor.y, fadeColor.z);
		sp.uniform("u_fadeWeight", fadeWeight);
		sp.uniform("u_scale", scale);
		sp.uniform("u_kd", kd);
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

}

void ParticleSystem::cleanup()
{
	glDeleteBuffers(1, &vertexShapeId);
	glDeleteBuffers(1, &vertexPositionId);
	glDeleteBuffers(1, &vertexColorsId);

	delete[] ParticlePositions;
	delete[] ParticleDrag;

	currentParticle = 0;
	accumulatedAdvance = 0.f;
}

void ParticleSystem::buildParticleSystem()
{
	currentParticle = 0;
	accumulatedAdvance = 0.f;

	glGenBuffers(1, &vertexShapeId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexShapeId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

	glGenBuffers(1, &vertexPositionId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexPositionId);
	glBufferData(GL_ARRAY_BUFFER, count * 3 * sizeof(float), nullptr, GL_STREAM_DRAW);

	glGenBuffers(1, &vertexColorsId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexColorsId);

	glm::vec3 *colors;
	colors = new glm::vec3[count];

	for (int i = 0; i < count; i++)
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

	std::uniform_real_distribution<float> xDist(direction1.x, direction2.x);
	std::uniform_real_distribution<float> yDist(direction1.y, direction2.y);
	std::uniform_real_distribution<float> zDist(direction1.z, direction2.z);
	std::uniform_real_distribution<float> speedDist(speed1, speed2);


	for (int i = 0; i < count; i++)
	{
		ParticleDrag[i].x = xDist(rng);
		ParticleDrag[i].y = yDist(rng);
		ParticleDrag[i].z = zDist(rng);
		ParticleDrag[i] = glm::normalize(ParticleDrag[i]);
		ParticleDrag[i] *= speedDist(rng);
	}

}

void ParticleSystem::loadParticleSystem(const char * name)
{

	std::ifstream f(name, std::ios::in | std::ios::binary);

	if (!f.is_open())
	{
		elog("couldn't open file");
		return;
	}

	R(f, this->color1);
	R(f, this->color2);
	R(f, this->fadeColor);
	R(f, this->direction1);
	R(f, this->direction2);
	R(f, this->speed1);
	R(f, this->speed2);
	R(f, this->fadeWeight);
	R(f, this->gravity);
	R(f, this->scale);
	R(f, this->cicleDuration);
	R(f, this->affectedByLight);
	R(f, this->kd);
	R(f, this->count);

	this->buildParticleSystem();

	f.close();


}

#undef R