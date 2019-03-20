//////////////////////////////
//Copyright(c) 2019 Luta Vlad
//////////////////////////////
#pragma once
#include <glm/glm.hpp>
#include <sfml/Graphics.hpp>

///This class allows the controll of the first player camera using the mouse movement.
class CharacterMouseController
{
	glm::vec2 lastMousePos;
	bool hasUpdatedLastFrame;
public:
	CharacterMouseController() {}

	float upperMax = glm::radians(85.f);
	float downMax = glm::radians(-85.f);
	
	float scrollMax = 10.f;
	float scrollMin = 2.f;

	float topDownRotationSpeed = 0.0035;
	float cameraAngleSpeed = 0.0035;
	float mouseScrollSpeed = 0.15;

	///this is for the angle on the y axe
	float *topDownRotation = nullptr;
	float *cameraAngle = nullptr;
	float *mouseScroll = nullptr;

	void update(glm::vec2 mousePos, bool isClicked, float mouseScrol, sf::Window &window);

};

