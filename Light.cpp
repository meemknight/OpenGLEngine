//////////////////////////////////////////////
//Light.cpp
//Copyright(c) 2019 Luta Vlad
//https://github.com/meemknight/OpenGLEngine
/////////////////////////////////////////////
#include "Light.h"

Light::Light()
{
}

void Light::bind(ShaderProgram & sp)
{
		glUniform4fv(sp.getUniformLocation("u_lightPosition[0]"), 1, &(position[0]));
		glUniform3fv(sp.getUniformLocation("u_lightAmbient[0]"), 1, &(ambient[0]));
		glUniform3fv(sp.getUniformLocation("u_lightDiffuse[0]"), 1, &(diffuse[0]));
		glUniform3fv(sp.getUniformLocation("u_lightSpecular[0]"), 1, &(specular[0]));
		glUniform1f(sp.getUniformLocation("u_lightStrength[0]"), strength);
}

void LightContext::bind(ShaderProgram & sp)
{	
	int size = positions.size();

	glUniform4fv(sp.getUniformLocation("u_lightPosition[0]"), size, (float*)&positions[0]);
	glUniform3fv(sp.getUniformLocation("u_lightAmbient[0]"), size, (float*)&ambienteces[0]);
	glUniform3fv(sp.getUniformLocation("u_lightDiffuse[0]"), size, (float*)&diffuses[0]);
	glUniform3fv(sp.getUniformLocation("u_lightSpecular[0]"), size, (float*)&speculares[0]);
	glUniform1fv(sp.getUniformLocation("u_lightStrength[0]"), size, (float*)&strengthes[0]);
	glUniform1i(sp.getUniformLocation("u_lightCount"), size);
}

void LightContext::pushElement(const Light & light)
{
	positions.push_back(light.position);
	ambienteces.push_back(light.ambient);
	diffuses.push_back(light.diffuse);
	speculares.push_back(light.specular);
	strengthes.push_back(light.strength);
}

void LightContext::removeElement(int index)
{
	positions.erase(positions.begin() + index);
	ambienteces.erase(ambienteces.begin() + index);
	diffuses.erase(diffuses.begin() + index);
	speculares.erase(speculares.begin() + index);
	strengthes.erase(strengthes.begin() + index);
	//todo check
}

glm::vec4 &LightContext::getPosition(int index)
{
	return positions[index];
}

glm::vec3 &LightContext::getAmbience(int index)
{
	return ambienteces[index];
}

glm::vec3 &LightContext::getDiffuseness(int index)
{
	return diffuses[index];
}

glm::vec3 &LightContext::getSpecularity(int index)
{
	return speculares[index];
}

float &LightContext::getStrength(int index)
{
	return strengthes[index];
}

void LightContext::clear()
{
	positions.clear();
	ambienteces.clear();
	diffuses.clear();
	speculares.clear();
	strengthes.clear();
}
