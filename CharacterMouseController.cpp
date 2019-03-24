//////////////////////////////
//Copyright(c) 2019 Luta Vlad
//////////////////////////////
#include "CharacterMouseController.h"

void CharacterMouseController::update(glm::vec2 mousePos, bool isClicked, float mouseScrol, sf::Window &window)
{
	if(isClicked)
	{
		if (!hasUpdatedLastFrame) { lastMousePos = mousePos; }

		glm::vec2 deltaMouse =  mousePos - lastMousePos;

		if(topDownRotation != nullptr)
		{
			*topDownRotation -= deltaMouse.x * topDownRotationSpeed;
		}

		if(cameraAngle != nullptr)
		{
			*cameraAngle += deltaMouse.y * cameraAngleSpeed;
		}

		hasUpdatedLastFrame = 1;
		lastMousePos = mousePos;
	}else
	{
		hasUpdatedLastFrame = 0;
	}

	if(cameraAngle != nullptr)
	{
		if (*cameraAngle > upperMax) 
			{ *cameraAngle = upperMax; }
		else if (*cameraAngle < downMax)
		{
			*cameraAngle = downMax;
		}
	}

	if(mouseScroll != nullptr)
	{
		*mouseScroll -= mouseScrol * mouseScrollSpeed;
		if (*mouseScroll > scrollMax) { *mouseScroll = scrollMax; }
		if (*mouseScroll < scrollMin) { *mouseScroll = scrollMin; }
	}

	//todo optimise
	sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2), window);
	lastMousePos = { sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y };
}
