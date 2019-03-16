//////////////////////////////
//Copyright(c) 2019 Luta Vlad
//////////////////////////////
#include "CharacterMouseController.h"

void CharacterMouseController::update(glm::vec2 mousePos, bool isClicked, float mouseScrol)
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

}
