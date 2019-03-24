/////////////////////////////////////////////
//Material.h
//Copyright(c) 2019 Luta Vlad
//https://github.com/meemknight/OpenGLEngine
/////////////////////////////////////////////
#pragma once
#include <glm/glm.hpp>
#include "Shader.h"

///\brief the material class
///
///a shinyness of the value 0 means an invalid material
///and it won't be bound
class Material
{
public:
	Material();
	Material(const glm::vec3 &ka, const glm::vec3 &kd, const glm::vec3 &ks, float shiny):
	ka(ka), kd(kd), ks(ks), shiny(shiny){};

	void bind(ShaderProgram &sp);

	glm::vec3 ka;
	glm::vec3 kd;
	glm::vec3 ks;
	float shiny = 0;

	//http://devernay.free.fr/cours/opengl/materials.html
	//for materials
	static inline Material emerald()		{ return Material(glm::vec3(0.0215f, 0.1745f, 0.0215f), glm::vec3(0.07568, 0.61424, 0.07568), glm::vec3(0.633, 0.727811, 0.633), 0.6f * 128.f); }
	static inline Material jade()			{ return Material(glm::vec3(0.135, 0.2225, 0.1575), glm::vec3(0.54, 0.89, 0.63), glm::vec3(0.316228, 0.316228, 0.316228), 0.1f * 128.f); }
	static inline Material obsidian()		{ return Material(glm::vec3(0.05375, 0.05, 0.06625), glm::vec3(0.18275, 0.17, 0.22525), glm::vec3(0.332741, 0.328634, 0.346435), 0.3f * 128.f); }
	static inline Material pearl()			{ return Material(glm::vec3(0.25,	0.20725,	0.20725), glm::vec3(1,	0.829,	0.829), glm::vec3(0.296648,	0.296648,	0.296648),	0.088f * 128.f); }
	static inline Material ruby()			{ return Material(glm::vec3(0.1745,	0.01175,	0.01175),	glm::vec3(0.61424,	0.04136,	0.04136), glm::vec3(0.727811,	0.626959,	0.626959f),	0.6f* 128.f); }
	static inline Material turquoise()		{ return Material(glm::vec3(0.1,	0.18725,	0.1745), glm::vec3(0.396,	0.74151,	0.69102), glm::vec3(0.297254f,	0.30829f,	0.306678f),	0.1f * 128.f); }
	static inline Material brass()			{return Material(glm::vec3(0.329412,	0.223529,	0.027451), glm::vec3(0.780392f,	0.568627f,	0.113725f), glm::vec3(0.992157f,	0.941176f,	0.807843f),	0.21794872f * 128.f);	 }
	static inline Material bronze()			{return Material(glm::vec3(0.2125f,	0.1275,	0.054), glm::vec3(0.714f,	0.4284f,	0.18144f), glm::vec3(0.393548f,	0.271906f,	0.166721f),	0.2f * 128.f);	 }
	static inline Material chrome()			{return Material(glm::vec3(0.25f,	0.25f,	0.25f), glm::vec3(0.4f,	0.4f,	0.4f), glm::vec3(0.774597,	0.774597f,	0.774597f),	0.6f * 128.f);	 }
	static inline Material copper()			{return Material(glm::vec3(0.19125,	0.0735f,	0.02250f),	glm::vec3(0.7038,	0.27048f,	0.0828),	glm::vec3(0.256777f,	0.137622,	0.086014),	0.1f * 128.f);}
	static inline Material gold()			{return Material(glm::vec3(0.24725,	0.1995f,	0.07450f),	glm::vec3(0.75164,	0.60648f,	0.22648),	glm::vec3(0.628281f,	0.555802f,	0.366065),	0.4f * 128.f);}
	static inline Material silver()			{ return Material(glm::vec3(0.19225f,	0.19225f,	0.19225f),	glm::vec3(0.50754,	0.50754f,	0.50754),	glm::vec3(0.508273f,	0.508273f,	0.508273),	0.4f * 128.f); }
	static inline Material blackPlastic()	{ return Material(glm::vec3(0.0f,	0.0,	0.0),	glm::vec3(0.01,	0.01,	0.01), glm::vec3(0.50,	0.50,	0.50),	.25 * 128.f); }
	static inline Material cyanPlastic()	{ return Material(glm::vec3(0.0f,	0.1,	0.06),	glm::vec3(0.0,	0.50980392,	0.50980392), glm::vec3(0.50196078,	0.50196078f,	0.50196078),	.25f * 128.f); }
	static inline Material greenPlastic()	{ return Material(glm::vec3(0.0f,	0.0,	0.0),	glm::vec3(0.1,	0.35,	0.1),	glm::vec3(0.45f,	0.55,	0.45),	.25f* 128.f); }
	static inline Material redPlastic()		{ return Material(glm::vec3(0.0f,	0.0,	0.0),	glm::vec3(0.5,	0.0,	0.0),	glm::vec3(0.7f,	0.6,	0.6),	.25f* 128.f); }
	static inline Material whitePlastic()	{ return Material(glm::vec3(0.0f,	0.0,	0.0),	glm::vec3(0.55,	0.55,	0.55),	glm::vec3(0.70f,	0.70,	0.70),	.25f* 128.f); }
	static inline Material yellowPlastic()	{ return Material(glm::vec3(0.0f,	0.0,	0.0),	glm::vec3(0.5,	0.5,	0.0),	glm::vec3(0.60f,	0.60,	0.50),	.25f* 128.f); }
	static inline Material blackRubber()	{ return Material(glm::vec3(0.02f,	0.02,	0.02),	glm::vec3(0.01,	0.01,	0.01),	glm::vec3(0.4f,	0.4,	0.4),	.078125f * 128.f); }
	static inline Material cyanRubber()		{ return Material(glm::vec3(0.0f,	0.05,	0.05),	glm::vec3(0.4,	0.5,	0.5),	glm::vec3(0.04f,	0.7,	0.7),	.078125f * 128.f); }
	static inline Material greenRubber()	{ return Material(glm::vec3(0.0f,	0.05,	0.0),	glm::vec3(0.4,	0.5,	0.4),	glm::vec3(0.04f,	0.7,	0.04),	.078125f * 128.f); }
	static inline Material redRubber()		{ return Material(glm::vec3(0.05f,	0.0,	0.0), glm::vec3(0.5,	0.4,	0.4), glm::vec3(0.7f,	0.04,	0.04),	.078125f * 128.f); }
	static inline Material whiteRubber()	{ return Material(glm::vec3(0.05f,	0.05,	0.05), glm::vec3(0.5,	0.5,	0.5), glm::vec3(0.7f, 0.7,	0.7),	.078125f * 128.f); }
	static inline Material yellowRubber()	{ return Material(glm::vec3(0.05f,	0.05,	0.0), glm::vec3(0.5,	0.5,	0.4), glm::vec3(0.7f,	0.7,	0.04),	.078125f * 128.f); }
	static inline Material defaultMaterial(){ return Material(glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.7, 0.7, 0.7), glm::vec3(1, 1, 1.f), 10.f); }
	static inline Material brightMaterial() { return Material(glm::vec3(0.4, 0.4, 0.4), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), 10.f); }
	static inline Material greyMaterial(float ambience, float diffuseness, float specularity, float expoennt) { return Material(glm::vec3(ambience, ambience, ambience), glm::vec3(diffuseness, diffuseness, diffuseness), glm::vec3(specularity, specularity, specularity), expoennt); }
	//static inline Material defaultMaterial() { return Material(glm::vec3(, , ), glm::vec3(, , ), glm::vec3(, , ), ); }
};