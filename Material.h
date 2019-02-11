#pragma once
#include <glm/glm.hpp>
#include "Shader.h"

/////////////////////////////////////////////////////////
///\brief the material class
///
///a shinyness of the value 0 means an invalid material
///and it won't be bound
/////////////////////////////////////////////////////////

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
	static inline Material emerald()	{ return Material(glm::vec3(0.0215f, 0.1745f, 0.0215f), glm::vec3(0.07568, 0.61424, 0.07568), glm::vec3(0.633, 0.727811, 0.633), 0.6 * 128.f); }
	static inline Material jade()		{ return Material(glm::vec3(0.135, 0.2225, 0.1575), glm::vec3(0.54, 0.89, 0.63), glm::vec3(0.316228, 0.316228, 0.316228), 0.1 * 128.f); }
	static inline Material obsidian() { return Material(glm::vec3(0.05375, 0.05, 0.06625), glm::vec3(0.18275, 0.17, 0.22525), glm::vec3(0.332741, 0.328634, 0.346435), 0.3 * 128.f); }
	static inline Material pearl() { return Material(glm::vec3(0.25,	0.20725,	0.20725), glm::vec3(1,	0.829,	0.829), glm::vec3(0.296648,	0.296648,	0.296648),	0.088 * 128.f); }
	static inline Material ruby() { return Material(glm::vec3(0.1745,	0.01175,	0.01175),	glm::vec3(0.61424,	0.04136,	0.04136), glm::vec3(0.727811,	0.626959,	0.626959),	0.6 * 128.f); }
	static inline Material turquoise() { return Material(glm::vec3(0.1,	0.18725,	0.1745), glm::vec3(0.396,	0.74151,	0.69102), glm::vec3(0.297254,	0.30829,	0.306678),	0.1 * 128.f); }
	static inline Material brass()			{return Material(glm::vec3(0.329412,	0.223529,	0.027451), glm::vec3(0.780392,	0.568627,	0.113725), glm::vec3(0.992157,	0.941176,	0.807843),	0.21794872 * 128.f);	 }
	static inline Material bronze()			{return Material(glm::vec3(0.2125,	0.1275,	0.054), glm::vec3(0.714,	0.4284,	0.18144), glm::vec3(0.393548,	0.271906,	0.166721),	0.2 * 128.f);	 }
	static inline Material chrome()			{return Material(glm::vec3(0.25,	0.25,	0.25), glm::vec3(0.4,	0.4,	0.4), glm::vec3(0.774597,	0.774597,	0.774597),	0.6 * 128.f);	 }
	static inline Material copper()			{return Material(glm::vec3(0.19125,	0.0735,	0.02250),	glm::vec3(0.7038,	0.27048,	0.0828),	glm::vec3(0.256777,	0.137622,	0.086014),	0.1 * 128.f);}
	static inline Material gold()			{return Material(glm::vec3(0.24725,	0.1995,	0.07450),	glm::vec3(0.75164,	0.60648,	0.22648),	glm::vec3(0.628281,	0.555802,	0.366065),	0.4 * 128.f);}
	static inline Material silver() { return Material(glm::vec3(0.19225,	0.19225,	0.19225),	glm::vec3(0.50754,	0.50754,	0.50754),	glm::vec3(0.508273,	0.508273,	0.508273),	0.4 * 128.f); }
	static inline Material blackPlastic() { return Material(glm::vec3(0.0,	0.0,	0.0),	glm::vec3(0.01,	0.01,	0.01), glm::vec3(0.50,	0.50,	0.50),	.25 * 128.f); }
	static inline Material cyanPlastic() { return Material(glm::vec3(0.0,	0.1,	0.06),	glm::vec3(0.0,	0.50980392,	0.50980392), glm::vec3(0.50196078,	0.50196078,	0.50196078),	.25 * 128.f); }
	static inline Material greenPlastic() { return Material(glm::vec3(0.0,	0.0,	0.0),	glm::vec3(0.1,	0.35,	0.1),	glm::vec3(0.45,	0.55,	0.45),	.25* 128.f); }
	static inline Material redPlastic() { return Material(glm::vec3(0.0,	0.0,	0.0),	glm::vec3(0.5,	0.0,	0.0),	glm::vec3(0.7,	0.6,	0.6),	.25* 128.f); }
	static inline Material whitePlastic() { return Material(glm::vec3(0.0,	0.0,	0.0),	glm::vec3(0.55,	0.55,	0.55),	glm::vec3(0.70,	0.70,	0.70),	.25* 128.f); }
	static inline Material yellowPlastic() { return Material(glm::vec3(0.0,	0.0,	0.0),	glm::vec3(0.5,	0.5,	0.0),	glm::vec3(0.60,	0.60,	0.50),	.25* 128.f); }
	static inline Material blackRubber() { return Material(glm::vec3(0.02,	0.02,	0.02),	glm::vec3(0.01,	0.01,	0.01),	glm::vec3(0.4,	0.4,	0.4),	.078125 * 128.f); }
	static inline Material cyanRubber() { return Material(glm::vec3(0.0,	0.05,	0.05),	glm::vec3(0.4,	0.5,	0.5),	glm::vec3(0.04,	0.7,	0.7),	.078125 * 128.f); }
	static inline Material greenRubber() { return Material(glm::vec3(0.0,	0.05,	0.0),	glm::vec3(0.4,	0.5,	0.4),	glm::vec3(0.04,	0.7,	0.04),	.078125 * 128.f); }
	static inline Material redRubber() { return Material(glm::vec3(0.05,	0.0,	0.0), glm::vec3(0.5,	0.4,	0.4), glm::vec3(0.7,	0.04,	0.04),	.078125 * 128.f); }
	static inline Material whiteRubber() { return Material(glm::vec3(0.05,	0.05,	0.05), glm::vec3(0.5,	0.5,	0.5), glm::vec3(0.7, 0.7,	0.7),	.078125 * 128.f); }
	static inline Material yellowRubber() { return Material(glm::vec3(0.05,	0.05,	0.0), glm::vec3(0.5,	0.5,	0.4), glm::vec3(0.7,	0.7,	0.04),	.078125 * 128.f); }
	static inline Material defaultMaterial() { return Material(glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.7, 0.7, 0.7), glm::vec3(1, 1, 1), 10.f); }
	static inline Material brightMaterial() { return Material(glm::vec3(0.4, 0.4, 0.4), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), 10.f); }
	static inline Material greyMaterial(float ambience, float diffuseness, float specularity, float expoennt) { return Material(glm::vec3(ambience, ambience, ambience), glm::vec3(diffuseness, diffuseness, diffuseness), glm::vec3(specularity, specularity, specularity), expoennt); }
	//static inline Material defaultMaterial() { return Material(glm::vec3(, , ), glm::vec3(, , ), glm::vec3(, , ), ); }
};