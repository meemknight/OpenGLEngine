//////////////////////////////
//Light.h
//Copyright(c) 2019 Luta Vlad
//////////////////////////////
#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"

struct Light
{
public:
	Light();
	Light(glm::vec4 position, glm::vec3 ambient, glm::vec3 diffuse ,glm::vec3 specular, float strength):
		position(position), ambient(ambient), diffuse(diffuse), specular(specular), strength(strength){}


	void bind(ShaderProgram &sp);

	///last component of the position determins whether it is a directional or a
	///positional light. 1 means positional and 0 means directional.
	glm::vec4 position;
	
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	///used to determine the distance to shine,   0 means infinite distance
	/// a big number = a small light
	float strength; 

	static Light SunLight() {return Light(glm::vec4{ 0, 0, 0, 1 }, glm::vec3{ 1, 1, 1 }, glm::vec3{ 1, 1, 1 }, glm::vec3{1, 1, 1}, 0.0);}
	static Light roomLight(float d = 0.1f) { {return Light(glm::vec4{ 0, 0, 0, 1 }, glm::vec3{ d, d, d }, glm::vec3{ 1, 1, 1 }, glm::vec3{ 1, 1, 1 }, 0.001f); } }
};

class LightContext
{
	std::vector<glm::vec4> positions;
	std::vector<glm::vec3> ambienteces;
	std::vector<glm::vec3> diffuses;
	std::vector<glm::vec3> speculares;
	std::vector<float> strengthes;
public:
	
	void pushElement(const Light &light);
	void removeElement(int index);

	glm::vec4 &getPosition(int index);
	glm::vec3 &getAmbience(int index);
	glm::vec3 &getDiffuseness(int index);
	glm::vec3 &getSpecularity(int index);
	float &getStrength(int index);


	void bind(ShaderProgram &sp);
};

