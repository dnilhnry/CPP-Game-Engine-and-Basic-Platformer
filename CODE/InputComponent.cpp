#include "Components.h"

bool InputComponent::getFirstInput()
{
	return firstInput;
}

void InputComponent::checkForInputs()
{
	pInputs->SampleKeyboard();
	if (pInputs->KeyPressed(DIK_RETURN))
	{
		firstInput = true;
		pPC->setActive(true);
	}
	if (firstInput == true)
	{
		if (pInputs->KeyPressed(DIK_W) || pInputs->KeyPressed(DIK_UP) || pInputs->KeyPressed(DIK_SPACE))
		{
			pPC->jump();
		}

		if (pInputs->KeyPressed(DIK_A) || pInputs->KeyPressed(DIK_LEFT))
		{
			pPC->moveLeft();
		}

		if (pInputs->KeyPressed(DIK_D) || pInputs->KeyPressed(DIK_RIGHT))
		{
			pPC->moveRight();
		}
	}
}