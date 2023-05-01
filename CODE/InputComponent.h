#pragma once

#include "Components.h"
#include "myinputs.h"

class InputComponent : public Component
{
private:
	MyInputs* pInputs;
	TransformComponent* transformComponent;

public:
	
	void init() override
	{
		pInputs = MyInputs::GetInstance();
		transformComponent = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		pInputs->SampleKeyboard();

		if (pInputs->KeyPressed(DIK_W) || pInputs->KeyPressed(DIK_UP) || pInputs->KeyPressed(DIK_SPACE))
		{
			transformComponent->jump();
		}

		if (pInputs->KeyPressed(DIK_A) || pInputs->KeyPressed(DIK_LEFT))
		{
			transformComponent->moveLeft();
		}

		if (pInputs->KeyPressed(DIK_D) || pInputs->KeyPressed(DIK_RIGHT))
		{
			transformComponent->moveRight();
		}
	}	

};