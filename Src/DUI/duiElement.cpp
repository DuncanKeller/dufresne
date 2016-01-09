#include "duiElement.h"


duiElement::duiElement(void)
{	
	isFocused = false;
	startsWithFocus = false;
	
	topLink = NULL;
	bottomLink = NULL;
	leftLink = NULL;
	rightLink = NULL;
}


duiElement::~duiElement(void)
{
}

void duiElement::Init()
{

}

void duiElement::Update()
{

}

void duiElement::SetFocus(bool val)
{
	isFocused = val;
}

void duiElement::OnFocus()
{

}

void duiElement::OnClick()
{

}