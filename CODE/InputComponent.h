#pragma once

#include "Components.h"
#include "myinputs.h"

class InputComponent : public Component
{
private:
	MyInputs* pInputs;
	PhysicsComponent* pPC;

	bool firstInput;

public:

	InputComponent(MyInputs* i)
	{
		pInputs = i;
		firstInput = false;
	}

	void init() override
	{
		pPC = &entity->getComponent<PhysicsComponent>();
	}

	bool getFirstInput()
	{
		return firstInput;
	}

	void checkForInputs()
	{
		pInputs->SampleKeyboard();
		if (pInputs->KeyPressed(DIK_RETURN))
		{
			firstInput = true;
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

};