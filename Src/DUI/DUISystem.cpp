#include "DUISystem.h"


DUISystem::DUISystem(void)
{
	currentFocusedElement = NULL;
}


DUISystem::~DUISystem(void)
{
}

void DUISystem::Init()
{

}

void DUISystem::Update()
{
	if(currentFocusedElement != NULL)
	{
		if(input.keyboard.arrowDown.tapped &&
			currentFocusedElement->bottomLink != NULL)
		{
			SetFocus(currentFocusedElement->bottomLink);
		}
		else if(input.keyboard.arrowUp.tapped &&
			currentFocusedElement->topLink != NULL)
		{
			SetFocus(currentFocusedElement->topLink);
		}
		else if(input.keyboard.arrowLeft.tapped &&
			currentFocusedElement->leftLink != NULL)
		{
			SetFocus(currentFocusedElement->leftLink);
		}
		else if(input.keyboard.arrowRight.tapped &&
			currentFocusedElement->rightLink != NULL)
		{
			SetFocus(currentFocusedElement->rightLink);
		}
		else if(input.keyboard.spacebar.tapped || input.keyboard.enter.tapped)
		{
			currentFocusedElement->OnClick();
		}
	}
}

void DUISystem::SetFocus(duiElement* newElement)
{
	if(newElement)
	{
		currentFocusedElement->SetFocus(false);
		newElement->SetFocus(true);
		currentFocusedElement = newElement;
	}
}