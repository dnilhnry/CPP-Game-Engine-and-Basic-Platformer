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

	bool getFirstInput();

	void checkForInputs();

};